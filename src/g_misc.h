#pragma once
#include "dgamex86.h"
#include "Entity.h"
gentity_t *G_GetEntityByClient(int clientNum);
Entity *G_GetEntity(int ent_num);
gentity_t *G_GetGEntity(int ent_num);
int G_GetEntityIndex(int number);
int G_GetEntityIndex(gentity_t * ent);