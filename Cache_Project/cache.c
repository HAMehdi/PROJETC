#include "low_cache.h"
#include "cache.h"

//! Création du cache.
struct Cache *Cache_Create(const char *fic, unsigned nblocks, unsigned nrecords,
                           size_t recordsz, unsigned nderef)
{
	struct Cache cache = (struct Cache)malloc(sizeof(struct Cache));
	return cache;
}

//! Fermeture (destruction) du cache.
Cache_Error Cache_Close(struct Cache *pcache)
{
	return NULL;
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
