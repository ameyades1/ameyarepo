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


/*
 * CUSTOM TYPES
 */

// Return Address Stack
typedef struct _rat
{
	std::list<uint> stack;
	uint8 max_size;

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
	TAKEN_STRONG,
	COUNTER_SIZE
}PREDICTION;

/*
 * Branch Target Buffer entry
 */
typedef struct _btb_entry
{
	uint32 tag;
	uint32 target;


	_btb_entry(uint32 _tag)
	{
		tag = _tag;
	}

	_btb_entry(uint32 _tag, uint32 _target)
	{
		tag = _tag;
		target = _target;
	}

	// Predicate
	bool operator() (const _btb_entry& entry) const
	{
		return entry.tag == tag;
	}

	bool operator== (const _btb_entry& entry) const
	{
		return entry.tag == tag;
	}

}BTB_ENTRY;




// The structure of a line
// Each element 1 bit, Max block size = 32
typedef struct _line
{
	uint32	line_data;
	uint32	tag;
	bool	valid;

	_line()
	{
		line_data = 0;
		tag = 0;
		valid = false;
	}

}Line;

// The structure of a set
typedef struct set
{
	Line*	lines;
	uint32	lru;

	set()
	{
		lines = NULL;
		lru = 0;
	}

	~set()
	{
		if(lines)
		{
			delete[] lines;
			lines = NULL;
		}
	}

}Set;

// A generic set associative cache for bit size elements
// Block size is 32 bits. Mask as needed
class Cache
{
private:
	uint32 num_sets;
    uint8 associativity;

    uint8 log2_num_sets;

public:
	Set* array;

	Cache()
	{
		num_sets      = 0;
		associativity = 0;
		log2_num_sets = 0;
		array         = NULL;
	}

	Cache(uint32 _num_sets, uint8 _associativity)
	{
		init_cache(_num_sets, _associativity);
	}

	~Cache()
	{
		if(array)
		{
		    for(unsigned int i = 0; i < num_sets; i++)
		    {
			    if(array[i].lines)
			    {
			    	delete [] array[i].lines;
			    	array[i].lines = NULL;
			    }
		    }

		    delete[] array;
		    array = NULL;
		}
	}

	void clear_cache()
	{
		for(unsigned int i = 0; i < num_sets; i++)
		{
			for(unsigned int j = 0; j < associativity; j++)
			{
				array[i].lines[j].line_data = 0;
				array[i].lines[j].tag       = 0;
				array[i].lines[j].valid     = false;
			}
		}
	}

	void init_cache(uint32 _num_sets, uint8 _associativity)
	{
		num_sets = _num_sets;
		associativity = _associativity;
		log2_num_sets = log2(num_sets);

		array = new Set[num_sets];

		for(unsigned int i = 0; i < num_sets; i++)
		{
			array[i].lines = new Line[associativity];
		}
	}

	void write_cache(uint32 address, uint32 data)
	{
		bool cache_hit = false;
        unsigned int way;

		uint32 index_bits = address & ~(-1 << log2_num_sets);
		uint32 tag_bits = address & (-1 << log2_num_sets);
		tag_bits = tag_bits >> log2_num_sets;

		for(way = 0; way < associativity; way++)
        {
			if(array[index_bits].lines[way].valid && array[index_bits].lines[way].tag == tag_bits)
        	{
        		// Cache Hit
				array[index_bits].lines[way].line_data = data;
				array[index_bits].lru = (way + 1) % associativity; // Definitely not this one
        		cache_hit = true;
        		break;
        	}
        }

		// Cache Miss
		if(!cache_hit)
		{
			// All ways full. Evict LRU
			if(way == associativity)
			{
				array[index_bits].lines[array[index_bits].lru].line_data = data;
				array[index_bits].lines[array[index_bits].lru].tag = tag_bits;
				array[index_bits].lines[array[index_bits].lru].valid = true;
				array[index_bits].lru = (way + 1) % associativity; // Definitely not this one
			}

			// Fill in the empty way
			else
			{
				array[index_bits].lines[way].line_data = data;
				array[index_bits].lines[way].tag = tag_bits;
				array[index_bits].lines[way].valid = true;
				array[index_bits].lru = (way + 1) % associativity; // Definitely not this one
			}
		}
	}


	bool read_cache(uint32 address, uint32& data)
	{
		bool cache_hit = false;
        unsigned int way;

		uint32 index_bits = address & ~(-1 << log2_num_sets);
		uint32 tag_bits = address & (-1 << log2_num_sets);
		tag_bits = tag_bits >> log2_num_sets;

		for(way = 0; way < associativity; way++)
        {
			if(array[index_bits].lines[way].valid && array[index_bits].lines[way].tag == tag_bits)
        	{
        		// Cache Hit
				data = array[index_bits].lines[way].line_data;
				array[index_bits].lru = way; // Definitely this one
        		cache_hit = true;
        		break;
        	}
        }

		// Cache Miss
		if(!cache_hit)
		{
            data = 0;
		}

		return cache_hit;
	}
};


/*
 * Predictor class
 */
class PREDICTOR
{
private:
	// Global History Record Size in bits
	uint8 GHR_SIZE; // = 12

	// Associative History Register Table (AHRT)
	Cache* AHRT;

	// AHRT Entries
	uint32 AHRT_ENTRIES; // = 512

	// AHRT Associativity
	uint32 AHRT_ASSOCIATIVITY;

	// Number of BTB Entries Implemented as a FIFO
	uint32 NUM_BTB_ENTRIES; // = AHRT_ENTRIES;

	// The prediction counters
	uint8* PRED_COUNTER; // = 2 ^ GHR_SIZE;

	// Number of Prediction Counters
	uint32 NUM_PRED_COUNTER;

	// The Branch Target Buffer
	std::list<BTB_ENTRY> BTB; // [NUM_BTB_ENTRIES];

	// The return address stack
	return_address_stack rat;

public:

    bool get_prediction(const branch_record_c* br, const op_state_c* os,
    					uint *predicted_target_address);

    void update_predictor(const branch_record_c* br, const op_state_c* os,
    					  bool taken, uint actual_target_address);

    uint get_target_address(uint32 current_branch_address);

    void update_counter(uint32 ghrt, bool taken);

    bool get_condition_prediction(uint8 counter_value);

    /*
     * Clear everything at reset:
     * All counters NOT_TAKEN_STRONG, all BTB entries invalid (0)
     * All target addresses and tags = 0x00000000
     */
    PREDICTOR()
    {
    	PRED_COUNTER = NULL;
    	GHR_SIZE = 0;
    	AHRT_ENTRIES = 0;
    	NUM_BTB_ENTRIES = 0;
    	AHRT = NULL;
    	AHRT_ASSOCIATIVITY = 0;
    	NUM_PRED_COUNTER = 0;
    }

    PREDICTOR(uint8 _rat_size, uint8 _ghr_size, uint32 _ahrt_entries, uint32 _ahrt_associativity, uint32 _btb_entries)
    {
    	PREDICTOR();
    	GHR_SIZE = _ghr_size;
    	rat.max_size = _rat_size;
    	AHRT_ASSOCIATIVITY = _ahrt_associativity;
    	AHRT_ENTRIES = _ahrt_entries;
    	NUM_BTB_ENTRIES = _btb_entries;
    	NUM_PRED_COUNTER = 1 << GHR_SIZE;

    	PRED_COUNTER = new uint8[NUM_PRED_COUNTER];

    	memset(PRED_COUNTER, 0, sizeof(uint8) * NUM_PRED_COUNTER);

    	AHRT = new Cache(AHRT_ENTRIES, AHRT_ASSOCIATIVITY);

    }

    ~PREDICTOR()
    {
    	if(PRED_COUNTER) delete[] PRED_COUNTER;
    	if(AHRT) delete AHRT;
    }
};

#endif // PREDICTOR_H_SEEN
