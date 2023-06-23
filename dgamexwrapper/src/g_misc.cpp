#include "g_misc.h"

gentity_t *G_GetEntityByClient(int clientNum)
{
	gentity_t* gent = G_GetGEntity(clientNum);

	for (int i = 0; gent && i < globals->num_entities; i++, gent++)
	{
		if (gent->client && gent->client->ps.clientNum == clientNum)//useful when sv_privatePassword is set
			return gent;
	}

	return NULL;
}

// Returns gentity form client name
// Guarenteed gent and gent->client if no NULL retuned
gentity_t * G_GetEntityByClientName(const char *name)
{
	gentity_t* gent = G_GetGEntity(0);

	for (int i = 0; gent && i < globals->num_entities; i++, gent++)
	{
		if (gent->client && !stricmp(gent->client->pers.netname, name))
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


void G_PrintToAllClients(const char *pszString, qboolean bBold)
{
	if (bBold)
	{
		gi.SendServerCommand(-1, "print \"" HUD_MESSAGE_WHITE "%s\n\"", pszString);
	}
	else
	{
		gi.SendServerCommand(-1, "print \"" HUD_MESSAGE_YELLOW "%s\n\"", pszString);
	}
}

void G_PrintToClient(int clientnum, const char* pszString)
{
	constexpr int buf_len = 500;
	static char buf[buf_len];
	int remlen = strlen(pszString);
	int curr_index = 0;
	while (remlen > buf_len-1)
	{
		strncpy(buf, pszString+curr_index, buf_len - 1);
		buf[buf_len-1] = NULL;
		remlen = remlen - buf_len - 1;
		curr_index += buf_len - 1;
		gi.SendServerCommand(clientnum, "print \"%s\"", buf);
	}
	strncpy(buf, pszString + curr_index, buf_len - 1);
	gi.SendServerCommand(clientnum, "print \"%s\n\"", buf);
}