/*!
 * \file LRU_strategy.c
 *
 * \brief  Stratégie de remplacement LRU..
 * 
 * \author Mehdi
 *
 * $Id: LRU_strategy.c
 */

#include <assert.h>

#include "strategy.h"
#include "low_cache.h"
#include "random.h"
#include "time.h"
#include "cache_list.h"

/* Transforme le pointeur sur la stratégie en un pointeur sur la liste LRU */
#define LRU_LIST(pcache) ((struct Cache_List *)((pcache)->pstrategy))



/*!
 * Crée et initialise les structures de données spécifiques à la stratégie.
 */
void *Strategy_Create(struct Cache *pcache)
{
    return Cache_List_Create();
}

/*!
 */
void Strategy_Close(struct Cache *pcache)
{
    Cache_List_Delete(LRU_LIST(pcache));
}

/*!
 * Libère et détruit les structures de données spécifiques à la stratégie.
 */
void Strategy_Invalidate(struct Cache *pcache)
{
    Cache_List_Delete(LRU_LIST(pcache));
}

/*!
 */
struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache)
{
    struct Cache_Block_Header *pbh;
    struct Cache_List *lru_list = LRU_LIST(pcache);

    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL)
    {
        /* On ajoute les blocs invalides à la fin de la liste  */
        Cache_List_Append(lru_list, pbh);  
        return pbh;
    }

    /* Sinon on prend le premier bloc de la liste LRU et on le déplace à la fin
     * de la liste */
    pbh = Cache_List_Remove_First(lru_list);
    Cache_List_Append(lru_list, pbh);

    return pbh;
}


/*!
 */
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
    Cache_List_Move_To_End(LRU_LIST(pcache), pbh);
}

/*!
 */
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
    Cache_List_Move_To_End(LRU_LIST(pcache), pbh);
}

/*!
 * Nom de la stratégie.
 */
char *Strategy_Name()
{
    return "LRU";
}
