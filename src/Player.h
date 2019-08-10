#pragma once
#include "Event.h"
#include "ClassDef.h"
#include "CustomEventResponseSet.h"
#include "Sentient.h"
#include "DM_Team.h"
#include "dgamex86.h"

class Player : public Sentient //1504
{
	// can't bother to fix the offsets, I'll use direct offests & dummies
	// for info about offsets, check Player.txt
	// 
	
	uint8_t pfiller1[BUTTONS_OFFSET - sizeof(Sentient)];
	int buttons;
	uint8_t pfiller2[NUM_DEATHS_OFFSET - BUTTONS_OFFSET - sizeof(buttons)];
	int num_deaths;
	int num_kills;
	uint8_t pfiller3[PLAYER_SIZE - sizeof(num_kills) - sizeof(num_deaths) - NUM_DEATHS_OFFSET];
public:
	Player();
	~Player();
	static ResponseDef<Player>	*Responses;
	static CustomEventResponseSet<Player> cerSet;
	static void PrintOffsets();
	static void Init();
	static void Shutdown();

	static void(__thiscall *Respawn_Orignal)(Player*_this, Event *ev);
	static void(__thiscall *Killed_Orignal)(Player*_this, Event *ev);

	void Test(Event * ev);
	
	static void		MiscInit();
	static void		ClientCommandsInit();

	void GetKillsEvent(Event * ev);
	void GetDeathsEvent(Event * ev);
	void GetConnStateEvent(Event * ev);
	void GetActiveWeapEvent(Event * ev);
	void SecFireHeldEvent(Event * ev);
	void GetUserInfoEvent(Event * ev);
	void GetInventoryEvent(Event * ev);
	void IsAdminEvent(Event *ev);

	void AdminLoginEvent(Event * ev);
	void AdminLogoutEvent(Event * ev);

	void AdminKickEvent(Event * ev);
	void AdminKickReasonEvent(Event * ev);
	void AdminClientKickEvent(Event * ev);
	void AdminClientKickReasonEvent(Event * ev);


	void AdminBanIPEvent(Event * ev);
	void AdminBanIPReasonEvent(Event * ev);
	void AdminClientBanEvent(Event * ev);
	void AdminClientBanReasonEvent(Event * ev);
	void AdminUnbanIPEvent(Event * ev);
	void AdminListIPsEvent(Event * ev);

	void AdminBanNameEvent(Event *ev);
	void AdminUnbanNameEvent(Event * ev);
	void AdminListNamesEvent(Event * ev);

	void AdminProtectNameEvent(Event * ev);
	void AdminUnprotectNameEvent(Event * ev);
	void AdminListProtectedNamesEvent(Event * ev);

	void AdminBanWordEvent(Event * ev);
	void AdminUnbanWordEvent(Event * ev);
	void AdminListWordsEvent(Event * ev);
	
	void AdminDisableChatEvent(Event *ev);
	void AdminDisableTauntsEvent(Event *ev);

	void AdminChangeMapEvent(Event *ev);
	void AdminRestartEvent(Event *ev);
	void AdminSetFragLimitEvent(Event *ev);
	void AdminSetTimeLimitEvent(Event *ev);
	void AdminSetGameTypeEvent(Event *ev);
	void AdminSayEvent(Event *ev);
	void AdminSayPrivateEvent(Event *ev);
	void AdminStatusEvent(Event *ev);
	void AdminListAdminsEvent(Event *ev);
};

void __fastcall Respawn(Player *_this, void * edx, Event * ev);
void __fastcall Killed(Player *_this, void * edx, Event * ev);
