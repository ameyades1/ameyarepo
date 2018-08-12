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


// Global History Size
const uint8 GR_SIZE = 12;

// Need at the most 2 ^ GR_SIZE counter
const uint32 NUM_COUNTERS = 1 << GR_SIZE;

// Same as number of counters
const uint32 NUM_BTB_ENTRIES = NUM_COUNTERS;


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

/*
 * 2 bit prediction counter
 */
typedef enum _counter
{
	NOT_TAKEN_STRONG = 0,
	NOT_TAKEN_WEAK,
	TAKEN_WEAK,
	TAKEN_STRONG
}PRED_COUNTER;

/*
 * Branch Target Buffer entry
 * Valid bit for fully associative
 * LRU for set associative
 */
typedef struct _btb_entry
{
	uint tag;
	uint target;
	bool valid;
	uint  lru;

}BTB_ENTRY;

/*
 * Predictor class
 */
class PREDICTOR
{
public:
	// The prediction counters
	uint8 PRED_COUNTER[NUM_COUNTERS];

	// The Branch Target Buffer
	BTB_ENTRY BTB[NUM_BTB_ENTRIES];

	// Current total number of valid entries in the BTB
	uint NUM_VALID_BTB_ENTRIES;

	// Current eviction candidate (Round Robin)
	uint EVICTION_ENTRY;

	// The global history (masked by GR_SIZE)
	uint32 GR;

	return_address_stack rat;

    bool get_prediction(const branch_record_c* br, const op_state_c* os,
    					uint *predicted_target_address);

    void update_predictor(const branch_record_c* br, const op_state_c* os,
    					  bool taken, uint actual_target_address);

    uint get_target_address(uint32 current_branch_address);

    /*
     * Clear everything at reset:
     * All counters NOT_TAKEN_STRONG, all BTB entries invalid (0)
     * All target addresses and tags = 0x00000000
     */
    PREDICTOR()
    {
    	memset(&PRED_COUNTER, 0, sizeof(PRED_COUNTER));
    	memset(&BTB, 0, sizeof(BTB));
    	GR = 0;
    	NUM_VALID_BTB_ENTRIES = 0;
    	EVICTION_ENTRY = 0;
    }
};

#endif // PREDICTOR_H_SEEN
