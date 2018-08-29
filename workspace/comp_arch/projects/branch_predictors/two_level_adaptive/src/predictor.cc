#define PREDICTOR_CC
#include "predictor.h"

bool PREDICTOR::get_prediction(const branch_record_c* br, const op_state_c* os,
							   uint *predicted_target_address)
{
	// Default
	bool prediction = false;
	*predicted_target_address = br->instruction_addr;

	/*
	 * Return address stack for calls, returns
	 */
	if(br->is_call)
	{
		// Call is unconditional, always taken
		prediction = true;

		// Oldest target address has least chance of being correct
		if(rat.stack.size() >= rat.max_size)
			rat.stack.pop_back();

		// Push the next RIP for a subsequent return to use
		rat.stack.push_front(br->instruction_next_addr);

        // Get target address from BTB
		*predicted_target_address = get_target_address(br->instruction_addr);

		// We are done
		return prediction;
	}
	else
	if (br->is_return)
	{
		// Return is unconditional, always taken
		prediction = true;

		if(rat.stack.empty())
		{
	        // Stack empty so pick a safe one
			*predicted_target_address = br->instruction_addr;
		}
		else
		{
			*predicted_target_address = rat.stack.front();
	    	rat.stack.pop_front();
		}

		// We are done
		return prediction;
	}

	/*
	 * If we land here, its a conditional branch
	 */

	// Compute the gshare hash
	uint gshare_hash = (br->instruction_addr & ~(-1 << GR_SIZE)) ^ (GR & ~(1 << GR_SIZE));

	// Predict taken
	if(true == get_condition_prediction(PRED_COUNTER[gshare_hash]))
	{
		*predicted_target_address = get_target_address(br->instruction_addr);
		prediction = true;
	}
	// Predict not taken
	else
		prediction = false;

	return prediction;   // true for taken, false for not taken
}


// Update the predictor after a prediction has been made.  This should accept
// the branch record (br) and architectural state (os), as well as a third
// argument (taken) indicating whether or not the branch was taken.

void PREDICTOR::update_predictor(const branch_record_c* br, const op_state_c* os, bool taken, uint actual_target_address)
{
	/*
	 * Update the condition counters
	 */
	update_counter(taken);

	// Find the current branch in the BTB and update with actual target address
	// As we traverse, count the valid and track the first invalid (empty) entry too.
	std::list<BTB_ENTRY>::iterator it;
	it = std::find(BTB.begin(), BTB.end(), BTB_ENTRY(br->instruction_addr));

	if (it != BTB.end())
	{
		// BTB Entry found
		it->target = actual_target_address;
	}
	else
	{
		// Not found
		if(BTB.size() >= NUM_BTB_ENTRIES)
		{
			// BTB Full. Evict someone
			BTB.pop_front();
		}

		// Insert the BTB entry
	    BTB.push_back(BTB_ENTRY(br->instruction_addr, actual_target_address));
	}

	/*
	 * Finally update the global history record
	 */
	GR = GR << 1;
	if(taken) GR |= 0x01;
	GR &= ~(-1 << GR_SIZE);
}

// Get the target address from BTB
uint PREDICTOR::get_target_address(uint current_branch_address)
{
	uint target_address;

	// If not found, set target to a safe known branch
	target_address = current_branch_address;

	std::list<BTB_ENTRY>::iterator it;
	it = std::find(BTB.begin(), BTB.end(), BTB_ENTRY(current_branch_address));

	if (it != BTB.end())
		target_address = it->target;
	else
		target_address = current_branch_address;

	return target_address;
}

// Update the two bit prediction counters
void PREDICTOR::update_counter(bool taken)
{
	if(taken)
	{
		PRED_COUNTER[GR]++;

		// Ceil to TAKEN_STRONG
		if(PRED_COUNTER[GR] >= COUNTER_SIZE)
			PRED_COUNTER[GR]--;
	}
	else
	{
		// Floor to NOT_TAKEN_STRONG
		if(NOT_TAKEN_STRONG != PRED_COUNTER[GR])
			PRED_COUNTER[GR]--;
	}
}

bool PREDICTOR::get_condition_prediction(uint8 counter_value)
{
	if(counter_value == NOT_TAKEN_STRONG || counter_value == NOT_TAKEN_WEAK)
		return false;
	else
		return true;
}
