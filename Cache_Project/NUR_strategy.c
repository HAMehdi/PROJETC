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


typedef struct t_Strategy {
	unsigned R:1; // 1 bit utilisé
	unsigned M:1; // 1 bit utilisé
	unsigned ndrf; // temps avant déréférençage
} Strategy;


/****
struct Cache {
	char* file; // Nom du fichier
	FILE *fp; // Pointeur sur fichier
	unsigned int nblocks; // Nb de blocs dans le cache
	unsigned int nrecords; // Nombre d'enregistrements par bloc 
	size_t recordsz; // Taille d'un enregistrement
	size_t blocksz; // Taille d'un bloc 
	unsigned int nderef; // Période de déréférençage pour NUR
	void *pstrategy; // Structure de données dépendant de la stratégie
	struct Cache_Instrument instrument; // Instrumentation du cache
	struct Cache_Block_Header *pfree; // premier bloc libre
	struct Cache_Block_Header *headers; // Les données elles-mêmes
};
*****/


void *Strategy_Create(struct Cache *pcache) 
{
	Strategy *strat = pcache->pstrategy;
	strat = (*Strategy) malloc(sizeof(Strategy));
	
	return NULL;
}

void Strategy_Close(struct Cache *pcache)
{
	Strategy *strat = pcache->pstrategy;
	free(strat);
}

void Strategy_Invalidate(struct Cache *pcache)
{
	Strategy *strat = pcache->pstrategy;
	free(strat);
}

/*
 * TODO (actuellement = RAND)
 */ 
struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache) 
{
    int ib, ibval = 4;
    struct Cache_Block_Header *pbh;

    /* On cherche d'abord un bloc invalide */
    if ((pbh = Get_Free_Block(pcache)) != NULL)
		return pbh;

    /* Sinon on cherche le bloc de valeur la plus faible (2R+M)
     	en cas d'égalité, on gardera le premier bloc trouvé */ 
	for(int i=0; i<pcache->nblocks; i++) {
		Strategy *strat = headers[i]->pstrategy;
		int val = (strat->R<<1) + strat->M;
		if(val < ibval)
		{
			if(!val)
				return &pcache->headers[i];
			ib = i;
			ibval = val;
		}
	}

	return &pcache->headers[ib];
}


void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh) 
{
	Strategy *strat = pcache->pstrategy;
	strat->R = 1;
}

void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
	Strategy *strat = pcache->pstrategy;
	strat->M = 1;
} 

char *Strategy_Name()
{
	return "NUR";
}
