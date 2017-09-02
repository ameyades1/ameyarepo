
#define PREDICTOR_CC

#include "predictor.h"
#include <iostream>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <cmath>
/*
 * DEBUG ENABLING MACRO
 */
//#define	__debug__



/*
 ** CONFIG MACROS
 */

// Size of local history table
#define TBL_SZ_LOCAL_HIST	(1024)

// Size of local predictor table
#define TBL_SZ_LOCAL_PRED	(1024)

// Size of global prediction table
#define TBL_SZ_GLOBAL_PRED	(4096)

// Size of choice prediction table
#define TBL_SZ_CHOICE_PRED	(4096)

// Size of path history
#define TBL_SZ_PATH_HIST	(12)

// Size of local prediction saturating counter (2 raised to num of bits)
#define SIZE_LOCAL_PRED_COUNT	(8)

// Size of global prediction saturating counter (2 raised to num of bits)
#define SIZE_GLOBAL_PRED_COUNT	(4)

// Size of choice prediction saturating counter (2 raised to num of bits)
#define SIZE_CHOICE_COUNT	(4)

// Size of local history
#define SIZE_LOCAL_HIST		(10)


// Size of return stack
#define SIZE_RET_STACK	(16)

/*
 * Macros for Offset Table (Direct Mapped)
 */
// Size of Offset BTB (entries) (Table 1)
#define BTB_TBL1_SIZE	(512)

// Num of offset bits
#define BTB_TBL1_NUM_OFFSET_BITS	(17)

// Num of index bits
#define BTB_INDEX_BITS			(9)

// Num of tag1 bits
#define BTB_TAG1_BITS			(15)

// Num of tag2 bits
#define BTB_TAG2_BITS			(8)


static uint32 get_index_bits(const uint32 pc)
{
	uint32 index = 0;

	index = pc << (32 - BTB_INDEX_BITS);
	index = index >> (32 - BTB_INDEX_BITS);

	return index;
}

static uint32 get_tag1_bits(const uint32 pc)
{
	uint32 tagbits1 = 0;
	tagbits1 = pc >> BTB_INDEX_BITS;
	tagbits1 = tagbits1 << (32 - BTB_TAG1_BITS);
	tagbits1 = tagbits1 >> (32 - BTB_TAG1_BITS);

	return tagbits1;
}

static uint32 get_tag2_bits(const uint32 pc)
{
	uint32 tagbits2 = 0;
	tagbits2 = pc >> (32 - BTB_TAG2_BITS);
	return tagbits2;
}
#define GET_TAG2_BITS(pc,tagbits2) (tagbits2) = (pc) >> (32 - BTB_TAG2_BITS)


// Num of remaining PC bits
#define BTB_TBL2_SIZE				(512)


/*
 * Macros of Fully associative tables
 */

// Table 3 size
#define BTB_TBL3_SIZE 	(128)

// Table 3 Size
#define BTB_TBL4_SIZE	(64)

// Table 4 Size
#define BTB_TBL5_SIZE 	(32)


/*
 ** MASKING MACROS
 */

#define GET_LOCAL_HIST_INDEX(V) ( (V) & 0x3FF )


/*
 ** GLOBAL DATA TABLES
 */

// The local history table
static uint tbl_local_hist[TBL_SZ_LOCAL_HIST];

// The local prediction table
static uint tbl_local_pred[TBL_SZ_LOCAL_PRED];

// The global prediction table
static uint tbl_global_pred[TBL_SZ_GLOBAL_PRED];

// The choice prediction table
static uint tbl_choice_pred[TBL_SZ_CHOICE_PRED];

// The global path history
static uint tbl_path_hist;

// The return stack
static std::list<uint32> list_ret_stack;


/*
 * Branch target buffers
 */

// Offset table
OFFSET_TBL offset_tbl[BTB_TBL1_SIZE];

// Tag table to store leftover bits of PC
uint8 tag_tbl[BTB_TBL2_SIZE];

// Fully associative tables
FASSO_TBL fasso_table3[BTB_TBL3_SIZE];
FASSO_TBL fasso_table4[BTB_TBL4_SIZE];
FASSO_TBL fasso_table5[BTB_TBL5_SIZE];

/*
 ** FUNCTION DEFINITIONS
 */

bool PREDICTOR::get_prediction(const branch_record_c* br, const op_state_c* os,
							   uint *predicted_target_address)
{
	bool prediction = true;
	//return prediction;
/*
 * BRANCH PREDICTION PART BEGINS
 */
	if(br)
	{
		if(br->is_return)
		{
			uint32 ret_add = ret_stack_pop();
			(*predicted_target_address) = ret_add;
			return true;
		}

		if(br->is_call)
		{

			uint32 address = get_btb_target(br->instruction_addr);
			if(address != 0)
				(*predicted_target_address) = address;
			return true;
		}

		if(!br->is_conditional)
		{
			uint32 address = get_btb_target(br->instruction_addr);
			if(address != 0)
				(*predicted_target_address) = address;
			return true;
		}
	}
	if(br)
	{
		// Get the local history
		uint local_hist_index = GET_LOCAL_HIST_INDEX(br->instruction_addr);
		uint local_hist = tbl_local_hist[local_hist_index];
#ifdef __debug__
		static uint32 inst_num = 1;
		printf("\n-----%d-----\n",inst_num++);
#endif

#ifdef __debug__
		printf("--Local History: %x\n",local_hist);
#endif

#ifdef __debug__
		printf("--Global Path History: %x\n",tbl_path_hist);
#endif

		// Get the local prediction counter value
		uint local_pred_cnt = tbl_local_pred[local_hist];

#ifdef __debug__
		printf("--Local Pred Counter: %d",local_pred_cnt);
#endif
		// Get the choice prediction counter value
		uint choice_pred_cnt = tbl_choice_pred[tbl_path_hist];
#ifdef __debug__
		printf("--Choice Pred Counter: %d",choice_pred_cnt);
#endif
		// Get the global prediction counter value
		uint global_pred_cnt = tbl_global_pred[tbl_path_hist];
#ifdef __debug__
		printf("--Global Pred Counter: %d",global_pred_cnt);
#endif
		// Choose the predictor
        PREDICTOR_TYPE predictor = PRED_LOCAL;
        bool cnt_res = counter_result(SIZE_CHOICE_COUNT,choice_pred_cnt);

        // true means global predictor, false means local predictor
        if(cnt_res)
        	predictor = PRED_LOCAL;
        else
        	predictor = PRED_GLOBAL;

        // Get the prediction from the counter
        if(PRED_LOCAL == predictor)
        	prediction = counter_result(SIZE_LOCAL_PRED_COUNT, local_pred_cnt);
        else
        	prediction = counter_result(SIZE_GLOBAL_PRED_COUNT, global_pred_cnt);

	}
/* -------------BRANCH PREDICTION PART ENDS ------------------------------ */
#if 1
	static uint i = 1;
	if(i == 1)
	{
		std::cout<<"Loading... "<< std::endl;
		i=0;
	}
#endif

	if(prediction)
	{
		uint32 address = get_btb_target(br->instruction_addr);
		if(address != 0)
			(*predicted_target_address) = address;
	}
	return prediction;   // true for taken, false for not taken
}



// Update the predictor after a prediction has been made.  This should accept
// the branch record (br) and architectural state (os), as well as a third
// argument (taken) indicating whether or not the branch was taken.
#ifdef __get_stats__
void PREDICTOR::update_predictor(const branch_record_c* br, const op_state_c* os, bool taken, uint actual_target_address, BRANCH_DATA& direct, BRANCH_DATA& indirect, BRANCH_DATA& call, BRANCH_DATA& cond, BRANCH_DATA& ret)
#else
void PREDICTOR::update_predictor(const branch_record_c* br, const op_state_c* os, bool taken, uint actual_target_address)
#endif
{
#ifdef __get_stats__
	//static int select = 2;
	if(br)
	{
		//select--;
		//if(select == 0)
		{
			//select = 2;
			// Indirect which are not returns
			if(br->is_indirect && !br->is_return)
			{
				if(br->instruction_addr > actual_target_address)
					indirect.offset = br->instruction_addr - actual_target_address;
				else
					indirect.offset = actual_target_address - br->instruction_addr;

				indirect.sum += indirect.offset;
				indirect.avg = indirect.sum / indirect.branch_count;
				indirect.branch_count++;
			}

			// Direct branches (jumps) and not calls
			if(!br->is_indirect && !br->is_call)
			{
				if (br->instruction_addr > actual_target_address)
					direct.offset = br->instruction_addr - actual_target_address;
				else
					direct.offset = actual_target_address - br->instruction_addr;

				direct.sum += direct.offset;
				direct.avg = direct.sum / direct.branch_count;
				direct.branch_count++;
			}

			// Direct calls
			if(br->is_call)
			{
				if(br->instruction_addr > actual_target_address)
					call.offset = br->instruction_addr - actual_target_address;
				else
					call.offset = actual_target_address - br->instruction_addr;

				call.sum += call.offset;
				call.avg = call.sum / call.branch_count;
				call.branch_count++;
			}

			// Conditional branches
			if(br->is_conditional)
			{
				if(br->instruction_addr > actual_target_address)
					cond.offset = br->instruction_addr - actual_target_address;
				else
					cond.offset = actual_target_address - br->instruction_addr;

				cond.sum += cond.offset;
				cond.avg = cond.sum / cond.branch_count;
				cond.branch_count++;
			}

			// Returns
			if(br->is_return)
			{
				if(br->instruction_addr > actual_target_address)
					ret.offset = br->instruction_addr - actual_target_address;
				else
					ret.offset = actual_target_address - br->instruction_addr;

				ret.sum += ret.offset;
				ret.avg = ret.sum / ret.branch_count;
				ret.branch_count++;
			}
		}
	}
#endif

	if(br)
	{
		if(br->is_call)
		{
			ret_stack_push(br->instruction_next_addr);
			write_btb(br->instruction_addr, actual_target_address);
			return;
		}
		if(!br->is_conditional)
		{
			write_btb(br->instruction_addr, actual_target_address);
			return;
		}
	}


	if(br)
	{
#ifdef __debug__
		static uint32 inst_no = 1;
		printf("\n----Update %d----\n",inst_no++);
#endif
		// Get the local history index
		uint local_hist_index = GET_LOCAL_HIST_INDEX(br->instruction_addr);

		// Get local history for that branch
		uint local_hist = tbl_local_hist[local_hist_index];

		// Save the previous local prediction counter
		uint prev_local_pred_count = tbl_local_pred[local_hist];

		// Update local prediction table for that branch
		update_ctr(&tbl_local_pred[local_hist],SIZE_LOCAL_PRED_COUNT,taken);

#ifdef __debug__
		printf("--Local Pred Counter: %d",tbl_local_pred[local_hist]);
#endif
		// Update local history for that branch
		tbl_local_hist[local_hist_index] = tbl_local_hist[local_hist_index] >> 1;
		tbl_local_hist[local_hist_index] |= (taken << (SIZE_LOCAL_HIST-1) );

#ifdef __debug__
		printf("--Local History: %x\n",tbl_local_hist[local_hist_index]);
#endif
		// Save global prediction counter before updating
		uint prev_global_pred_count = tbl_global_pred[tbl_path_hist];

		// Update global prediction table for that path history
		update_ctr(&tbl_global_pred[tbl_path_hist], SIZE_GLOBAL_PRED_COUNT,taken);
#ifdef __debug__
		printf("--Global Pred Counter: %d",tbl_global_pred[tbl_path_hist]);
#endif
		// Update choice prediction table for that path history

		// If global predictor was successful and local unsuccessful stick with global predictor
		if(counter_result(SIZE_GLOBAL_PRED_COUNT, prev_global_pred_count) == taken &&
				counter_result(SIZE_LOCAL_PRED_COUNT, prev_local_pred_count) != taken)
			update_choice_ctr(&tbl_choice_pred[tbl_path_hist],PRED_GLOBAL);

		// If global predictor was unsuccessful and local successful stick with local predictor
		else if(counter_result(SIZE_GLOBAL_PRED_COUNT, prev_global_pred_count) != taken &&
				counter_result(SIZE_LOCAL_PRED_COUNT, prev_local_pred_count) == taken)
			update_choice_ctr(&tbl_choice_pred[tbl_path_hist],PRED_LOCAL);


		//update_ctr(&tbl_choice_pred[tbl_path_hist], SIZE_CHOICE_COUNT,which_pred);
#ifdef __debug__
		printf("--Choice Pred Counter: %d",tbl_choice_pred[tbl_path_hist]);
#endif
		// Update global path history
		tbl_path_hist = tbl_path_hist >> 1;
		tbl_path_hist |= (taken << (TBL_SZ_PATH_HIST-1) );
#ifdef __debug__
		printf("--Global Path History: %x\n",tbl_path_hist);
#endif

		write_btb(br->instruction_addr, actual_target_address);
	}

}

void PREDICTOR::update_ctr(uint* ctr, uint size, bool actual)
{
	if(ctr)
	{
		// If branch was taken, move towards left
		if(true == actual)
		{
			if((*ctr) > 0)
				(*ctr)--;
		}
		// If branch was not taken, move towards right
		else
		{
			if((*ctr) < size - 1)
				(*ctr)++;
		}
	}
}

void PREDICTOR::update_choice_ctr(uint* ctr, PREDICTOR_TYPE pred)
{
	if(ctr)
	{
		// If Local was successful, move towards strongly local
		if(PRED_LOCAL == pred)
		{
			if((*ctr) > 0)
				(*ctr)--;
		}

		// Or if global was successful, move towards strongly global
		else if(PRED_GLOBAL == pred)
		{
			if((*ctr) < SIZE_CHOICE_COUNT - 1)
				(*ctr)++;
		}
	}
}

bool PREDICTOR::counter_result(uint size, uint cnt)
{
	bool prediction = false;

	if(cnt < (size)/2)
	{
		prediction = true;
	}

	return prediction;
}

/*
 * We implement the stack as a list. Items are added to front,
 * and removed from the back.
 * If we push items on a full stack, we remove the bottom element.
 * i.e. the back element.
 */
uint32 PREDICTOR::ret_stack_pop()
{

	uint32 stack_top = 0;

	if(list_ret_stack.empty())
		stack_top = 0;
	else
	{
		stack_top = list_ret_stack.front();
		list_ret_stack.pop_front();
	}

	return stack_top;
}

void PREDICTOR::ret_stack_push(const uint32 address)
{

	if(list_ret_stack.size() >= SIZE_RET_STACK)
	{
		list_ret_stack.pop_back();
	}

	list_ret_stack.push_front(address);
}


void PREDICTOR::write_btb(const uint32 pc, const uint32 target)
{
	// If the target can be expressed as a displacement offset, lets put it
	// in the offset table

	uint32 uoffset = abs(pc - target);
	int32 soffset = pc - target;

	uint32 index;
	uint32 tag1;
	uint32 tag2;

	if( uoffset < (1 << BTB_TBL1_NUM_OFFSET_BITS) )
	{
		index = get_index_bits(pc);
		tag1 = get_tag1_bits(pc);
		tag2 = get_tag2_bits(pc);

		offset_tbl[index].pc = tag1;
		offset_tbl[index].offset = soffset;
		tag_tbl[index] = tag2;
	}
	else
	{
#if 0
		// We store in fully associative stores
		if (0 != find_item(pc,BTB_TBL3_SIZE,&fasso_table3[0]))
		{
			insert_item(pc,BTB_TBL3_SIZE,&fasso_table3[0],target);
		}
		else if(0! = find_item(pc,BTB_TBL4_SIZE,&fasso_table4[0]) )
		{

		}
#endif
	}

}

uint32 PREDICTOR::get_btb_target(const uint32 address)
{
	uint32 target = 0;

	// First look in offset table
	int32 offset = 0;

	offset = get_offset(address);
	if(0 == offset)
	{
#if 0
		/*
		 * IF WE LAND HERE, WE CHECK THE OTHER FULLY ASSOCIATIVE TABLES
		 */
		target = find_item(address,(uint32)BTB_TBL3_SIZE,&fasso_table3[0]);
		if(0 == target)
		{
			target = find_item(address,(uint32)BTB_TBL4_SIZE,&fasso_table4[0]);
			if(0 == target)
			{
				target = find_item(address,(uint32)BTB_TBL5_SIZE,&fasso_table5[0]);
			}
		}
#endif
	}
	else
	{
		// We found the PC in offset table.
		uint32 mag_offset = abs(offset);
		if(offset < 0)
		{
			target = address + mag_offset;
		}
		else
		{
			target = address - mag_offset;
		}

	}

	return target;
}


int32 PREDICTOR::get_offset(const uint32 pc)
{
	int32 offset = 0;
	uint16 index = 0;
	uint16 tagbits1 = 0;
	uint16 tagbits2 = 0;

	/*
	 * CHECK IN THE OFFSET TABLE
	 */
	// Get the index bits
	index = get_index_bits(pc);
	//GET_INDEX_BITS(pc,index);

	// Obtain the tag1 bits
	tagbits1 = get_tag1_bits(pc);
	//GET_TAG1_BITS(pc,tagbits1);

	// Get the tag2 bits
	tagbits2 = get_tag2_bits(pc);
	//GET_TAG2_BITS(pc,tagbits2);

	// Check if the tagbits1 and the tagbits2 match
	if(offset_tbl[index].pc == tagbits1 && tag_tbl[index] == tagbits2)
	{
		// If they do, we have a match!
		offset = offset_tbl[index].offset;
		return offset;
	}

	return offset;
}

/*
 * Searches for an item in an fully associative table
 */
uint32 PREDICTOR::find_item(const uint32 pc, const uint32 tbl_size, FASSO_TBL* ptbl)
{
	uint32 target_address = 0;

	if(NULL == ptbl)
		return 0;

	uint32 i = 0;
	for(i = 0; i < tbl_size; i++)
	{
		if(ptbl[i].pc == pc)
		{
			return ptbl[i].target_address;
		}
	}

	return target_address;
}

void PREDICTOR::insert_item(const uint32 pc, const uint32 tbl_size, FASSO_TBL* ptbl, uint32 data)
{
	if(NULL == ptbl)
		return;

	bool found = false;
	uint32 i = 0;
	uint32 empty_slot = 0;
	bool slot_avail = false;

	for(i = 0; i < tbl_size; i++)
	{
		if(ptbl[i].pc == pc)
		{
			ptbl[i].target_address = data;
			ptbl[i].pc = pc;
			found = true;
			break;
		}
		if(ptbl[i].target_address == 0)
		{
			empty_slot = i;
			slot_avail = true;
		}
	}
	if(!found && !slot_avail)
	{
		ptbl[0].target_address = data;
		ptbl[0].pc = pc;
	}
	else if(!found && slot_avail)
	{
		ptbl[empty_slot].target_address = data;
		ptbl[empty_slot].pc = pc;
	}
}


