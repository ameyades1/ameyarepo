/*******************************************************************************
    Project: SplitL1Cache
    File: Config.h
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    Master configuration file. Update parameters as necessary.
*******************************************************************************/

#ifndef _CACHE_CONFIG_H
#define _CACHE_CONFIG_H

// L1 Data cache line size in bytes
#define CACHE_L1D_LINE_SIZE     (64)

// L1 Data cache number of sets
#define CACHE_L1D_NUM_SETS      (16384)

// L1 Data cache ways per set
#define CACHE_L1D_WAYS_PER_SET  (4)


// L1 Instruction cache line size in bytes
#define CACHE_L1I_LINE_SIZE     (64)

// L1 Instruction cache number of sets
#define CACHE_L1I_NUM_SETS      (16384)

// L1 Instruction cache ways per set
#define CACHE_L1I_WAYS_PER_SET  (2)

#endif