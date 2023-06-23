#pragma once
#include "dgamex86.h"
#include "Entity.h"
gentity_t *G_GetEntityByClient(int clientNum);
gentity_t *G_GetEntityByClientName(const char *name);
Entity *G_GetEntity(int ent_num);
int G_GetEntityIndex(int number);
int G_GetEntityIndex(gentity_t * ent);
gentity_t *G_GetGEntity(int ent_num);

void G_PrintToAllClients(const char *pszString, qboolean bBold = qtrue);
void G_PrintToClient(int clientnum, const char* pszString);