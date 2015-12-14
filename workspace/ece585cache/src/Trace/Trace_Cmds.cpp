/*******************************************************************************
    Project: SplitL1Cache
    File: Trace_Cmds.cpp
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains the implementation of trace commands. 
*******************************************************************************/

/*
** ----------------------------------------------------------------------------------
** S Y S T E M   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include <iostream>

/*
** ----------------------------------------------------------------------------------
** C O M P O N E N T   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include "Trace_Cmds.h"



/*============================================================================
**
** Command Name:        Invalidate   
**
** Description:         Invalidates specified data from lowermost cache.
**                      
**==========================================================================*/
BOOL cmd_invalidate(const TRACE_CMD& cmd, CCache* pL1D, CCache* pL1I, CCache* pL2)
{
    BOOL status = TRUE;

    if(cmd.command >= CMD_MAX_COUNT || NULL == pL1D || NULL == pL1I || NULL == pL2)
        status = FALSE;
    else
        pL2->Invalidate(cmd.address);

    return status;
}


/*============================================================================
**
** Command Name:        Read   
**
** Description:         Reads specified data from L1 Data cache.
**                      
**==========================================================================*/

BOOL cmd_read(const TRACE_CMD& cmd, CCache* pL1D, CCache* pL1I, CCache* pL2)
{
    BOOL status = TRUE;

    if(cmd.command >= CMD_MAX_COUNT || NULL == pL1D || NULL == pL1I || NULL == pL2)
        status = FALSE;

    else
    {
        pL1D->Read(cmd.address);
    }

    return status;
}


/*============================================================================
**
** Command Name:        Write   
**
** Description:         Writes specified data to L1 Data cache.
**                      
**==========================================================================*/
BOOL cmd_write(const TRACE_CMD& cmd, CCache* pL1D, CCache* pL1I, CCache* pL2)
{
    BOOL status = TRUE;

    if(cmd.command >= CMD_MAX_COUNT || NULL == pL1D || NULL == pL1I || NULL == pL2)
        status = FALSE;
    else
    {
        pL1D->Write(cmd.address, 0xCC);
    }

    return status;
}


/*============================================================================
**
** Command Name:        Instruction fetch   
**
** Description:         Reads specified data (instruction) from L1 Instruction 
**                      cache.
**                      
**==========================================================================*/
BOOL cmd_inst_fetch(const TRACE_CMD& cmd, CCache* pL1D, CCache* pL1I, CCache* pL2)
{
    BOOL status = TRUE;

    if(cmd.command >= CMD_MAX_COUNT || NULL == pL1D || NULL == pL1I || NULL == pL2)
        status = FALSE;
    else
    {
        pL1I->Read(cmd.address);
    }

    return status;
}


/*============================================================================
**
** Command Name:        Clear and Reset   
**
** Description:         Clears the contents of the L1 Instruction and data 
**                      cache and resets it state.
**                      
**==========================================================================*/
BOOL cmd_clr_rst(const TRACE_CMD& cmd, CCache* pL1D, CCache* pL1I, CCache* pL2)
{
    BOOL status = TRUE;

    if(cmd.command >= CMD_MAX_COUNT || NULL == pL1D || NULL == pL1I || NULL == pL2)
        status = FALSE;
    else
    {
        pL1D->Reset();
        pL1I->Reset();
    }

    return status;
}


/*============================================================================
**
** Command Name:        Print stats
**
** Description:         Prints all valid way status, and cache hit miss ratios
**                      
**==========================================================================*/
BOOL cmd_print_stats(const TRACE_CMD& cmd, CCache* pL1D, CCache* pL1I, CCache* pL2)
{
    BOOL status = TRUE;

    if(cmd.command >= CMD_MAX_COUNT || NULL == pL1D || NULL == pL1I || NULL == pL2)
        status = FALSE;
    else
    {
        std::cout << "--------------STATS CENTRAL--------------\n" << std::endl;

	//	std::cout << "Valid Lines for L1 Data cache:" << std::endl;
    //    pL1D->PrintValidLines();
	//	std::cout << "==========================================" << std::endl;
        
    //    std::cout << "Valid Lines for L1 Instruction cache:" << std::endl;
    //    pL1I->PrintValidLines();
	//	std::cout << "\n==========================================" << std::endl;

        std::cout << "Number of L1 Data Cache Reads \t= " << std::dec << pL1D->GetReads() << std::endl;
        std::cout << "Number of L1 Data Cache Writes \t= " << std::dec << pL1D->GetWrites() << std::endl;
        std::cout << "Number of L1 Data Cache Hits \t= " << std::dec << pL1D->GetHits() << std::endl;
        std::cout << "Number of L1 Data Cache Misses \t= " << std::dec << pL1D->GetMisses() << std::endl;
        std::cout << "L1 Data Cache Hit Ratio \t= " << std::dec << pL1D->GetHitRatio() << std::endl;

        std::cout << std::endl << "Number of L1 Instruction Cache Reads \t= " << std::dec << pL1I->GetReads() << std::endl;
        std::cout << "Number of L1 Instruction Cache Writes \t= " << std::dec << pL1I->GetWrites() << std::endl;
        std::cout << "Number of L1 Instruction Cache Hits \t= " << std::dec << pL1I->GetHits() << std::endl;
        std::cout << "Number of L1 Instruction Cache Misses \t= " << std::dec << pL1I->GetMisses() << std::endl;
        std::cout << "L1 Instruction Cache Hit Ratio \t\t= " << std::dec << pL1I->GetHitRatio() << std::endl;
		 

    }

    return status;
}

