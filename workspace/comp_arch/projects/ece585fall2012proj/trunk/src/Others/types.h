/*******************************************************************************
    Project: SplitL1Cache
    File: types.h
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the master type definitions file.
*******************************************************************************/

#ifndef _TYPES_H_
#define _TYPES_H_

/*
** ----------------------------------------------------------------------------------
** S Y S T E M   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include <iostream> // To get the definition of 'NULL', although we could have
                    // written our own



/* 
** The primitive types. By defining these, we achieve portability, since the C 
** standard does not define actual byte sizes of the types.
*/

typedef unsigned char		UINT8;	// Unsigned 8 bit number
typedef signed char			INT8;	// Signed 8 bit number

typedef unsigned short int	UINT16;	// Unsigned 16 bit number
typedef signed short int	INT16;	// Signed 16 bit number

typedef unsigned long		UINT32;	// Unsigned 32 bit number
typedef signed long			INT32;	// Signed 32 bit number

typedef unsigned char		BOOL;	// Boolean

typedef float				FLOAT;	// Single precision floating point number
typedef double				DOUBLE;	// Double precision floating point number


/*
** For use in BOOL as TRUE or FALSE
*/
#ifndef TRUE
#define TRUE	(1)
#endif

#ifndef FALSE
#define FALSE	(0)
#endif


// The invalid ways and tags
#define WAY_INVALID (0xFFFFFFFFUL)
#define TAG_INVALID (0xFFFFFFFFUL)

typedef enum _cache_hm
{
    CACHE_HIT,
    CACHE_MISS

}CACHE_HM;

/*
** This enum defines the command types. Make sure that the command 
** number matches here.
*/
typedef enum _cmd_type_
{
    //Read from L1 Data Cache
	CMD_READ_DATA_L1	= 0,
	
    //Read from L1 Instruction Cache
    CMD_WRITE_DATA_L1	= 1,
	
    // Instruction fectch (Read from L1 Instruction cache
    CMD_INSTR_FETCH		= 2, 
	
    // Invalidate 
    CMD_INVALIDATE		= 3,
	
    // Reset all caches
    CMD_CLR_RST			= 8,
	
    // Print stats for all caches
    CMD_PRINT_STATS		= 9,
	
    // Keep this last one for the max command count
    CMD_MAX_COUNT

}CMD_TYPE;


// The command structure 
typedef struct _trace_cmd
{
	UINT32 address;
	CMD_TYPE command;

}TRACE_CMD;


// The stucture of a line
typedef struct line 
{
	UINT8*	line_data;
	UINT32	tag;
	BOOL	valid;
	
	line()
	{
		line_data = NULL;
		tag = 0;
		valid = FALSE;
	}
    
	~line()
	{
		if(line_data)
			delete[] line_data;
	}

} LINE;


// The structure of a set
typedef struct set
{
	LINE*	lines;
	UINT32*	lru;

	set()
	{
		lines = NULL;
		lru = NULL;
	}

	~set()
	{
		if(lines)
			delete[] lines;

		if(lru)
			delete[] lru;
	}

} SET;

#endif