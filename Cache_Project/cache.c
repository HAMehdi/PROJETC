#include "low_cache.h"
#include "cache.h"
#include "strategy.h"
#include <string.h>

//! Création du cache.
struct Cache *Cache_Create(const char *fic, unsigned nblocks, unsigned nrecords,
                           size_t recordsz, unsigned nderef)
{
	struct Cache *cache = malloc(sizeof(struct Cache));
	
	char* name;
	strcpy(name,fic);
	cache->file = name;
	cache->fp = fopen(fic,"r+");
	cache->nblocks = nblocks;
	cache->nrecords = nrecords;
	cache->recordsz = recordsz;
		// La taille d'un bloc corresponds à la taille utilisable pour remplir le block( soit nrecords * recordsz)
	cache->blocksz =  nrecords * recordsz; 
	cache->nderef = nderef;
	cache->pstrategy = Strategy_Create(cache);
	
	struct Cache_Instrument instrument = { 0, 0, 0, 0, 0 };
	
	cache->instrument = instrument;
	
	struct Cache_Block_Header* pfree = malloc(sizeof(struct Cache_Block_Header));
	pfree->flags = VALID;
	pfree->ibfile = 0;
	pfree->ibcache = 0;
	pfree->data = NULL;
	
	cache->pfree = pfree;
	
	cache->headers = NULL;
	
	return cache;
}

//! Fermeture (destruction) du cache.
Cache_Error Cache_Close(struct Cache *pcache)
{
	Strategy_Close(pcache);
	
	free(pcache->file);
	free(pcache->fp);
	free(pcache->pstrategy);
	free(pcache->pfree);
	free(pcache->headers);
	free(pcache);
}

//! Synchronisation du cache.
Cache_Error Cache_Sync(struct Cache *pcache)
{
	//on regarde tous les headers du cache
	for(int i = 0 ; i < length(pcache->headers);i++){
		//si on trouve un bloc du cache qui est modifié, on écrit ce bloc dans le fichier
		if(pcache->headers[i]->flags.MODIF == 1){
			//on remet le flag à 0:
			pcache->headers[i]->flags.MODIF = 0;
			
			
		}
	}
	return NULL;
}

//! Invalidation du cache.
Cache_Error Cache_Invalidate(struct Cache *pcache)
{
	return NULL;
}

//! Lecture  (à travers le cache).
Cache_Error Cache_Read(struct Cache *pcache, int irfile, void *precord)
{
	return NULL;
}

//! Écriture (à travers le cache).
Cache_Error Cache_Write(struct Cache *pcache, int irfile, const void *precord)
{
	return NULL;
}


//! Résultat de l'instrumentation.
struct Cache_Instrument *Cache_Get_Instrument(struct Cache *pcache)
{
	struct Cache_Instrument* nInstrument = &pcache->instrument;
	
	pcache->instrument.n_reads = 0;
	pcache->instrument.n_hits = 0;
	pcache->instrument.n_deref = 0;
	pcache->instrument.n_syncs = 0;
	pcache->instrument.n_writes = 0;
	
	
	return nInstrument;
}
