/*!
 * \file FIFO_strategy.c
 *
 * \brief  Stratégie de remplacement FIFO..
 * 
 * \author Lucas
 *
 * $Id: FIFO_strategy.c
 */

#include <assert.h>

#include "strategy.h"
#include "low_cache.h"
#include "random.h"
#include "time.h"
#include "cache_list.h"

struct Cache_List * list_cache;

/*!
 */
void *Strategy_Create(struct Cache *pcache)
{
    //Création de la liste
    list_cache = Cache_List_Create();

    //Initialisation de la liste TODO Faut-il le faire ? Ou on laisse les bloques invalides
    /*
    int i;

    for(i = 0 ; i < pcache->nblocks ; i++){
        Cache_List_Append(list_cache,&pcache->headers[i]);
    }
    */

    return list_cache;
}

/*!
 * FIFO : Détruit la liste.
 */
void Strategy_Close(struct Cache *pcache)
{
    Cache_List_Delete(list_cache);
}

/*!
 * FIFO : Vide la liste.
 */
void Strategy_Invalidate(struct Cache *pcache)
{
    Cache_List_Clear(list_cache);
}

/*!
 * FIFO : On prend le premier bloc invalide. S'il n'y en a plus, on "prend" celui en tête
 */
struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache)
{
    struct Cache_Block_Header *pbh;

    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL) {
        //On l'ajoute à la fin de la liste
        Cache_List_Append(list_cache,pbh);
        return pbh;
    }

    /* Sinon on "prend" celui en tête */
    else {
        //On enlève le premier et on stock l'adresse
        pbh = Cache_List_Remove_First(list_cache);
        //On l'ajoute à la fin de la liste
        Cache_List_Append(list_cache,pbh);

        return pbh;
    }
}


/*!
 * FIFO : Rien à faire ici.
 */
void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
}

/*!
 * FIFO : Rien à faire ici.
 */
void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
}

/*!
 * FIFO : Nom de la stratégie
 */
char *Strategy_Name()
{
    return "FIFO";
}
