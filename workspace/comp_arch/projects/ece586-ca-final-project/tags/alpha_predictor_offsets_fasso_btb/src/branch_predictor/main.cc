/* Author: Chris Wilkerson;   Created: Thu Aug 12 16:19:58 PDT 2004
 * Description: Branch predictor driver.
*/

#include <cstdio>
#include <cstdlib>
#include "tread.h"

// include and define the predictor
#include "predictor.h"
PREDICTOR predictor;

// usage: predictor <trace>
int
main(int argc, char* argv[])
{
    using namespace std;

    if (2 != argc) {
        printf("usage: %s <trace>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    cbp_trace_reader_c cbptr = cbp_trace_reader_c(argv[1]);
    branch_record_c br;
    uint targetaddress;		// predicted target address 
#ifdef __get_stats__
    BRANCH_DATA direct;
    BRANCH_DATA indirect;
    BRANCH_DATA call;
    BRANCH_DATA cond;
    BRANCH_DATA ret;

    direct.branch_count = 1;
    direct.sum = 0;
    indirect.branch_count = 1;
    indirect.sum = 0;
    call.branch_count = 1;
    call.sum = 0;
    cond.branch_count = 1;
    cond.sum = 0;
    ret.branch_count = 1;
    ret.sum = 0;
#endif
    // read the trace, one branch at a time, placing the branch info in br
    while (cbptr.get_branch_record(&br)) {

        // ************************************************************
        // Competing predictors must have the following methods:
        // ************************************************************

        // get_prediction() returns the prediction your predictor would like to make
        bool predicted_taken = predictor.get_prediction(&br, cbptr.osptr, &targetaddress);

        // predict_branch() tells the trace reader how you have predicted the branch and target address
        bool actual_taken    = cbptr.predict_branch(predicted_taken, &targetaddress);
            
        // finally, update_predictor() is used to update your predictor with the
        // correct branch result
#ifdef __get_stats__
        predictor.update_predictor(&br, cbptr.osptr, actual_taken, targetaddress, direct, indirect, call, cond, ret);
#else
        predictor.update_predictor(&br, cbptr.osptr, actual_taken, targetaddress);
#endif
    }

#ifdef __get_stats__
    printf ("\n-----Branch Stats-----\n");
    printf ("\n Direct: Count: %Lf Avg_Offset: %Lf", direct.branch_count, direct.avg);
    printf ("\n Indirect: Count: %Lf Avg_Offset: %Lf", indirect.branch_count, indirect.avg);
    printf ("\n Call: Count: %Lf Avg_Offset: %Lf", call.branch_count, call.avg);
    printf ("\n Conditional: Count: %Lf Avg_Offset: %Lf", cond.branch_count, cond.avg);
    printf ("\n Return: Count: %Lf Avg_Offset: %Lf", ret.branch_count, ret.avg);
    printf ("\n----------------------\n");
#endif
}



