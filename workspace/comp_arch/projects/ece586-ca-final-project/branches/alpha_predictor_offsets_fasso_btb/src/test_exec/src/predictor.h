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


class PREDICTOR
{
public:
    bool get_prediction(const branch_record_c* br, const op_state_c* os, uint *predicted_target_address);

    void update_predictor(const branch_record_c* br, const op_state_c* os, bool taken, uint actual_target_address);

private:
    bool counter_result(uint size, uint cnt);
    void update_ctr(uint* ctr, uint size, bool actual);
    void update_choice_ctr(uint* ctr, PREDICTOR_TYPE pred);
};

#endif // PREDICTOR_H_SEEN

