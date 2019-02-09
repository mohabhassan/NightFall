#pragma once
#include "Listener.h"
#include "str.h"
#include "gamex86.h"
#include "Player.h"
class DM_Team :
	public Listener
{

	void* /*Container< PlayerStart * >*/ m_spawnpoints[3];
	void* /*Container< Player * >*/ m_players[3];

	int			m_maxplayers;

	str			m_teamname;

	int			m_teamnumber;

	teamType_t	teamType;

	int			m_countdown;

	int			m_teamwins;
	int			m_wins_in_a_row;

	int			m_iKills;
	int			m_iDeaths;

	qboolean	m_bHasSpawnedPlayers;

public:
	DM_Team();
	~DM_Team();
};

