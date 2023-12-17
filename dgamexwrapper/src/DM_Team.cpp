#include "DM_Team.h"
//#define INTERMISSIONTIME_ADDR 
//constexpr int leve_intermissiontime = reinterpret_cast<int>(1);
#include "AddressDefinitions.h"


void(__thiscall* DM_Team::AddKills_Orignal)(DM_Team* _this, Player* player, int numKills);
void(__thiscall* DM_Team::AddDeaths_Orignal)(DM_Team* _this, Player* player, int numDeaths);

DM_Team::DM_Team()
{
	sizeof(Listener);
}


DM_Team::~DM_Team()
{
}

void DM_Team::Init()
{
	if (gameInfo.IsAA())
	{
		AddKills_Orignal = reinterpret_cast<void(__thiscall*)(DM_Team * _this, Player * player, int numKills)>((int)DMTEAM_ADDKILLS_ADDR);
		AddDeaths_Orignal = reinterpret_cast<void(__thiscall*)(DM_Team * _this, Player * player, int numDeaths)>((int)DMTEAM_ADDDEATHS_ADDR);
	}
}

void DM_Team::AddKillsAA(Player* player, int numKills)
{
	if (!gameInfo.IsAA())
		return;
	AddKills_Orignal(this, player, numKills);
}

void DM_Team::AddDeathsAA(Player* player, int numDeaths)
{
	if (!gameInfo.IsAA())
		return;
	AddDeaths_Orignal(this, player, numDeaths);
}