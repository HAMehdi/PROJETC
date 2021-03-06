/*!
 * \file FIFO_strategy.c
 *
 * \brief  Stratégie de remplacement FIFO..
 * 
 * \author
 *
 * $Id: FIFO_strategy.c
 */

#include <assert.h>

#include "strategy.h"
#include "low_cache.h"
#include "random.h"
#include "time.h"

/*!
 */
void *Strategy_Create(struct Cache *pcache)
{
}

/*!
 */
void Strategy_Close(struct Cache *pcache)
{
}

/*!
 */
void Strategy_Invalidate(struct Cache *pcache)
{
}

/*!
 */
struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache)
{
}


/*!
 */
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
}

/*!
 */
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
}

char *Strategy_Name()
{
    return "FIFO";
}
