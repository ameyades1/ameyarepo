/*******************************************************************************
    Project: SplitL1Cache
    File: CacheL2.cpp
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains the definition of the Cache Class
    This implements the CCache interface minimally i.e. a stub
*******************************************************************************/

/*
** ----------------------------------------------------------------------------------
** C O M P O N E N T   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include "CacheL2.h"


CCacheL2::CCacheL2(void)
{
    pPrevL1D = NULL;
    pPrevL1I = NULL;
}


CCacheL2::~CCacheL2(void)
{
}

void CCacheL2::Reset()
{
}

/*============================================================================
**
** Function Name:       Write   
**
** Visibility:          Public
**
** Description:         This function writes to the L2 cache. 
**
** Invocation:          User who wants wants to write data into L2 Cache
**
** Input Parameters:    const UINT32 address, const UINT8 data
**
** Return Values:       CACHE_HM  // Hit or miss
**                      
**==========================================================================*/
CACHE_HM CCacheL2::Write(const UINT32 address, const UINT8 data)
{
    CACHE_HM hm = CACHE_HIT;
    return hm;
}


/*============================================================================
**
** Function Name:       Read   
**
** Visibility:          Public
**
** Description:         This function reads data from to the L2 cache. 
**
** Invocation:          User who wants wants to read data from L2 Cache
**
** Input Parameters:    const UINT32 address
**
** Return Values:       UINT8 data
**                      
**==========================================================================*/
UINT8 CCacheL2::Read(const UINT32 address)
{
    return (address >> 24);
}


/*============================================================================
**
** Function Name:       Invalidate   
**
** Visibility:          Public
**
** Description:         This function invalidates specified 
**                      data from to the L2 cache, and its upper level cache. 
**
** Invocation:          User who wants wants invalidate data from L2 Cache
**
** Input Parameters:    const UINT32 address
**
** Return Values:       BOOL // True if successful i.e. data existed in cache
**                           // False otherwise
**                      
**==========================================================================*/
BOOL CCacheL2::Invalidate(const UINT32 address)
{
    if(pPrevL1D)
        pPrevL1D->Invalidate(address);

    if(pPrevL1I)
        pPrevL1I->Invalidate(address);

    return TRUE;
}

