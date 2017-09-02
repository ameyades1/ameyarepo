/*******************************************************************************
    Project: SplitL1Cache
    File: Trace.cpp
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains the implementation of the Trace Class
*******************************************************************************/

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
#define _TRACE_CPP
#include "Trace.h"

//#define __debug__

using namespace std;


CTrace::CTrace(void)
{

}

CTrace::CTrace(const char* fname)
{
	if(fname)
	{
		m_fname = fname;
		trace_file.open(m_fname.c_str());
	}
}


/*============================================================================
**
** Function Name:       Open
**
** Visibility:          Public
**
** Description:         This function opens the spcefied file. 
**
** Invocation:          User who wants to open a trace file
**
** Input Parameters:    const char* fname // The file to be opened
**
** Return Values:       BOOL TRUE if open suceeds, FALSE otherwise
**                      
**==========================================================================*/
BOOL CTrace::Open(const char* fname)
{
    BOOL status = FALSE;
    if(fname)
    {
        // Copy constructor for string class exists!
        if(!m_fname.empty())
            m_fname.clear();
        m_fname = fname;    
		
        trace_file.open(m_fname.c_str());

        // Check if we really opened the file
        if( trace_file.is_open() )
            status = TRUE;
        else
            status = FALSE;
    }
    else
    {
        status = FALSE;
    }

    return status;
}

CTrace::~CTrace(void)
{
}

/*============================================================================
**
** Function Name:       GetNextTrace
**
** Visibility:          Public
**
** Description:         This function returns opens the spcefied file. 
**
** Invocation:          User who wants to get the next trace from an 
**                      already opened file
**
** Input Parameters:    TRACE_CMD& info // The trace to which is upadted
**
** Return Values:       BOOL TRUE if we get a trace, FALSE otherwise (at EOF)
**                      TRACE_CMD& info // The trace to which is upadted
**                      
**==========================================================================*/
BOOL CTrace::GetNextTrace(TRACE_CMD& info)
{
	BOOL status = FALSE;
	string line;
	BOOL line_exist = FALSE;

	//Check if file has been opened
	if(trace_file.is_open() && !trace_file.eof())
	{
		getline(trace_file, line, '\n');
		if("" == line)
		{
			while(!trace_file.eof() && "" == line)
				getline(trace_file, line, '\n');
			
			//Check if the latest line extracted is blank or not
			if("" == line)
				line_exist = FALSE;
			else
				line_exist = TRUE;
		}
		else
		{
			line_exist = TRUE;
		}

		if(!line_exist)
		{
			status = FALSE;
		}
		else
		{
			std::sscanf(line.c_str(),"%d %lu",&info.command, &info.address);
			status = TRUE;
		}
		
#ifdef __debug__
		cout << "Command = " << info.command << "   Address = " << hex << info.address << endl;
#endif
		
	}
	else
	{
		status = FALSE;
	}
	return status;
}


/*============================================================================
**
** Function Name:       ExecuteCmd
**
** Visibility:          Public
**
** Description:         This function executes the specified trace command.
**
** Invocation:          User who wants to execute a trace command
**
** Input Parameters:    const TRACE_CMD& cmd // The trace command
**                      CCache* pL1D         // Pointer to L1 Data cache
**                      CCache* pL1I         // Pointer to L1 Inst cache
**                      CCache* pL2          // Pointer to L2 cache
**
** Return Values:       BOOL TRUE if the command is executed successfully
**                      FALSE otherwise
**                      
**==========================================================================*/
BOOL CTrace::ExecuteCmd(const TRACE_CMD& cmd, CCache* pL1D, CCache* pL1I, 
                        CCache* pL2)
{
    UINT32 cmd_no = 0;
    BOOL status = FALSE;

    // Arguement Check
    if(cmd.command >= CMD_MAX_COUNT || NULL == pL1D || NULL == pL1I || NULL == pL2)
        status = FALSE;
    else
    {
        // If all args are OK, decode the command, get the function
        for(cmd_no = 0; cmd_no < NUM_TRACE_COMMAND_TYPES; cmd_no++)
        {
            if(trace_commands[cmd_no].cmd == cmd.command)
            {
                if(trace_commands[cmd_no].action)
                {   
                    // Execute the command
                    status = trace_commands[cmd_no].action(cmd, pL1D, pL1I, pL2);
                    break;
                }
            }

        } // for(cmd_no...) 
    }

    return status;
}
