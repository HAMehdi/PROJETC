#include "low_cache.h"
#include "cache.h"

//! Création du cache.
struct Cache *Cache_Create(const char *fic, unsigned nblocks, unsigned nrecords,
                           size_t recordsz, unsigned nderef)
{
	struct Cache *cache = malloc(sizeof(struct Cache));
	
	cache->file = fic;
	cache->fp = fopen(fic,"r+");
	cache->nblocks = nblocks;
	cache->nrecords = nrecords;
	cache->recordsz = recordsz;
	// TODO cache->blocksz = 0; 
	cache->nderef = nderef;
	// TODO cache->pstrategy = NULL;
	
	struct Cache_Instrument instrument = { 0, 0, 0, 0, 0 };
	
	cache->instrument = instrument;
	
	struct Cache_Block_Header* pfree = malloc(sizeof(struct Cache_Block_Header));
	pfree->flags = VALID;
	pfree->ibfile = 0;
	pfree->ibcache = 0;
	pfree->data = NULL;
	
	cache->pfree = pfree;
	
	struct Cache_Block_Header* headers = malloc(sizeof(struct Cache_Block_Header));
	headers->flags = VALID;
	headers->ibfile = 0;
	headers->ibcache = 0;
	headers->data = NULL;
	
	cache->headers = headers;
	
	return cache;
}

//! Fermeture (destruction) du cache.
Cache_Error Cache_Close(struct Cache *pcache)
{
	free(cache->file);
	free(cache->fp);
	free(cache->pstrategy);
	free(cache->pfree);
	free(cache->headers);
	free(cache);
}

//! Synchronisation du cache.
Cache_Error Cache_Sync(struct Cache *pcache)
{
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
	return NULL;
}
