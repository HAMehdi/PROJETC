#include "low_cache.h"

//! Recherche d'un bloc libre.
struct Cache_Block_Header *Get_Free_Block(struct Cache *pcache)
{
	return pcache->pfree;
}
