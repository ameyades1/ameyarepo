#define PREDICTOR_CC
#include "predictor.h"

extern return_address_stack rat;

bool PREDICTOR::get_prediction(const branch_record_c* br, const op_state_c* os,
							   uint *predicted_target_address)
{
	// Default
	bool prediction = false;
	*predicted_target_address = br->instruction_addr;

	/*
	 * Return address stack
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

        // No BTB yet, cant predict so pick a safe one
		*predicted_target_address = br->instruction_addr;
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
	}

	return prediction;   // true for taken, false for not taken

}


// Update the predictor after a prediction has been made.  This should accept
// the branch record (br) and architectural state (os), as well as a third
// argument (taken) indicating whether or not the branch was taken.

void PREDICTOR::update_predictor(const branch_record_c* br, const op_state_c* os, bool taken, uint actual_target_address)
{

}

