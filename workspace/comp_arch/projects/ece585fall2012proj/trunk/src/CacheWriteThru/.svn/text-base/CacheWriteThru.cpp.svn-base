/*******************************************************************************
    Project: SplitL1Cache
    File: CacheWriteThru.h
    Revision: 1.0
    Date & Time: 09/15/2012

    Description:
    This is the file contains implements the CacheWriteThrough Class
 
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
#include "CacheWriteThru.h"
#include "MemoryLeaks.h"


//#define __debug__

CCacheWriteThru::CCacheWriteThru(void)
{
	m_sets = NULL;
}



/*============================================================================
**
** Function Name:       InitMem
**
** Visibility:          Public
**
** Description:         This function allocates memory for the sets, line data
**
** Invocation:          Once after specifying sets, line size.
**
** Input Parameters:    None
**
** Return Values:       None
**                      
**==========================================================================*/
void CCacheWriteThru::InitMem()
{
	UINT32 set_no;
	UINT32 way_no;

	CCache::CalcBits();

	// Delete any previously allocated memory
	if(m_sets)
	{
		delete[] m_sets;
		m_sets = NULL;
	}

    // Try your luck when allocating such big memory
	try
	{
		// Allocate all sets
        m_sets = new SET[m_num_sets];
	             
		for(set_no = 0; set_no < m_num_sets; set_no++)
		{
			// For each set, allocate all lines
            m_sets[set_no].lines = new LINE[m_ways_per_set];

            // Allocate line data for each line
			for(way_no = 0; way_no < m_ways_per_set; way_no++)
			{
				m_sets[set_no].lines[way_no].line_data = new UINT8[m_line_size];
			}

            // Allocate the LRU array
			m_sets[set_no].lru = new UINT32[m_ways_per_set];
            
            // Init the LRU array so that all lines are LRUs
            for(way_no = 0; way_no < m_ways_per_set; way_no++)
            {
                m_sets[set_no].lru[way_no] = m_ways_per_set - 1;
                m_sets[set_no].lines[way_no].valid = 0;
                m_sets[set_no].lines[way_no].tag = 0;
            }



		} // for(set_no...)

	} // try
    // Catch a bad alloc exception
	catch(std::bad_alloc) 
    {
        std::cout << "Memory Allocation Failed!\n";
    }
}



/*============================================================================
**
** Function Name:       Write
**
** Visibility:          Public
**
** Description:         Write data into the cache. Writes through to second 
**                      level memory to maintain inclusivity. On a miss, 
**                      identifies LRU and evicts the data prior to reading data 
**                      from next lower level memory
**
** Invocation:          By the CPU or adjecent memory hierarchy.
**
** Input Parameters:    const UINT32 address, const UINT8 data
**
** Return Values:       CACHE_HM // Cache hit or miss info
**                      
**==========================================================================*/
CACHE_HM CCacheWriteThru::Write(const UINT32 address, const UINT8 data)
{
    CACHE_HM hm_type = CACHE_HIT;

    // Separate Tag, index, offset bits
    UINT32 offset = GetOffsetBits(address);
    UINT32 index = GetIndexBits(address);
    UINT32 tag = GetTagBits(address);
    
    UINT32 way_to_write = WAY_INVALID;
    
    // Starting address of a line. 
    // Useful for reading a line from next memory hierarchy.
    UINT32 line_start_add;

#ifdef __debug__
    std::cout << std::endl << "--------------------------------------------------------" << std::endl;
    std::cout << " Address =  " << std::hex << address << " Data = " << data << std::dec << " Set No = " << index << std::endl;
#endif
    // Make sure sets exists
    if(m_sets)
    {
        // All is well
        way_to_write = MatchTagBits(m_sets[index], tag);
            
        if(WAY_INVALID != way_to_write)
        {
            // Cache write hit
            // Do nothing
            m_hits++;
            hm_type = CACHE_HIT;
#ifdef __debug__
std::cout << "Cache Hit. " << " Way to write = " << way_to_write << std::endl;         
#endif
        }
        else
        {
            UINT32 empty_way = GetEmptyWay(m_sets[index]);
            if(empty_way != WAY_INVALID)
            {
                // The set is not full
                m_misses++;
                hm_type = CACHE_MISS;
                way_to_write = empty_way;

#ifdef __debug__
    std::cout << "Cache miss. Set not full. " << " Way to write = " << way_to_write << std::endl;         
#endif
            }
            else
            {
                // The set is full
                // Cache write miss
                m_misses++;
                hm_type = CACHE_MISS;

                UINT32 way_lru = GetLRU(m_sets[index]);
                
                way_to_write = way_lru;
        

            }// if(WAY_INVALID == way_to_write)

            // Need to read new cache line from L2. Common to compuslory and confilct misses
            line_start_add = (m_sets[index].lines[way_to_write].tag << (m_num_offset_bits + m_num_index_bits)) |
                                        (index << m_num_offset_bits);

            for(UINT32 item_offset = 0; item_offset < m_line_size; item_offset++)
            {
                m_sets[index].lines[way_to_write].line_data[item_offset] = m_next_mem->Read(line_start_add + item_offset);
            }

        }

        m_sets[index].lines[way_to_write].line_data[offset] = data;

        // Need to write to next memeory hierarchy (L2) to maintain inclusivity

        line_start_add = (m_sets[index].lines[way_to_write].tag << (m_num_offset_bits + m_num_index_bits)) |
                                    (index << m_num_offset_bits);

        // No need to write the whole line, since we write only one byte at time.
        m_next_mem->Write(address, data);
      
        m_sets[index].lines[way_to_write].valid = 1;
        m_sets[index].lines[way_to_write].tag = tag;

        m_num_writes++;

        UpdateLRU(m_sets[index],way_to_write);
#ifdef __debug__
        std::cout << "Stats: Total Reads = " << m_num_reads << " Total Writes = " << m_num_writes << std::endl;         
        std::cout << "Stats: Total Hits = " << m_hits << " Total Misses = " << m_misses << std::endl;
        for(UINT32 item_offset = 0; item_offset < m_line_size; item_offset++)
        {
            printf("\n Line data %d = %x ", item_offset, m_sets[index].lines[way_to_write].line_data[item_offset]);
        }
#endif


    }
    else
    {
        // Sets not allocated!! SERIOUS ERROR!!!
        hm_type = hm_type;
    }

    return hm_type;

}


/*============================================================================
**
** Function Name:       Read
**
** Visibility:          Public
**
** Description:         Read data from the cache. On a miss, 
**                      identifies LRU and evicts the data prior to reading data 
**                      from next lower level memory.
**
** Invocation:          By the CPU of adjecent memory hierarchy.
**
** Input Parameters:    const UINT32 address, 
**
** Return Values:       UINT8 data
**                      
**==========================================================================*/
UINT8 CCacheWriteThru::Read(const UINT32 address)
{
	// Separate tag, index and offset bits
    UINT32 offset = GetOffsetBits(address);
    UINT32 index = GetIndexBits(address);
    UINT32 tag = GetTagBits(address);
    
    UINT32 way_to_read = WAY_INVALID;
	
    // The byte to be returned
    UINT8 data = 0xFF;
    
    // Starting address of a line. 
    // Useful for reading a line from next memory hierarchy.
    UINT32 line_start_add;

#ifdef __debug__
    std::cout << std::endl << "--------------------------------------------------------" << std::endl;
    std::cout << " Address =  " << std::hex << address << std::dec << " Set No = " << index << std::endl;
#endif

	// Make sure sets exists
    if(m_sets)
    {
        // All is well
        way_to_read = MatchTagBits(m_sets[index], tag);

		if(WAY_INVALID != way_to_read)
        {
            // Cache Read hit. Yay!
            // Do nothing
            m_hits++;

#ifdef __debug__
std::cout << "Cache Read Hit. " << " Way to read = " << way_to_read << std::endl;         
#endif
        }
        else
        {
			UINT32 empty_way = GetEmptyWay(m_sets[index]);
            if(empty_way != WAY_INVALID)
            {
                // The set is not full, an empty way has been found
                m_misses++;
                way_to_read = empty_way;

#ifdef __debug__
    std::cout << "Cache miss. Set not full. " << " Way to read = " << way_to_read << std::endl;         
#endif
            }
            else
            {
                // The set is full
                // Cache read miss
                m_misses++;

                UINT32 way_lru = GetLRU(m_sets[index]);
                
                way_to_read = way_lru;

            } // if(empty_way == WAY_INVALID)

            // Need to read new cache line from L2 (Common to Is there an empty way, Conflict / Compulsory misses)
            line_start_add = (m_sets[index].lines[way_to_read].tag << (m_num_offset_bits + m_num_index_bits)) |
                                (index << m_num_offset_bits);

            for(UINT32 item_offset = 0; item_offset < m_line_size; item_offset++)
            {
                m_sets[index].lines[way_to_read].line_data[item_offset] = m_next_mem->Read(line_start_add + item_offset);
            }

		} // if(WAY_INVALID == way_to_read)

		// Get the requested byte and update the state bits
		data = m_sets[index].lines[way_to_read].line_data[offset];
        m_sets[index].lines[way_to_read].valid = 1;
        m_sets[index].lines[way_to_read].tag = tag;

        m_num_reads++;
		UpdateLRU(m_sets[index],way_to_read);

#ifdef __debug__
        printf("Data Read = %x\n", data); 
        std::cout << std::dec << "Stats: Total Reads = " << m_num_reads << " Total Writes = " << m_num_writes << std::endl;         
        std::cout << "Stats: Total Hits = " << m_hits << " Total Misses = " << m_misses << std::endl; 
        for(UINT32 item_offset = 0; item_offset < m_line_size; item_offset++)
        {
            printf("\n Line data %d = %x ", item_offset, m_sets[index].lines[way_to_read].line_data[item_offset]);
        }
#endif

	}
	else
	{
	// Sets not allocated!! SERIOUS ERROR!!!
        
	}

	return data;

}



/*============================================================================
**
** Function Name:       Reset
**
** Visibility:          Public
**
** Description:         Clears all cache contents. Zeros out all data, tag, 
**                      and valid bits

** Invocation:          By the CPU of adjecent memory hierarchy.
**
** Input Parameters:    const UINT32 address, 
**
** Return Values:       UINT8 data
**                      
**==========================================================================*/
void CCacheWriteThru::Reset()
{
    UINT32 set_no = 0;
    UINT32 way_no = 0;
    UINT32 item_no = 0;

    // Reset all stats
    CCache::Reset();
    
#ifdef __debug__
    printf("\n------RESET------\n");
#endif

    if(m_sets)
    {
        for(set_no = 0; set_no < m_num_sets; set_no++)
        {
            for(way_no = 0; way_no < m_ways_per_set; way_no++)
            {
                // Reset all way parameters
                m_sets[set_no].lru[way_no]          = m_ways_per_set - 1;
                m_sets[set_no].lines[way_no].valid  = 0;
                m_sets[set_no].lines[way_no].tag    = 0;

                // Reset all line data
                for(item_no = 0; item_no < m_line_size; item_no++)
                {
                    m_sets[set_no].lines[way_no].line_data[item_no] = 0;
#ifdef __debug__
                   
                    if( (set_no == m_num_sets - 1) && (way_no == m_ways_per_set - 1) )
                    {
                        printf("\n %x ", m_sets[set_no].lines[way_no].line_data[item_no]);
                    }
                    
#endif
                }

            } // for(way_no...)

        } // for(set_no...)

    } // if(m_sets)
}



/*============================================================================
**
** Function Name:       Invalidate
**
** Visibility:          Public
**
** Description:         Invalidates data in the cache, if present.
**
** Invocation:          By the CPU of adjecent memory hierarchy.
**
** Input Parameters:    const UINT32 address, 
**
** Return Values:       TRUE if data was present and invalidated.
**                      FALSE otherwise.
**                      
**==========================================================================*/

BOOL CCacheWriteThru :: Invalidate (const UINT32 address)
{
	UINT32 index = GetIndexBits(address);
    UINT32 tag = GetTagBits(address);
	UINT32 way_to_inv = WAY_INVALID;
	BOOL inv_success = FALSE;

	if (m_sets)
	{
		way_to_inv = MatchTagBits(m_sets[index], tag);
		if(WAY_INVALID != way_to_inv)
		{
			//Make the VALID bit of that line = 0
			m_sets[index].lines[way_to_inv].valid = 0;
			inv_success = TRUE;	
		}
		else
		{
			//we don't have the line to be invalidated in our cache!
			inv_success = FALSE;
		}
		
	}
	else
	{
		inv_success = FALSE;
	}
	return inv_success;
}

CCacheWriteThru::~CCacheWriteThru(void)
{
	if(m_sets)
		delete[] m_sets;
}
