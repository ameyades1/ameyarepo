/* Author: Mark Faust
 *
 * C version of predictor file
*/

#ifndef PREDICTOR_H_SEEN
#define PREDICTOR_H_SEEN

#include <cstddef>
#include <cstring>
#include <inttypes.h>
#include <vector>
#include "op_state.h"   // defines op_state_c (architectural state) class 
#include "tread.h"      // defines branch_record_c class

#include <iostream>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <cmath>

//#define __get_stats__
//#define	__debug__
/*
 ** CUSTOM TYPEDEFS
 */

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef signed int 			int32;
typedef signed short		int16;

/*
 ** CUSTOM DATA TYPES
 */
typedef enum _PREDICTOR_TYPE
{
	PRED_GLOBAL = 0,
	PRED_LOCAL
}PREDICTOR_TYPE;

typedef enum _INST_TYPE
{
	INST_DIRECT,
	INST_INDIRECT,
	INST_CALL,
	INST_RETURN,
	INST_CONDITIONAL,
	INST_TYPE_NO_CARE
}INST_TYPE;


// Used for stats collection
typedef struct _BRANCH_DATA
{
	long double offset;
	long double branch_count;
	long double avg;
	long double sum;
}BRANCH_DATA;

// Type for the signed offset table
typedef struct _OFFSET_TBL
{
	int32 offset;
	uint32 pc;

}OFFSET_TBL;

// Type for the return stack needed only for STL
class BranchTBuf
{
public:
	uint32 address;
	uint32 target;

	BranchTBuf()
	{
		address = 0;
		target = 0;
	};

	// Simple parameterized copy constructor
	BranchTBuf(uint32 l_address, uint32 l_target)
	{
		address = l_address;
		target = l_target;
	};

	~BranchTBuf()
	{

	}

	// Overloaded == operator for STL find() algorithm
	bool operator== (const BranchTBuf& other)
	{
		if (address == other.address)
			return true;
		else
			return false;

	};
};


class PREDICTOR
{
public:
    bool get_prediction(const branch_record_c* br, const op_state_c* os,
    					uint *predicted_target_address);

#ifdef __get_stats__
    void update_predictor(const branch_record_c* br, const op_state_c* os,
    					bool taken, uint actual_target_address,
    					BRANCH_DATA& direct, BRANCH_DATA& indirect,
    					BRANCH_DATA& call, BRANCH_DATA& cond,
    					BRANCH_DATA& ret);
#else
    void update_predictor(const branch_record_c* br, const op_state_c* os,
    					  bool taken, uint actual_target_address);
#endif

private:
    bool counter_result(uint size, uint cnt);

    void update_ctr(uint* ctr, uint size, bool actual);

    void update_choice_ctr(uint* ctr, PREDICTOR_TYPE pred);

    uint32 ret_stack_pop();

    void ret_stack_push(const uint32 address);

    uint32 get_btb_target(const uint32 address, INST_TYPE type);

    void write_btb(const uint32 address, const uint32 data, INST_TYPE type);

    int32 get_offset(const uint32 pc);

    uint32 find_item(const uint32 pc, std::list<BranchTBuf>& buf);

    void insert_item(const uint32 pc, std::list<BranchTBuf>& buf, uint32 data,
    				 uint32 buf_size);

    bool is_full(std::list<BranchTBuf>& buf, uint32 size);

    void remove_item(const uint32 pc, std::list<BranchTBuf>& buf);
};

#endif // PREDICTOR_H_SEEN
