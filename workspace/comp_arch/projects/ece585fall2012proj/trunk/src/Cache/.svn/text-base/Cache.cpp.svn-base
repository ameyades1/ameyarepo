/*******************************************************************************
    Project: SplitL1Cache
    File: Cache.cpp
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains the implementation of the Cache Class
    Only the methods common to all derived classes are implemented. The rest
    must be implemented by the derived classes.
*******************************************************************************/

/*
** ----------------------------------------------------------------------------------
** C O M P O N E N T   I N C L U D E S
** ----------------------------------------------------------------------------------
*/
#include "Cache.h"

/*============================================================================
**
** Function Name:       InitVar
**
** Visibility:          Protected. Only to inheritors of this class
**                      THIS IS NOT A USER ENTRY POINT!
**
** Description:         This function initializes the variables. 
**
** Invocation:          User who wants do an init on the object creation
**
** Input Parameters:    None
**
** Return Values:       None
**                      
**==========================================================================*/
void CCache:: InitVar()
{
	m_num_offset_bits = 0;	
	m_num_index_bits = 0;		
	m_num_tag_bits = 0;		
    
	m_num_sets = 0;
    m_line_size = 0;		
	m_ways_per_set = 0;	
    
	m_num_sets = 0;			
    m_hits = 0;
    m_misses = 0;			
	m_hit_ratio = 0;		
	m_miss_ratio = 0;		
    
	m_num_reads = 0;			
	m_num_writes = 0;	
}

/*============================================================================
**
** Function Name:       CCache
**
** Visibility:          Public
**
** Description:         This is the default constructor. 
**
** Invocation:          On object creation
**
** Input Parameters:    None
**
** Return Values:       None
**                      
**==========================================================================*/
CCache::CCache(void)
{
	InitVar();
    m_next_mem = NULL;
}


/*============================================================================
**
** Function Name:       GetTagBits
**
** Visibility:          Public
**
** Description:         This extracts the tag bits from the given address. 
**                      Number of tag bits is m_num_tag_bits
**
** Invocation:          By the user who wants the tag bits
**
** Input Parameters:    const UINT32 address // The address
**
** Return Values:       UINT32 // The tag bits
**                      
**==========================================================================*/
UINT32 CCache::GetTagBits(const UINT32 address)
{
	return address >> (m_num_offset_bits + m_num_index_bits);
}


/*============================================================================
**
** Function Name:       GetIndexBits
**
** Visibility:          Public
**
** Description:         This extracts the index bits from the given address. 
**                      Number of index bits is m_num_index_bits
**
** Invocation:          By the user who wants the index bits
**
** Input Parameters:    const UINT32 address // The address
**
** Return Values:       UINT32 // The index bits
**                      
**==========================================================================*/
UINT32 CCache::GetIndexBits(const UINT32 address)
{
	UINT32 l_index_bits;
	UINT32 l_index_mask = -1;

	l_index_bits = address >> m_num_offset_bits;
	
	l_index_mask = l_index_mask << m_num_index_bits;
	l_index_mask = ~l_index_mask;
	
	l_index_bits &= l_index_mask;

	return l_index_bits;
}


/*============================================================================
**
** Function Name:       GetOffsetBits
**
** Visibility:          Public
**
** Description:         This extracts the offset bits from the given address. 
**                      Number of offset bits is m_num_offset_bits
**
** Invocation:          By the user who wants the offset bits
**
** Input Parameters:    const UINT32 address // The address
**
** Return Values:       UINT32 // The index bits
**                      
**==========================================================================*/
UINT32 CCache::GetOffsetBits(const UINT32 address)
{
	UINT32 l_offset_mask = -1;

	l_offset_mask = l_offset_mask << m_num_offset_bits;
	l_offset_mask = ~l_offset_mask;

	return address & l_offset_mask;

}



/*============================================================================
**
** Function Name:       GetLRU
**
** Visibility:          Public
**
** Description:         This returns the LRU for a given set. (The way number)
**
** Invocation:          By the user who wants the LRU
**
** Input Parameters:    const SET& l_set // The set from which LRU is to be known
**
** Return Values:       UINT32 // The way number which is the LRU
**                      
**==========================================================================*/
UINT32 CCache::GetLRU(const SET& l_set)
{
    UINT32 way_no = 0;
    UINT32 lru = 0;

    for(way_no = 0; way_no < m_ways_per_set; way_no++)
    {
        // Find the way which occupies largest (last) position in the array
        if( (m_ways_per_set - 1) == l_set.lru[way_no] )
        {    
            lru = way_no;
            break;
        }
    }

    return lru;
}


/*============================================================================
**
** Function Name:       UpdateLRU
**
** Visibility:          Public
**
** Description:         This updates LRU for a given set, when a given way is 
**                      accessed.
**
** Invocation:          By the user after accessing a way.
**
** Input Parameters:    const SET& l_set    // The set from which a ways is 
**                                              accessed
**                      const UINT32 l_mru  // The MRU way
**
** Return Values:       None
**                      
**==========================================================================*/
void CCache::UpdateLRU(const SET& l_set, const UINT32 l_mru)
{
    UINT32 way_no = 0;

    for(way_no = 0; way_no < m_ways_per_set; way_no++)
    {
        // For all ways that are more recently used than next (given) mru, 
        // increment their position by 1.
        if( (way_no != l_mru) && (l_set.lru[way_no] < l_set.lru[l_mru]) )
        {
            l_set.lru[way_no]++;
        }
    }

    // Assign the first position to the mru
    l_set.lru[l_mru] = 0;

}


/*============================================================================
**
** Function Name:       GetEmptyWay
**
** Visibility:          Public
**
** Description:         This returns an empty way in the set. The set is full,
**                      It returns WAY_INVALID
**
** Invocation:          By the user who wants an empty way
**
** Input Parameters:    const SET& l_set    // The set
**
** Return Values:       The empty way or WAY_INVALID
**                      
**==========================================================================*/
UINT32 CCache::GetEmptyWay(const SET& l_set)
{
    UINT32 way_no = 0;
    UINT32 empty_way = WAY_INVALID;

    for(way_no = 0; way_no < m_ways_per_set; way_no++)
    {
        if(!l_set.lines[way_no].valid)
        {
            empty_way = way_no;
            break;
        }
    }

    return empty_way;
}

/*============================================================================
**
** Function Name:       MatchTagBits
**
** Visibility:          Public
**
** Description:         This returns a way in the set for which the given tag
**                      bits matched. If they did not, it returns WAY_INVALID
**
** Invocation:          By the user who wants to match the tag bits for a set
**
** Input Parameters:    const SET& l_set    // The set
**                      const UINT32 tag    // The tag bits to match
**
** Return Values:       The the matched way or WAY_INVALID
**                      
**==========================================================================*/
UINT32 CCache::MatchTagBits(const SET& set, const UINT32 tag)
{
    UINT32 way_no = 0;
    UINT32 way_match = WAY_INVALID;

    for(way_no = 0; way_no < m_ways_per_set; way_no++)
    {
        if( (tag == set.lines[way_no].tag) && set.lines[way_no].valid)
        {
            way_match = way_no;
            break;
        }
    }

    return way_match;
}


void CCache::Reset()
{
    			
    m_hits = 0;
    m_misses = 0;			
	m_hit_ratio = 0;		
	m_miss_ratio = 0;		
    
	m_num_reads = 0;			
	m_num_writes = 0;	
}


/*============================================================================
**
** Function Name:       PrintValidLines
**
** Visibility:          Public
**
** Description:         This prints all the valid lines for a cache on the 
**                      terminal
**
** Invocation:          By the user who wants to print valid cache lines
**
** Input Parameters:    None
**
** Return Values:       None
**                      
**==========================================================================*/
void CCache::PrintValidLines()
{
    UINT32 set_no = 0;
    UINT32 way_no = 0;
    BOOL is_valid = FALSE;
	BOOL no_lines_valid = TRUE;
	
    if(m_sets)
    {
        //printf("THE VALID LINES AND STATE BITS\n");
        for(set_no = 0; set_no < m_num_sets; set_no++)
        {
            is_valid = FALSE;
            for(way_no = 0; way_no < m_ways_per_set; way_no++)
            {
                if(m_sets[set_no].lines[way_no].valid)
                {
                    is_valid = TRUE;
					no_lines_valid = FALSE;
                    printf("SET NO: %lu \t WAY NO: %lu \t POS: %lu \n",
                        set_no, way_no, m_sets[set_no].lru[way_no]);

                }
                if(is_valid && (way_no == m_ways_per_set - 1))
                    printf("------------------------------------------\n");
					            
			}
        }
		if(no_lines_valid)
		{
			printf("\nNO VALID LINES IN THIS CACHE\n");
		}

    }
}

CCache::~CCache(void)
{
}
