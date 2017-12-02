/*******************************************************************************
    Project: SplitL1Cache
    File: main.cpp
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This file integrates all modules of the SplitL1Cache project. Reads traces
    from a trace file using command line arguments, executes those commands
    and prints those results.
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
#include "Others\types.h"
#include "Config\Config.h"
#include "CacheWriteThru\CacheWriteThru.h"
#include "L2\CacheL2.h"
#include "Others\MemoryLeaks.h"
#include "Trace\Trace.h"


void InitCache(CCache* pCache, UINT32 n_sets, UINT32 n_ways, UINT32 n_line_size);

int main(int argc, char* argv[])
{
	
	CTrace* pftrace = new CTrace;
	// Accept the first command line arg as trace file name
    if(argv[1])
	{
        if(!pftrace->Open(argv[1]))
        {
            std::cout << "Cannot open the trace file!";
            return 0;
        }
	}
    else
    {
        std::cout << "Please specify a trace file..." << std::endl;
        return 0;
    }
	
	// File read successfully
	std::cout << "File read successfully..." << std::endl;
	std::cout << "Processing File..." << std::endl;

    // Create and initialize L1 Instruction Cache
    CCacheWriteThru* pCacheL1Inst = new CCacheWriteThru;
    InitCache(pCacheL1Inst,CACHE_L1I_NUM_SETS,CACHE_L1I_WAYS_PER_SET,
                CACHE_L1I_LINE_SIZE);
    pCacheL1Inst->SetPrevMem(NULL,NULL);
    pCacheL1Inst->InitMem();

    // Create and initialize L1 Data Cache
	CCacheWriteThru* pCacheL1Data = new CCacheWriteThru;
    InitCache(pCacheL1Data,CACHE_L1D_NUM_SETS,CACHE_L1D_WAYS_PER_SET,
                 CACHE_L1D_LINE_SIZE);
    pCacheL1Data->SetPrevMem(NULL,NULL);
    pCacheL1Data->InitMem();

    // Create and initialize L2 Cache stub
    CCacheL2* pCacheL2 = new CCacheL2;

    // Interface L2 as next level of memory hierarchy
    pCacheL1Data->SetNextMem(pCacheL2);
    pCacheL1Inst->SetNextMem(pCacheL2);

    // Interface L1I and L1D as previous level memory hierarchy
    pCacheL2->SetPrevMem(dynamic_cast<CCache*>(pCacheL1Inst), 
                         dynamic_cast<CCache*>(pCacheL1Data));

    // Grab commands from the trace file
    TRACE_CMD trace;
    while( pftrace->GetNextTrace(trace) )
	{
        // Only execute valid commands
        if(!pftrace->ExecuteCmd(trace,pCacheL1Data,pCacheL1Inst, pCacheL2))
            std::cout << std::endl << "#### Bad Command ####" << std:: endl;
	}
    
    // Once we finish reading the trace file, print all stats
	trace.command = CMD_PRINT_STATS;
    pftrace->ExecuteCmd(trace,dynamic_cast<CCache*>(pCacheL1Data), 
        dynamic_cast<CCache*>(pCacheL1Inst), dynamic_cast<CCache*>(pCacheL2));

    // Cleanup
    delete pCacheL2;
	delete pCacheL1Data;
    delete pCacheL1Inst;
    delete pftrace;

	_SHOW_MEM_LEAK();
	return 0;
}

void InitCache(CCache* pCache, UINT32 n_sets, UINT32 n_ways, UINT32 n_line_size)
{
    if(pCache)
    {
        pCache->SetLineSize(n_line_size);
        pCache->SetWaysPerLine(n_ways);
        pCache->SetNumSets(n_sets);
    }

}
