#include "DM_Team.h"
//#define INTERMISSIONTIME_ADDR 
//constexpr int leve_intermissiontime = reinterpret_cast<int>(1);
#include "GameVersion.h"

#ifdef MOHAA

void(__thiscall* DM_Team::AddKills_Orignal)(DM_Team* _this, Player* player, int numKills);
void(__thiscall* DM_Team::AddDeaths_Orignal)(DM_Team* _this, Player* player, int numDeaths);

#endif // MOHAA
DM_Team::DM_Team()
{
	sizeof(Listener);
}


DM_Team::~DM_Team()
{
}

void DM_Team::Init()
{
#ifdef MOHAA

	AddKills_Orignal = reinterpret_cast<void(__thiscall*)(DM_Team * _this, Player * player, int numKills)>((int)DMTEAM_ADDKILLS_ADDR);
	AddDeaths_Orignal = reinterpret_cast<void(__thiscall*)(DM_Team * _this, Player * player, int numDeaths)>((int)DMTEAM_ADDDEATHS_ADDR);

#endif // MOHAA
}

#ifdef MOHAA

void DM_Team::AddKills(Player* player, int numKills)
{
	AddKills_Orignal(this, player, numKills);
}

void DM_Team::AddDeaths(Player* player, int numDeaths)
{
	AddDeaths_Orignal(this, player, numDeaths);
}

#endif // MOHAA