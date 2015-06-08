#include "cache_list.h"
#include <stdlib.h>
#include "low_cache.h"

/*!Renvoie le vrai début de la liste*/
struct Cache_List *Cache_List_First(struct Cache_List *list)
{
	while(list->prev != NULL){
		list = list->prev;
	}
	return list;
}

/*!Renvoie la vraie fin de la liste*/
struct Cache_List *Cache_List_Last(struct Cache_List *list)
{
	while(list->next != NULL){
		list = list->next;
	}
	return list;
}

/*! Création d'une liste de blocs */
struct Cache_List *Cache_List_Create()
{
	struct Cache_List *nList = malloc(sizeof(struct Cache_List));
	return nList;
}

/*! Destruction d'une liste de blocs */
void Cache_List_Delete(struct Cache_List *list)
{
	free(list->pheader);
	free(list);
}

/*! Insertion d'un élément à la fin */
void Cache_List_Append(struct Cache_List *list, struct Cache_Block_Header *pbh)
{
	if( list->next != NULL)
		Cache_List_Append(list->next,pbh);
	else
	{
		struct Cache_List *nList = Cache_List_Create();
	
		list->next = nList;
	
		nList->pheader = pbh;
		nList->prev = list;
		nList->next = NULL;
	}
}

/*! Insertion d'un élément au début*/
void Cache_List_Prepend(struct Cache_List *list, struct Cache_Block_Header *pbh)
{
	if( list->prev != NULL)
		Cache_List_Append(list->prev,pbh);
	else
	{
		struct Cache_List *nList = Cache_List_Create();
	
		list->prev = nList;
	
		nList->pheader = pbh;
		nList->prev = NULL;
		nList->next = list;
	}
}

/*! Retrait du premier élément */
struct Cache_Block_Header *Cache_List_Remove_First(struct Cache_List *list)
{
	if( list->prev != NULL)
		return Cache_List_Remove_First(list->prev);
	else
	{
		struct Cache_Block_Header *header = list->pheader;
		list->next->prev = NULL;
		Cache_List_Delete(list);

		return header;
	}
	
}

/*! Retrait du dernier élément */
struct Cache_Block_Header *Cache_List_Remove_Last(struct Cache_List *list)
{
	if( list->next != NULL)
		return Cache_List_Remove_First(list->next);
	else
	{
		struct Cache_Block_Header *header = list->pheader;
		list->prev->next = NULL;
		Cache_List_Delete(list);

		return header;
	}
}

/*! Retrait d'un élément quelconque */
struct Cache_Block_Header *Cache_List_Remove(struct Cache_List *list,
                                             struct Cache_Block_Header *pbh)
{
	for(list = Cache_List_First(list); list->next != NULL; list = list->next)
	{
		if (list->pheader == pbh)
		{
			struct Cache_Block_Header *header = list->pheader;
			
			list->next->prev = list->prev;
			list->prev->next = list->next;

			Cache_List_Delete(list);

			return header;
		}
	}
	
	return NULL;
}

/*! Remise en l'état de liste vide */
void Cache_List_Clear(struct Cache_List *list)
{
	list = Cache_List_Last(list);
	
	//je remonte dans ma liste en supprimant le dernier bloc
	while(list->prev !=NULL){
		//je recule de un
		list= list->prev;
		//puis je supprime l'élément devant moi
		Cache_List_Delete(list->next);
	}
	//quand tous les precedent sont free, on doit free le dernier(et premier) element
	Cache_List_Delete(list);

}

/*! Test de liste vide */
bool Cache_List_Is_Empty(struct Cache_List *list)
{
	if(list->next == NULL && list->prev == NULL && list->pheader == NULL)
		return true;

	return false;
}

/*! Transférer un élément à la fin */
void Cache_List_Move_To_End(struct Cache_List *list,
                            struct Cache_Block_Header *pbh)
{
	if(list->prev != NULL)
	{
		struct Cache_List* pList = list->prev;
		Cache_List_Remove(list,pbh);
		Cache_List_Append(pList,pbh);
	}
	else if (list->next != NULL)
	{
		struct Cache_List* nList = list->next;
		Cache_List_Remove(list,pbh);
		Cache_List_Append(nList,pbh);
	}
	else
		// On ne fait rien car ca veut dire que l'élement est seul dans la liste
}

/*! Transférer un élément  au début */
void Cache_List_Move_To_Begin(struct Cache_List *list,
                              struct Cache_Block_Header *pbh)
{
	if(list->prev != NULL)
	{
		struct Cache_List* pList = list->prev;
		Cache_List_Remove(list,pbh);
		Cache_List_Prepend(pList,pbh);
	}
	else if (list->next != NULL)
	{
		struct Cache_List* nList = list->next;
		Cache_List_Remove(list,pbh);
		Cache_List_Prepend(nList,pbh);
	}
	else
		// On ne fait rien car ca veut dire que l'élement est seul dans la liste
}
