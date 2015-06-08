/*!
 * \file NUR_strategy.c
 *
 * \brief  Stratégie de remplacement NUR..
 * 
 * \author Groupe 15
 *
 * NUR_strategy.c, 2015/06/08
 */
 

#include <assert.h>

#include "strategy.h"
#include "low_cache.h"
#include "random.h"
#include "time.h"



/*
 * TODO (actuellement = RAND)
 */ 
void *Strategy_Create(struct Cache *pcache) 
{
    return NULL;
}

/*
 * TODO
 */ 
void Strategy_Close(struct Cache *pcache)
{
}

/*
 * TODO
 */ 
void Strategy_Invalidate(struct Cache *pcache)
{
}

/*
 * TODO (actuellement = RAND)
 */ 
struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache) 
{
    int ib;
    struct Cache_Block_Header *pbh;

    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL) return pbh;

    /* Sinon on tire un numéro de bloc au hasard */
    ib = RANDOM(0, pcache->nblocks);
    return &pcache->headers[ib];
}


/*
 * TODO
 */ 
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh) 
{
}  

/*
 * TODO
 */  
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
} 

char *Strategy_Name()
{
    return "NUR";
}
