#include "cache_list.h"

/*! Création d'une liste de blocs */
struct Cache_List *Cache_List_Create()
{
	// TODO
	return NULL;
}

/*! Destruction d'une liste de blocs */
void Cache_List_Delete(struct Cache_List *list)
{
	free(list);
}

/*! Insertion d'un élément à la fin */
void Cache_List_Append(struct Cache_List *list, struct Cache_Block_Header *pbh)
{
	if( list->next != NULL)
		Cache_List_Append(list->next,pbh);
	else
	{
		struct Cache_List *nList = malloc(sizeof(struct Cache_List));
	
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
		struct Cache_List *nList = malloc(sizeof(struct Cache_List));
	
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
		Cache_List_Remove_First(list->prev);
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
		Cache_List_Remove_First(list->next);
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
	// TODO Voir le cas ou le header n'est pas du tout dans la liste

	if( list->pheader != pbh)
	{
		if( list->next != NULL)
			Cache_List_Remove(list->next,pbh);
		if ( list->prev != NULL)
			Cache_List_Remove(list->prev,pbh);
	}
	else
	{
		struct Cache_List *nPrev = list->prev;
		struct Cache_Block_Header *header = list->pheader;
		
		list->next->prev = list->prev;
		list->prev->next = list->next;

		Cache_List_Delete(list);

		return header;
	}
}

/*! Remise en l'état de liste vide */
void Cache_List_Clear(struct Cache_List *list)
{

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

	
}

/*! Transférer un élément  au début */
void Cache_List_Move_To_Begin(struct Cache_List *list,
                              struct Cache_Block_Header *pbh)
{

}
