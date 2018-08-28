/* Author: Chris Wilkerson;   Created: Thu Aug 12 16:19:58 PDT 2004
 * Description: Branch predictor driver.
*/

#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include "tread.h"

/*
 * Optimal Sizes
 * RAT : 16
 */

// include and define the predictor
#include "predictor.h"
PREDICTOR* predictor;


// usage: predictor <trace>
int
main(int argc, char* argv[])
{
    using namespace std;
    /*
     * Arguments
     * 1 = trace file
     * 2 = return address stack size
     */
    // Return address stack size
    uint8 rat_size;

    // Global history record size
    uint8 gr_size;

    branch_record_c br;     // Branch record
    uint targetaddress;		// predicted target address
    int c;

    cbp_trace_reader_c* cbptr = NULL;
    predictor = NULL;

    /*
     * Parse arguments
     */
    while (1)
      {
        static struct option long_options[] =
          {
            /* These options don’t set a flag.
               We distinguish them by their indices. */
            {"help",           no_argument,       0, 'h'},
            {"trace-file",     required_argument, 0, 't'},
            {"rat-size",       required_argument, 0, 'r'},
			{"g-history-size", required_argument, 0, 'g'},
            {0, 0, 0, 0}
          };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "ht:r:g:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
          break;

        switch (c)
          {
          case 0:
            /* If this option set a flag, do nothing else now. */

        	if (long_options[option_index].flag != 0)
              break;
            printf ("option %s", long_options[option_index].name);

            if (optarg)
              printf (" with arg %s", optarg);

            printf ("\n");
            break;

            // Read trace file **MANDATORY**
          case 't':
        	cbptr = new cbp_trace_reader_c (cbp_trace_reader_c(optarg));
            break;

            // Return address stack size
          case 'r':
        	sscanf(optarg, "%d", &rat_size);
        	break;

          case 'g':
        	  sscanf(optarg, "%d", &gr_size);
            break;

          default:
            abort ();
          }
      }

    predictor = new PREDICTOR(rat_size, gr_size);

	printf("---CONFIG---\n");
	printf("RAT Size: %d\n", predictor->rat.max_size);
	printf("BTB Size: %d\n", predictor->NUM_BTB_ENTRIES);

    if(NULL == cbptr)
    {
    	printf("usage: %s --trace-file=<trace> --rat-size=<value> --g-history-size=<value>\n", argv[0]);
    	exit(EXIT_FAILURE);
    }

    // read the trace, one branch at a time, placing the branch info in br
    while (cbptr->get_branch_record(&br)) {

        // ************************************************************
        // Competing predictors must have the following methods:
        // ************************************************************

        // get_prediction() returns the prediction your predictor would like to make
        bool predicted_taken = predictor->get_prediction(&br, cbptr->osptr, &targetaddress);

        // predict_branch() tells the trace reader how you have predicted the branch and target address
        bool actual_taken    = cbptr->predict_branch(predicted_taken, &targetaddress);
            
        // finally, update_predictor() is used to update your predictor with the
        // correct branch result
        predictor->update_predictor(&br, cbptr->osptr, actual_taken, targetaddress);

    }

    if (cbptr) delete cbptr;
    if (predictor) delete predictor;
}



