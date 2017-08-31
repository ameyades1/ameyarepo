/*******************************************************************************
    Project: SplitL1Cache
    File: Trace_Cmds.h
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This file contains trace command interfaces. You may add your own here.
    Make sure you update the array in Trace.h and provide an implementation in
    Trace_Cmds.cpp
*******************************************************************************/
#ifndef _TRACE_CMDS_H_
#define _TRACE_CMDS_H_

/*
** ----------------------------------------------------------------------------------
** C O M P O N E N T   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include "types.h"
#include "Cache.h"


/*
** The interface of command contains 3 pointers to L1D, L1I and L2.
*/

BOOL cmd_invalidate(const TRACE_CMD& , CCache*, CCache*, CCache*);

BOOL cmd_read(const TRACE_CMD& , CCache*, CCache*, CCache*);

BOOL cmd_write(const TRACE_CMD& , CCache*, CCache*, CCache*);

BOOL cmd_inst_fetch(const TRACE_CMD& , CCache*, CCache*, CCache*);

BOOL cmd_clr_rst(const TRACE_CMD& , CCache*, CCache*, CCache*);

BOOL cmd_print_stats(const TRACE_CMD& , CCache*, CCache*, CCache*);

#endif