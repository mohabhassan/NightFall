#include "Player.h"
#include "g_misc.h"
#include "ClientAdmin.h"

#define	BUTTON_ATTACK2		2	// +/-attacksecondary

void Player::MiscInit()
{
	cerSet.AddEventResponse(new Event(
		"getkills",
		EV_DEFAULT,
		NULL,
		NULL,
		"gets kills number of player",
		EV_RETURN
	),
		&Player::GetKillsEvent);
	cerSet.AddEventResponse(new Event(
		"getdeaths",
		EV_DEFAULT,
		NULL,
		NULL,
		"gets deaths number of player",
		EV_RETURN
	),
		&Player::GetDeathsEvent);
	cerSet.AddEventResponse(new Event(
		"getconnstate",
		EV_DEFAULT,
		NULL,
		NULL,
		"Gets state of player's connection.",
		EV_RETURN
	),
		&Player::GetConnStateEvent);
	cerSet.AddEventResponse(new Event(
		"getactiveweap",
		EV_DEFAULT,
		"i",
		"weapon_hand",
		"Gets currently active weapon from player's hand of given index.",
		EV_RETURN
	),
		&Player::GetActiveWeapEvent);
	cerSet.AddEventResponse(new Event(
		"secfireheld",
		EV_DEFAULT,
		NULL,
		NULL,
		"Returns 1 if player is holding secondary fire button.",
		EV_GETTER
	),
		&Player::SecFireHeldEvent);
	cerSet.AddEventResponse(new Event(
		"userinfo",
		EV_DEFAULT,
		NULL,
		NULL,
		"Returns player's userinfo.",
		EV_GETTER
	),
		&Player::GetUserInfoEvent);
	cerSet.AddEventResponse(new Event(
		"inventory",
		EV_DEFAULT,
		NULL,
		NULL,
		"Returns player's inventory.",
		EV_GETTER
	),
		&Player::GetInventoryEvent);

	cerSet.AddEventResponse(new Event(
		"isadmin",
		EV_DEFAULT,
		NULL,
		NULL,
		"Check if player is logged in as admin",
		EV_RETURN
	),
		&Player::IsAdminEvent);
#ifdef MOHAA

	cerSet.AddEventResponse(new Event(
		"addkills",
		EV_DEFAULT,
		"i",
		"numkills",
		"Adds number of kills to player. (Can be also negative)"
	),
		&Player::AddKillsEvent);

	cerSet.AddEventResponse(new Event(
		"adddeaths",
		EV_DEFAULT,
		"i",
		"numDeaths",
		"Adds number of deaths to player. (Can be also negative)"
	),
		&Player::AddDeathsEvent);
#endif // MOHAA

}

void Player::GetKillsEvent(Event *ev)
{
	ev->AddInteger(num_kills);
}

void Player::GetDeathsEvent(Event *ev)
{
	ev->AddInteger(num_deaths);
}

void Player::GetConnStateEvent(Event *ev)
{
	ev->AddInteger(client->pers.connectionState);
}

void Player::GetActiveWeapEvent(Event *ev)
{
	ev->AddListener(GetActiveWeapon((weaponhand_t)ev->GetInteger(1)));
}

void Player::SecFireHeldEvent(Event *ev)
{
	ev->AddInteger((bool)(buttons & BUTTON_ATTACK2));
}

void Player::GetUserInfoEvent(Event *ev)
{
	ev->AddString(client->pers.userinfo);
}

void Player::GetInventoryEvent(Event *ev)
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

void Player::IsAdminEvent(Event * ev)
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


#ifdef MOHAA

void Player::AddKillsEvent(Event* ev)
{
	current_team->AddKills(this, ev->GetInteger(1));
}

void Player::AddDeathsEvent(Event* ev)
{
	current_team->AddDeaths(this, ev->GetInteger(1));
}

#endif // MOHAA