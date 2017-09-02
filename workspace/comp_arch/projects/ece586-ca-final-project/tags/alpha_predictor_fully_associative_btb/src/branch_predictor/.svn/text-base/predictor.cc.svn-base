
#define PREDICTOR_CC

#include "predictor.h"
#include <iostream>
#include <stdlib.h>
#include <list>
#include <algorithm>
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

// Size of BTB (entries)
#define SIZE_BTB	(512)

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


static std::list<uint32> list_ret_stack;

static std::list<BranchTBuf> branch_tbuf;


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

			(*predicted_target_address) = get_btb_target(br->instruction_addr);
			return true;
		}

		if(!br->is_conditional)
		{
			(*predicted_target_address) = get_btb_target(br->instruction_addr);
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
		(*predicted_target_address) = get_btb_target(br->instruction_addr);
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
	BranchTBuf item;
	if(list_ret_stack.size() >= SIZE_RET_STACK)
	{
		list_ret_stack.pop_back();
	}

	list_ret_stack.push_front(address);
}


void PREDICTOR::write_btb(const uint32 address, const uint32 data)
{
	BranchTBuf item(address,data);
	if(branch_tbuf.size() >= SIZE_BTB)
	{
		branch_tbuf.pop_back();
	}
	branch_tbuf.push_front(item);
}

uint32 PREDICTOR::get_btb_target(const uint32 address)
{
	uint32 target = 0;
	BranchTBuf item;
	item.address = address;

	std::list<BranchTBuf>::iterator l_it;
	l_it = std::find(branch_tbuf.begin(),branch_tbuf.end(), item);
	if(l_it != branch_tbuf.end())
	{
		item = (*l_it);
		target = l_it->target;

		branch_tbuf.erase(l_it);
		branch_tbuf.push_front((*l_it));
	}
	return target;
}
