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

//#define __get_stats__

/*
 ** CUSTOM TYPEDEFS
 */

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;

/*
 ** CUSTOM DATA TYPES
 */
typedef enum _PREDICTOR_TYPE
{
	PRED_GLOBAL = 0,
	PRED_LOCAL
}PREDICTOR_TYPE;


typedef struct _BRANCH_DATA
{
	long double offset;
	long double branch_count;
	long double avg;
	long double sum;
}BRANCH_DATA;


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

	BranchTBuf(uint32 l_address, uint32 l_target)
	{
		address = l_address;
		target = l_target;
	};
	~BranchTBuf()
	{

	}
	//BTB(const& BTB);
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
    bool get_prediction(const branch_record_c* br, const op_state_c* os, uint *predicted_target_address);

#ifdef __get_stats__
    void update_predictor(const branch_record_c* br, const op_state_c* os, bool taken, uint actual_target_address, BRANCH_DATA& direct, BRANCH_DATA& indirect, BRANCH_DATA& call, BRANCH_DATA& cond, BRANCH_DATA& ret);
#else
    void update_predictor(const branch_record_c* br, const op_state_c* os, bool taken, uint actual_target_address);
#endif
private:
    bool counter_result(uint size, uint cnt);
    void update_ctr(uint* ctr, uint size, bool actual);
    void update_choice_ctr(uint* ctr, PREDICTOR_TYPE pred);
    uint32 ret_stack_pop();
    void ret_stack_push(const uint32 address);
    uint32 get_btb_target(const uint32 address);
    void write_btb(const uint32 address, const uint32 data);

};




#endif // PREDICTOR_H_SEEN

