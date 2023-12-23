#include "Player.h"
#include "g_misc.h"
#include "ClientAdmin.h"
#include "Item.h"

#define	BUTTON_ATTACK2		2	// +/-attacksecondary

void PlayerNF::MiscInit()
{
	cerSet.AddEventResponse(new Event(
		"getkills",
		EV_DEFAULT,
		NULL,
		NULL,
		"gets kills number of player",
		EV_RETURN
	),
		&PlayerNF::PreGetKillsEvent);
	cerSet.AddEventResponse(new Event(
		"getdeaths",
		EV_DEFAULT,
		NULL,
		NULL,
		"gets deaths number of player",
		EV_RETURN
	),
		&PlayerNF::PreGetDeathsEvent);
	cerSet.AddEventResponse(new Event(
		"getconnstate",
		EV_DEFAULT,
		NULL,
		NULL,
		"Gets state of player's connection.",
		EV_RETURN
	),
		&PlayerNF::PreGetConnStateEvent);
	cerSet.AddEventResponse(new Event(
		"getactiveweap",
		EV_DEFAULT,
		"i",
		"weapon_hand",
		"Gets currently active weapon from player's hand of given index.",
		EV_RETURN
	),
		&PlayerNF::PreGetActiveWeapEvent);
	cerSet.AddEventResponse(new Event(
		"secfireheld",
		EV_DEFAULT,
		NULL,
		NULL,
		"Returns 1 if player is holding secondary fire button.",
		EV_GETTER
	),
		&PlayerNF::PreSecFireHeldEvent);
	cerSet.AddEventResponse(new Event(
		"userinfo",
		EV_DEFAULT,
		NULL,
		NULL,
		"Returns player's userinfo.",
		EV_GETTER
	),
		&PlayerNF::PreGetUserInfoEvent);
	cerSet.AddEventResponse(new Event(
		"inventory",
		EV_DEFAULT,
		NULL,
		NULL,
		"Returns player's inventory.",
		EV_GETTER
	),
		&PlayerNF::PreGetInventoryEvent);

	cerSet.AddEventResponse(new Event(
		"isadmin",
		EV_DEFAULT,
		NULL,
		NULL,
		"Check if player is logged in as admin",
		EV_RETURN
	),
		&PlayerNF::PreIsAdminEvent);
	if (gameInfo.IsAA())
	{
		cerSet.AddEventResponse(new Event(
			"addkills",
			EV_DEFAULT,
			"i",
			"numkills",
			"Adds number of kills to player. (Can be also negative)"
		),
			&PlayerNF::PreAddKillsEventAA);

		cerSet.AddEventResponse(new Event(
			"adddeaths",
			EV_DEFAULT,
			"i",
			"numDeaths",
			"Adds number of deaths to player. (Can be also negative)"
		),
			&PlayerNF::PreAddDeathsEventAA);


		cerSet.AddEventResponse(new Event(
			"bindweap",
			EV_DEFAULT,
			"e",
			"weapon",
			"Binds weapon to player and set player as weapon owner.",
			EV_NORMAL
		),
			&PlayerNF::PreBindWeapEventAA);
	}

}

void PlayerNF::GetKillsEvent(Event *ev)
{
	ev->AddInteger(num_kills);
}

void PlayerNF::GetDeathsEvent(Event *ev)
{
	ev->AddInteger(num_deaths);
}

void PlayerNF::GetConnStateEvent(Event *ev)
{
	client_t* cl = GetClientByClientNum(client->ps.clientNum);
	if(!cl)
	{
		gi->Printf(PATCH_NAME " SCRIPT ERROR: Invalid player for getconnstate!\n");
		return;
	}
	
	ev->AddInteger(Client(cl)->state);
}

void PlayerNF::GetActiveWeapEvent(Event *ev)
{
	weaponhand_t hand = (weaponhand_t)ev->GetInteger(1);
	if (hand >= WEAPON_ERROR)
	{
		gi->Printf(PATCH_NAME " SCRIPT ERROR: Wrong hand number for getactiveweap: %d, maximum is: %d\n", int(hand), int(WEAPON_ERROR-1));
		return;
	}
	ev->AddListener((Listener*)GetActiveWeapon((weaponhand_t)ev->GetInteger(1)));
}

void PlayerNF::SecFireHeldEvent(Event *ev)
{
	ev->AddInteger((bool)(buttons & BUTTON_ATTACK2));
}

void PlayerNF::GetUserInfoEvent(Event *ev)
{
	ev->AddString(client->pers.userinfo);
}

void PlayerNF::GetInventoryEvent(Event *ev)
{
	Entity *ent = NULL;
	ScriptVariable arr;
	ScriptVariable index, value;
	int count = 0;
	for (size_t i = 0; i < inventory.NumObjects(); i++)
	{
		ent = G_GetEntity(inventory[i]);
		if (!ent)
		{
			continue;
		}
		index.setIntValue(count);
		value.setListenerValue((Listener*)ent);
		arr.setArrayAtRef(index, value);
		count++;
	}
	ev->AddValue(arr);
}

void PlayerNF::IsAdminEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (admin.isAdmin())
	{
		ev->AddInteger(1);
	}
	else
	{
		ev->AddInteger(0);
	}
}


void PlayerNF::AddKillsEventAA(Event* ev)
{
	if (current_team)
		current_team->AddKillsAA((Player*)realPlayer, ev->GetInteger(1));
	
}

void PlayerNF::AddDeathsEventAA(Event* ev)
{
	if (current_team)
		current_team->AddDeathsAA((Player*)realPlayer, ev->GetInteger(1));
}

void PlayerNF::BindWeapEventAA(Event* ev)
{
	ItemAA* itm = (ItemAA*)ev->GetEntity(1);
	if (itm->owner == (SentientAA*)realPlayer)
	{
		itm->owner = nullptr;
	}
	else
	{
		itm->owner = (SentientAA*)realPlayer;
	}
}