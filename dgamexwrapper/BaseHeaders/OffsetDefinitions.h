#pragma once
#include "AddressManager.h"
//these are offsets of member variables inside classes

//CLIENT
//BT
#define DGAMEX_OFFSET(name, addr) constexpr int name##_CBT = addr;
//Player.h
DGAMEX_OFFSET(BUTTONS_OFFSET, 1724)//string, g_success 
DGAMEX_OFFSET(NUM_DEATHS_OFFSET, 2108)//string, you killed yourself
DGAMEX_OFFSET(PLAYER_SIZE, 2404)//string, player

//Sentient.h
DGAMEX_OFFSET(ACTIVEWEAPONLIST_OFFSET, 1036)//string, putaway
DGAMEX_OFFSET(SENTEINT_SIZE, 1504)//string, Sentient
#undef DGAMEX_OFFSET

//SERVER
//BT
#define DGAMEX_OFFSET(name, addr) constexpr int name##_DBT = addr;
//Player.h
DGAMEX_OFFSET(BUTTONS_OFFSET, 1724)//string, g_success 
DGAMEX_OFFSET(NUM_DEATHS_OFFSET, 2108)//string, you killed yourself
DGAMEX_OFFSET(PLAYER_SIZE, 2404)//string, player

//Sentient.h
DGAMEX_OFFSET(ACTIVEWEAPONLIST_OFFSET, 1036)//string, putaway
DGAMEX_OFFSET(SENTEINT_SIZE, 1504)//string, Sentient

#undef DGAMEX_OFFSET

//SH
//separate section for sh, it's worth noting that SH and BT are the same thing.

#define DGAMEX_OFFSET(name, addr) constexpr int name##_DSH = addr;
//Player.h
DGAMEX_OFFSET(BUTTONS_OFFSET, 1724)//string, g_success 
DGAMEX_OFFSET(NUM_DEATHS_OFFSET, 2108)//string, you killed yourself
DGAMEX_OFFSET(PLAYER_SIZE, 2404)//string, player

//Sentient.h
DGAMEX_OFFSET(ACTIVEWEAPONLIST_OFFSET, 1036)//string, putaway
DGAMEX_OFFSET(SENTEINT_SIZE, 1504)//string, Sentient


#undef DGAMEX_OFFSET

//AA SERVER & CLIENT

#define DGAMEX_OFFSET(name, addr) constexpr int name##_AA = addr;
//Player.h
DGAMEX_OFFSET(BUTTONS_OFFSET, 1824)//string, g_success 
DGAMEX_OFFSET(NUM_DEATHS_OFFSET, 2208)//string, you killed yourself
DGAMEX_OFFSET(CURRENT_TEAM_OFFSET, 2248)//string, wait 250;pushmenu_teamselect
DGAMEX_OFFSET(PLAYER_SIZE, 2428)//string, player

//Sentient.h
DGAMEX_OFFSET(ACTIVEWEAPONLIST_OFFSET, 1000)//string, putaway
DGAMEX_OFFSET(SENTEINT_SIZE, 1464)//string, Sentient


#undef DGAMEX_OFFSET