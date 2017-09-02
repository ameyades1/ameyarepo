/*******************************************************************************
    Project: SplitL1Cache
    File: CacheWriteThru.h
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains the definition of the CacheWriteThrough Class
 
*******************************************************************************/

#ifndef _CACHE_WRITETHROUGH_H
#define _CACHE_WRITETHROUGH_H

/*
** ----------------------------------------------------------------------------------
** C O M P O N E N T   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include "../Cache/Cache.h"

class CCacheWriteThru :
	public CCache
{
	
public:
	CCacheWriteThru(void);
	void InitMem();
    virtual void Reset();
	virtual BOOL Invalidate(const UINT32 address);
	~CCacheWriteThru(void);
    virtual CACHE_HM Write(const UINT32 address, const UINT8 data);
	
	virtual UINT8 Read(const UINT32 address);

    virtual void SetPrevMem(CCache* pL1I, CCache* pL1D)
    {
        pPrevL1I = pL1I;
        pPrevL1D = pL1D;
    }

};

#endif
