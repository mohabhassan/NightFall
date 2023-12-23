#pragma once
#include "Event.h"
#include "ClassDef.h"
#include "CustomEventResponseSet.h"
#include "Sentient.h"
#include "DM_Team.h"
#include "dgamex86.h"

class Player {};//empty defintion to avoid mistakes 

/*
 * Class Player
 * Used as an important utility class in the patch.
 **/


class DM_Team;

class PlayerAA : public SentientAA //1504
{
public:
	// can't bother to fix the offsets, I'll use direct offests & dummies
	// for info about offsets, check Player.txt
	// 

	uint8_t pfiller1[BUTTONS_OFFSET_AA - sizeof(SentientAA)];
	int buttons;
	uint8_t pfiller2[NUM_DEATHS_OFFSET_AA - sizeof(buttons) - BUTTONS_OFFSET_AA];
	int num_deaths;
	int num_kills;
	uint8_t pfiller3[CURRENT_TEAM_OFFSET_AA - sizeof(num_kills) - sizeof(num_deaths) - NUM_DEATHS_OFFSET_AA];
	DM_Team* current_team;
	uint8_t pfiller4[PLAYER_SIZE_AA - sizeof(current_team) - CURRENT_TEAM_OFFSET_AA];
};

class PlayerDSH : public SentientDSH //1504
{
public:
	// can't bother to fix the offsets, I'll use direct offests & dummies
	// for info about offsets, check Player.txt
	// 

	uint8_t pfiller1[BUTTONS_OFFSET_DSH - sizeof(SentientDSH)];
	int buttons;
	uint8_t pfiller2[NUM_DEATHS_OFFSET_DSH - sizeof(buttons) - BUTTONS_OFFSET_DSH];
	int num_deaths;
	int num_kills;
	uint8_t pfiller3[PLAYER_SIZE_DSH - sizeof(num_kills) - sizeof(num_deaths) - NUM_DEATHS_OFFSET_DSH];

};

using PlayerDBT = PlayerDSH;

class PlayerNF : public SentientNF
{
	union realPlayerType
	{
		PlayerAA playerAA;
		PlayerDSH playerDSH;
		PlayerDBT playerDBT;
	};
	realPlayerType* realPlayer;

#define PLAYERNF_MEMEBER_GETTER(varname) \
		decltype(PlayerAA::varname)& init_##varname() \
		{\
			static decltype(PlayerAA::varname) s_##varname; \
			if (!realPlayer) return s_##varname; \
			if (gameInfo.IsAA())\
				return realPlayer->playerAA.varname;\
			else if (gameInfo.IsSH())\
				return realPlayer->playerDSH.varname;\
			else if (gameInfo.IsBT())\
				return realPlayer->playerDBT.varname;\
		}

	PLAYERNF_MEMEBER_GETTER(buttons);
	PLAYERNF_MEMEBER_GETTER(num_kills);
	PLAYERNF_MEMEBER_GETTER(num_deaths);
	DM_Team* init_current_team()
	{
		if (gameInfo.IsAA())
			return realPlayer->playerAA.current_team;
		else
			return nullptr;
	}
#undef PLAYERNF_MEMEBER_GETTER
public:
	int& buttons;
	int& num_kills;
	int& num_deaths;
	DM_Team* const & current_team;
	PlayerNF(Player *p)
		: SentientNF((Sentient*)p), realPlayer((realPlayerType*)p), buttons(init_buttons()), num_kills(init_num_kills()), num_deaths(init_num_deaths()), current_team(init_current_team())
	{

	}

	bool isValid()
	{
		return realPlayer != NULL;
	}
	static ResponseDef<PlayerNF>	*Responses;
	static CustomEventResponseSet<PlayerNF> cerSet;


	//static void PrintOffsets();
	static void Init();
	static void Shutdown();

	static void(__thiscall *Respawn_Orignal)(Player*_this, Event *ev);
	static void(__thiscall *Killed_Orignal)(Player*_this, Event *ev);


	
	static void		MiscInit();
	static void		AdminCommandsInit();
	static void		ClientCommandsInit();
#define ScriptEventHandler(FuncName) void Pre##FuncName (Event *ev) { PlayerNF p((Player*)this); p.FuncName(ev);}; void FuncName(Event* ev);

	ScriptEventHandler(Test);
	ScriptEventHandler(GetKillsEvent);
	ScriptEventHandler(GetDeathsEvent);
	ScriptEventHandler(GetConnStateEvent);
	ScriptEventHandler(GetActiveWeapEvent);
	ScriptEventHandler(SecFireHeldEvent);
	ScriptEventHandler(GetUserInfoEvent);
	ScriptEventHandler(GetInventoryEvent);
	ScriptEventHandler(IsAdminEvent);

	ScriptEventHandler(AddKillsEventAA);
	ScriptEventHandler(AddDeathsEventAA);
	ScriptEventHandler(BindWeapEventAA);

	//The following functions are console(client command) events.
	ScriptEventHandler(PatchVersionEvent);

	//The following functions are console(admin command) events.
	ScriptEventHandler(AdminLoginEvent);
	ScriptEventHandler(AdminLogoutEvent);

	ScriptEventHandler(AdminKickEvent);
	ScriptEventHandler(AdminKickReasonEvent);
	ScriptEventHandler(AdminClientKickEvent);
	ScriptEventHandler(AdminClientKickReasonEvent);


	ScriptEventHandler(AdminBanIPEvent);
	ScriptEventHandler(AdminBanIPReasonEvent);
	ScriptEventHandler(AdminClientBanEvent);
	ScriptEventHandler(AdminClientBanReasonEvent);
	ScriptEventHandler(AdminUnbanIPEvent);
	ScriptEventHandler(AdminListIPsEvent);

	ScriptEventHandler(AdminBanNameEvent);
	ScriptEventHandler(AdminUnbanNameEvent);
	ScriptEventHandler(AdminListNamesEvent);

	ScriptEventHandler(AdminProtectNameEvent);
	ScriptEventHandler(AdminUnprotectNameEvent);
	ScriptEventHandler(AdminListProtectedNamesEvent);

	ScriptEventHandler(AdminBanWordEvent);
	ScriptEventHandler(AdminUnbanWordEvent);
	ScriptEventHandler(AdminListWordsEvent);

	ScriptEventHandler(AdminDisableChatEvent);
	ScriptEventHandler(AdminDisableTauntsEvent);

	ScriptEventHandler(AdminChangeMapEvent);
	ScriptEventHandler(AdminRestartEvent);
	ScriptEventHandler(AdminSetFragLimitEvent);
	ScriptEventHandler(AdminSetTimeLimitEvent);
	ScriptEventHandler(AdminSetGameTypeEvent);
	ScriptEventHandler(AdminSayEvent);
	ScriptEventHandler(AdminSayPrivateEvent);
	ScriptEventHandler(AdminStatusEvent);
	ScriptEventHandler(AdminListAdminsEvent);
	ScriptEventHandler(AdminRCONEvent);

};

void __fastcall Respawn(Player *_this, void * edx, Event * ev);
void __fastcall Killed(Player*_this, void * edx, Event * ev);
