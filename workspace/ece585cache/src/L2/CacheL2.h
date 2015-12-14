/*******************************************************************************
    Project: SplitL1Cache
    File: CacheL2.h
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains the definition of the Cache Class
    This implements the CCache interface minimally i.e. a stub
*******************************************************************************/
#ifndef _CCACHE_L2_H
#define _CCACHE_L2_H

/*
** ----------------------------------------------------------------------------------
** C O M P O N E N T   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include "../Cache/Cache.h"


class CCacheL2 :
    public CCache
{
public:
    CCacheL2(void);
    virtual ~CCacheL2(void);

    virtual void Reset();
    virtual CACHE_HM Write(const UINT32 address, const UINT8 data);
	virtual UINT8 Read(const UINT32 address); 
    virtual BOOL Invalidate(const UINT32 address);

    void SetPrevMem(CCache* pL1I, CCache* pL1D)
    {
        pPrevL1D = pL1D;
        pPrevL1I = pL1I;
    }

};

#endif
