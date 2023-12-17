#include "g_misc.h"

gentity_t *G_GetEntityByClient(int clientNum)
{
	gentity_t* gent_actual = G_GetGEntity(clientNum);

	for (int i = 0; i < globals->num_entities; i++, gent_actual = G_GetGEntity(i))
	{
		if (!gent_actual)
			continue;
		GEntity gent(gent_actual);
		if (gent->client->isValid() && gent->client->ps.clientNum == clientNum)//useful when sv_privatePassword is set
			return gent;
	}

	return NULL;
}

// Returns gentity form client name
// Guarenteed gent and gent->client if no NULL retuned
gentity_t * G_GetEntityByClientName(const char *name)
{
	gentity_t* gent_actual = G_GetGEntity(0);

	for (int i = 0;  i < globals->num_entities; i++, gent_actual = G_GetGEntity(i))
	{
		if (!gent_actual)
			continue;
		GEntity gent(gent_actual);
		if (gent->client->isValid() && !stricmp(gent->client->pers.netname, name))
			return gent;
	}

	return NULL;
}


Entity *G_GetEntity(int ent_num)
{
	gentity_t* gent = G_GetGEntity(ent_num);
	if (gent)
		return GEntity(gent)->entity;
	else
		return NULL;
}


int G_GetEntityIndex(int number)
{

	if (number < 0 || number > globals->max_entities) {
		return -1;
	}

	for (int i = 0; i < globals->num_entities; i++)
	{
		GEntity gent = globals->GetGEntity(i);
		if (gent->s.number == number) {
			return i;
		}
	}

	return -1;
}

int G_GetEntityIndex(gentity_t * ent)
{
	return G_GetEntityIndex(GEntity(ent)->s.number);
}

gentity_t *G_GetGEntity(int ent_num)
{

	if (ent_num < 0 || ent_num > globals->max_entities)
	{
		gi->DPrintf("G_GetEntity: %d out of valid range.\n", ent_num);
		return NULL;
	}

	return globals->GetGEntity(ent_num);
}


void G_PrintToAllClients(const char *pszString, qboolean bBold)
{
	if (bBold)
	{
		gi->SendServerCommand(-1, "print \"" HUD_MESSAGE_WHITE "%s\n\"", pszString);
	}
	else
	{
		gi->SendServerCommand(-1, "print \"" HUD_MESSAGE_YELLOW "%s\n\"", pszString);
	}
}

void G_PrintToClient(int clientnum, const char* pszString)
{
	using std::string;
	constexpr size_t buf_len = 500;
	std::string str = pszString;
	size_t remlen = str.size();
	size_t curr_index = 0;
	while (remlen > buf_len - 1)
	{
		string buf = str.substr(curr_index, buf_len - 1);
		size_t last_newline_index = buf.find_last_of('\n');
		buf = buf.substr(0, last_newline_index + 1);
		size_t part_size = buf.size();
		remlen = remlen - part_size - 1;
		curr_index += part_size - 1;
		gi->SendServerCommand(clientnum, "print \"%s\"", buf.c_str());
	}

	if (remlen > 0)
	{
		string buf = str.substr(curr_index, buf_len - 1);
		gi->SendServerCommand(clientnum, "print \"%s\"", buf.c_str());
	}
}

