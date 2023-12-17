#pragma once
#include "Listener.h"
#include "str.h"
#include "dgamex86.h"
#include "Player.h"

class Player;
//FIXME: size is not proper.
class DM_Team :
	public Listener
{

	void* /*Container< PlayerStart * >*/ m_spawnpoints[3];//20
	void* /*Container< Player * >*/ m_players[3];//32

	int			m_maxplayers;//44

	str			m_teamname;//48

	int			m_teamnumber;//60

	teamType_t	teamType;//64

	int			m_countdown;

	int			m_teamwins;
	int			m_wins_in_a_row;

	int			m_iKills;
	int			m_iDeaths;

	qboolean	m_bHasSpawnedPlayers;

public:
	DM_Team();
	~DM_Team();

	static void Init();


	void	AddKillsAA(Player* player, int numKills);
	void	AddDeathsAA(Player* player, int numDeaths);


	static void(__thiscall* AddKills_Orignal)(DM_Team* _this, Player* player, int numKills);
	static void(__thiscall* AddDeaths_Orignal)(DM_Team* _this, Player* player, int numDeaths);
};

