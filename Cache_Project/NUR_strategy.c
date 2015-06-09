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
	unsigned tpsBfDrf; // temps avant déréférençage
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
	strat = malloc(sizeof(Strategy));

	strat->tpsBfDrf = pcache->nderef;
	
	return strat;
}

void Strategy_Close(struct Cache *pcache)
{
	Strategy *strat = pcache->pstrategy;
	free(strat);
}

void Strategy_Invalidate(struct Cache *pcache)
{
	// TODO
}

struct Cache_Block_Header *Strategy_Replace_Block(struct Cache *pcache) 
{
	int ibval = 4;
	struct Cache_Block_Header *pbh;

	/* On cherche d'abord un bloc invalide */
	if ((pbh = Get_Free_Block(pcache)) != NULL)
		return pbh;

	/* Sinon on cherche le bloc de valeur la plus faible (2R+M)
		en cas d'égalité, on gardera le premier bloc trouvé */ 
	for(int i=0; i<pcache->nblocks; i++) {

		struct Cache_Block_Header *pbhi = &pcache->headers[i];

		int val = (pbhi->flags & READ?2:0) + (pbhi->flags & MODIF?1:0); // Calcul 2R+M
		if(val < ibval)
		{
			if(!val) // val = 0, nous avons le (ou l'un des) meilleur(s) bloc(s), innutile de continuer
				break;
			pbh = pbhi; // enregistrement car meilleur
			ibval = val; // enregistrement de la valeur pour le comparer aux suivants
		}
	}

	return pbh;
}

void Strategy_Read(struct Cache *pcache, struct Cache_Block_Header *pbh) 
{
	pbh->flags |= READ;
}

void Strategy_Write(struct Cache *pcache, struct Cache_Block_Header *pbh)
{
	pbh->flags |= VALID;
}

static void deref(struct Cache *pcache)
{
	Strategy *strat = pcache->pstrategy;

	// décrémenter le compte à rebour avant déréférenciation, ne rien faire de plus s'il reste du temps
	if (--(strat->tpsBfDrf) > 0)
		return;

	// Déréférencer chaque bloc
	for (int i = 0; i < pcache->nblocks; i++)
		pcache->headers[i].flags -= READ;

	strat->tpsBfDrf = pcache->nderef;
}

char *Strategy_Name()
{
	return "NUR";
}
