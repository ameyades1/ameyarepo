/*******************************************************************************
    Project: SplitL1Cache
    File: Cache.h
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains the definition of the Cache Class
    This is an abstact class, providing a common interface for 
    other "Caches" to implement. This serves as a common interface for caches to
    interact with each other.
*******************************************************************************/
#ifndef _CACHE_H_
#define _CACHE_H_

/*
** ----------------------------------------------------------------------------------
** S Y S T E M   I N C L U D E S
** ----------------------------------------------------------------------------------
*/

#include <cmath>
#include <cstdio>

/*
** ----------------------------------------------------------------------------------
** C O M P O N E N T   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include "../Others/types.h"
#include "../Config/Config.h"


class CCache
{

protected:
	UINT8	m_num_offset_bits;	// Number of offset bits
	UINT16	m_num_index_bits;	// Number of index bits
	UINT16	m_num_tag_bits;		// Number of tag bits

	UINT32	m_line_size;		// Line size in bytes
	UINT32	m_ways_per_set;	    // Number of ways per set
	UINT32	m_num_sets;		    // Number of sets

	UINT32	m_hits;			    // Number of cache hits after reset
	UINT32	m_misses;			// Number of cache misses after reset
	DOUBLE	m_hit_ratio;		// Cache hit ratio after reset
	DOUBLE	m_miss_ratio;		// Cache miss ratio after reset

	UINT32	m_num_reads;		// Number of reads after reset
	UINT32	m_num_writes;		// Number of writes after reset

    CCache* m_next_mem;         // Pointer to next level of cache
    CCache* pPrevL1I;           // Pointer to previous level caches
    CCache* pPrevL1D;

    SET * m_sets;               // The pointer to the sets memory
    
 public:
    CCache(void);
	virtual ~CCache(void);
	
    // The public interface each derieving class must implement
    virtual void Reset() = 0;
	virtual BOOL Invalidate(const UINT32 address) = 0;
    virtual CACHE_HM Write(const UINT32 address, const UINT8 data) = 0;
	virtual UINT8 Read(const UINT32 address) = 0;
    
    // These set the previous cache memory hierarchy
    virtual void SetPrevMem(CCache* pL1I, CCache* pL1D) = 0;
    
    // This sets the next memory hierarchy   
    void SetNextMem(CCache* next_mem)
    {
        m_next_mem = next_mem;
    }

    // Displays all the valid lines on the terminal
    void PrintValidLines();

protected:
    // The init variables
    virtual void InitVar();
    
    // Get the Least Recently Used Way for a given set
    UINT32 GetLRU(const SET& l_set);

    // Update the LRU, for a given set, when a given way is accessed
    void UpdateLRU(const SET& l_set, const UINT32 l_mru);
    
    // Extract the tag, index and offset bits from the address
    UINT32 GetTagBits(const UINT32 address);
    UINT32 GetIndexBits(const UINT32 address);
	UINT32 GetOffsetBits(const UINT32 address);
    
    // Find an empty way in the given set
    UINT32 GetEmptyWay(const SET&);
    
    // Find a way in the given set for which the given tagbits match
    UINT32 MatchTagBits(const SET&, const UINT32 tag);
    
    // Compute the number tag, index and offset bits for the given number of sets, ways per set, and line size
    void CalcBits()
	{
		m_num_offset_bits = (UINT8)ceil((DOUBLE)((DOUBLE)log10((DOUBLE)CACHE_L1D_LINE_SIZE) / (DOUBLE)log10 ((DOUBLE)2)));
		m_num_index_bits = (UINT16)ceil((DOUBLE)((DOUBLE)log10((DOUBLE)CACHE_L1D_NUM_SETS) / (DOUBLE)log10 ((DOUBLE)2)));
		m_num_tag_bits =  8 * sizeof(UINT32) - m_num_index_bits - m_num_offset_bits;
	}

public:
    // The getters and setters 
	void SetLineSize(UINT32 l_line_size)
	{
		m_line_size = l_line_size;
	}

	void SetWaysPerLine(UINT32 l_ways)
	{
		m_ways_per_set = l_ways;
	}

	void SetNumSets(UINT32 l_sets)
	{
		m_num_sets = l_sets;
	}

    // Compute and return the hit ratio
    DOUBLE GetHitRatio()
    {
        // Divide by zero check
        if ((m_hits + m_misses) == 0)
            m_hit_ratio = 0;
        else
            m_hit_ratio =  ((DOUBLE) ((DOUBLE)m_hits / (DOUBLE)(m_hits + m_misses)));
        return m_hit_ratio;
    }

    // Compute and return the miss ratio
    DOUBLE GetMissRatio()
    {
        // Divide by zero check
        if ((m_hits + m_misses) == 0)
            m_miss_ratio = 0;
        else
            m_miss_ratio = (DOUBLE)((DOUBLE)m_misses / (DOUBLE)(m_hits + m_misses));
        return m_miss_ratio;
    }

    UINT32 GetHits()
    {
        return m_hits;
    }

    UINT32 GetMisses()
    {
        return m_misses;
    }

    UINT32 GetReads()
    {
        return m_num_reads;
    }

    UINT32 GetWrites()
    {
        return m_num_writes;
    }
};

#endif
