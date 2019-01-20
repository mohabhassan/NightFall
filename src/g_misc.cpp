#include "g_misc.h"

gentity_t *G_GetEntityByClient(int clientNum)
{
	gentity_t* gent = G_GetGEntity(clientNum);

	for (int i = 0; gent && i < globals->num_entities; i++, gent++)
	{
		if (gent->s.clientNum == clientNum)//extra check ?
			return gent;
	}

	return NULL;
}


Entity *G_GetEntity(int ent_num)
{
	gentity_t* gent = G_GetGEntity(ent_num);
	if (gent)
		return (Entity*)gent->entity;
	else
		return NULL;
}


int G_GetEntityIndex(int number)
{
	gentity_t * ent = globals->gentities;

	if (number < 0 || number > globals->max_entities) {
		return -1;
	}

	for (int i = 0; i < globals->num_entities; i++, ent++)
	{
		if (ent->s.number == number) {
			return i;
		}
	}

	return -1;
}

int G_GetEntityIndex(gentity_t * ent)
{
	return G_GetEntityIndex(ent->s.number);
}

gentity_t *G_GetGEntity(int ent_num)
{
	gentity_t * ent = &globals->gentities[ent_num];

	if (ent_num < 0 || ent_num > globals->max_entities)
	{
		gi.DPrintf("G_GetEntity: %d out of valid range.\n", ent_num);
		return NULL;
	}

	return ent;
}