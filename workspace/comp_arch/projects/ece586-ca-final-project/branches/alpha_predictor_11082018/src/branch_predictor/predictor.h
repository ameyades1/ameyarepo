/* Author: Mark Faust
 *
 * C version of predictor file
*/

#ifndef PREDICTOR_H_SEEN
#define PREDICTOR_H_SEEN

#include <cstddef>
#include <cstring>
#include <inttypes.h>

#include "op_state.h"   // defines op_state_c (architectural state) class 
#include "tread.h"      // defines branch_record_c class

#include <iostream>
#include <stdlib.h>

#include <cmath>
#include <list>
#include <vector>
#include <algorithm>

/*
 ** CUSTOM TYPEDEFS
 */

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef signed int 			int32;
typedef signed short		int16;

class PREDICTOR
{
public:
    bool get_prediction(const branch_record_c* br, const op_state_c* os,
    					uint *predicted_target_address);

    void update_predictor(const branch_record_c* br, const op_state_c* os,
    					  bool taken, uint actual_target_address);
};


/*
 * CUSTOM TYPES
 */

// Return Address Stack
typedef struct _rat
{
	std::list<uint> stack;
	uint max_size;

	_rat()
	{
		max_size = 4; // Default
	}
}return_address_stack;


#endif // PREDICTOR_H_SEEN
