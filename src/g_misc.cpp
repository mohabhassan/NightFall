#include "g_misc.h"

gentity_t *G_GetEntityByClient(int clientNum)
{
	gentity_t * ent = globals->gentities;
	if (clientNum < 0 || clientNum > globals->max_entities)
	{
		gi.DPrintf("G_GetEntity: %d out of valid range.", clientNum);
		return NULL;
	}

	for (int i = 0; ent && i < globals->num_entities; i++, ent++)
	{
		if (ent->s.clientNum == clientNum)
			return ent;
	}

	return NULL;
}

