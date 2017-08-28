/*******************************************************************************
    Project: SplitL1Cache
    File: Trace.h
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains the definition of the Trace Class
    It also exposes the valid trace commands for the user to update 
*******************************************************************************/

#ifndef _TRACE_H_
#define _TRACE_H_

/*
** ----------------------------------------------------------------------------------
** S Y S T E M   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include <iostream>
#include <fstream>
#include <string>


/*
** ----------------------------------------------------------------------------------
** C O M P O N E N T   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include "types.h"


//#include "CacheWriteThru.h"
#include "Cache.h"
#include "Trace_Cmds.h"


/*
** ----------------------------------------------------------------------------------
** T Y P E   D E F I N I T I O N S
** ----------------------------------------------------------------------------------
*/
// Type definition of a function pointer 
typedef BOOL (*TRACE_CMD_ACT)(const TRACE_CMD&, CCache*, CCache*, CCache*);


/*
** This structure maps enumerated command to the action it performs
*/
typedef struct _trace_cmd_fn
{
    CMD_TYPE        cmd;
    TRACE_CMD_ACT   action;

}TRACE_CMD_FN;


// This conditional compilation will ensure that the command array 
// is included in Trace.cpp only. This array is included here, since
// this header file is the only public interface to Class Trace
#ifdef _TRACE_CPP

/*
** This array consists of the commands and their actions.
** To add any command, first create an enum in types.h and
** define the function in Trace_Cmds.cpp. / .h Lastly, add 
** those in the array below.
*/
TRACE_CMD_FN trace_commands[] = {

    // Command          // Action
    {CMD_READ_DATA_L1,  cmd_read},
    {CMD_WRITE_DATA_L1, cmd_write},
    {CMD_INSTR_FETCH,   cmd_inst_fetch},
    {CMD_INVALIDATE,    cmd_invalidate},
    {CMD_CLR_RST,       cmd_clr_rst},
    {CMD_PRINT_STATS,   cmd_print_stats}

};

// The total number of commands
#define NUM_TRACE_COMMAND_TYPES (sizeof(trace_commands) / sizeof(trace_commands[0]))
#endif

class CTrace
{
private:
    // The file name of the trace file
	std::string m_fname;

    // The input stream object for the trace file
	std::ifstream trace_file;

public:
	// Default constructor
    CTrace(void);

    // Parametrized copy constructor
	CTrace(const char*);
	
    // Virtual destructor
    virtual ~CTrace(void);
	
    // Open the trace file
    BOOL Open(const char *);

    // Get the next trace command from the file
	BOOL GetNextTrace(TRACE_CMD&);
    
    // Execute the given command
    BOOL ExecuteCmd(const TRACE_CMD&, CCache*, CCache*, CCache*);

};

#endif