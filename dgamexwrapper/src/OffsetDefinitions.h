#pragma once

#if defined(MOHBT) || defined(MOHSH) || defined(MOHAA)
#define DGAMEX_OFFSET(name, addr) constexpr int name = addr;
#endif

#ifdef CLIENT
#ifdef MOHBT

//Player.h
DGAMEX_OFFSET(BUTTONS_OFFSET, 1724)//string, g_success 
DGAMEX_OFFSET(NUM_DEATHS_OFFSET, 2108)//string, you killed yourself
DGAMEX_OFFSET(PLAYER_SIZE, 2404)//string, player

//Sentient.h
DGAMEX_OFFSET(ACTIVEWEAPONLIST_OFFSET, 1036)//string, putaway
DGAMEX_OFFSET(SENTEINT_SIZE, 1504)//string, Sentient

#endif // MOHBT
#endif // CLIENT

#ifdef SERVER
#ifdef MOHBT

//Player.h
DGAMEX_OFFSET(BUTTONS_OFFSET, 1724)//string, g_success 
DGAMEX_OFFSET(NUM_DEATHS_OFFSET, 2108)//string, you killed yourself
DGAMEX_OFFSET(PLAYER_SIZE, 2404)//string, player

//Sentient.h
DGAMEX_OFFSET(ACTIVEWEAPONLIST_OFFSET, 1036)//string, putaway
DGAMEX_OFFSET(SENTEINT_SIZE, 1504)//string, Sentient

#endif // MOHBT

//separate section for sh, it's worth noting that SH and BT are the same thing.
#ifdef MOHSH

//Player.h
DGAMEX_OFFSET(BUTTONS_OFFSET, 1724)//string, g_success 
DGAMEX_OFFSET(NUM_DEATHS_OFFSET, 2108)//string, you killed yourself
DGAMEX_OFFSET(PLAYER_SIZE, 2404)//string, player

//Sentient.h
DGAMEX_OFFSET(ACTIVEWEAPONLIST_OFFSET, 1036)//string, putaway
DGAMEX_OFFSET(SENTEINT_SIZE, 1504)//string, Sentient


#endif // MOHSH

#ifdef MOHAA



//Player.h
DGAMEX_OFFSET(BUTTONS_OFFSET, 1824)//string, g_success 
DGAMEX_OFFSET(NUM_DEATHS_OFFSET, 2208)//string, you killed yourself
DGAMEX_OFFSET(CURRENT_TEAM_OFFSET, 2248)//string, wait 250;pushmenu_teamselect
DGAMEX_OFFSET(PLAYER_SIZE, 2428)//string, player

//Sentient.h
DGAMEX_OFFSET(ACTIVEWEAPONLIST_OFFSET, 1000)//string, putaway
DGAMEX_OFFSET(SENTEINT_SIZE, 1464)//string, Sentient


#endif // MOHAA

#endif // SERVER