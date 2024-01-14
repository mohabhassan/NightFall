#include "Winsock2.h"
#include "Player.h"
#include "ClientAdmin.h"
#include "g_misc.h"
#include "nf_misc.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "sv_misc.h"

using namespace std;
void PlayerNF::AdminCommandsInit()
{
	/////////////////////////////////
	// login/logout
	cerSet.AddEventResponse(new Event(
		"ad_login",
		EV_CONSOLE,
		"ss",
		"login password",
		"admin login with login and password"
	),
		&PlayerNF::PreAdminLoginEvent);
	cerSet.AddEventResponse(new Event(
		"ad_logout",
		EV_CONSOLE,
		NULL,
		NULL,
		"admin logout"
	),
		&PlayerNF::PreAdminLogoutEvent);
	// login/logout
	/////////////////////////////////

	/////////////////////////////////
	// kick
	cerSet.AddEventResponse(new Event(
		"ad_kick",
		EV_CONSOLE,
		"s",
		"name",
		"kick player name"
	),
		&PlayerNF::PreAdminKickEvent);

	cerSet.AddEventResponse(new Event(
		"ad_kickr",
		EV_CONSOLE,
		"ss",
		"name reason",
		"kick player name with reason"
	),
		&PlayerNF::PreAdminKickReasonEvent);

	cerSet.AddEventResponse(new Event(
		"ad_clientkick",
		EV_CONSOLE,
		"s",
		"name",
		"kick player name"
	),
		&PlayerNF::PreAdminClientKickEvent);

	cerSet.AddEventResponse(new Event(
		"ad_clientkickr",
		EV_CONSOLE,
		"ss",
		"name reason",
		"kick player name with reason"
	),
		&PlayerNF::PreAdminClientKickReasonEvent);

	// kick
	/////////////////////////////////

	/////////////////////////////////
	// ban
	cerSet.AddEventResponse(new Event(
		"ad_banid",
		EV_CONSOLE,
		"i",
		"clientnum",
		"ban player with clientnum"
	),
		&PlayerNF::PreAdminClientBanEvent);

	cerSet.AddEventResponse(new Event(
		"ad_banidr",
		EV_CONSOLE,
		"is",
		"clientnum reason",
		"ban player with clientnum for reason"
	),
		&PlayerNF::PreAdminClientBanReasonEvent);

	cerSet.AddEventResponse(new Event(
		"ad_banip",
		EV_CONSOLE,
		"s",
		"ip",
		"ban ip"
	),
		&PlayerNF::PreAdminBanIPEvent);

	cerSet.AddEventResponse(new Event(
		"ad_banipr",
		EV_CONSOLE,
		"s",
		"ip",
		"ban ip with reason"
	),
		&PlayerNF::PreAdminBanIPReasonEvent);

	cerSet.AddEventResponse(new Event(
		"ad_unbanip",
		EV_CONSOLE,
		"s",
		"ip",
		"remove ip from ban list"
	),
		&PlayerNF::PreAdminUnbanIPEvent);

	cerSet.AddEventResponse(new Event(
		"ad_listips",
		EV_CONSOLE,
		"i",
		"page_num",
		"list ips in page_num"
	),
		&PlayerNF::PreAdminListIPsEvent);

	// ban
	/////////////////////////////////

	/////////////////////////////////
	// name ban

	cerSet.AddEventResponse(new Event(
		"ad_banname",
		EV_CONSOLE,
		"sI",
		"name any",
		"ban specific name"
	),
		&PlayerNF::PreAdminBanNameEvent);

	cerSet.AddEventResponse(new Event(
		"ad_unbanname",
		EV_CONSOLE,
		"s",
		"name",
		"unban specific name"
	),
		&PlayerNF::PreAdminUnbanNameEvent);

	cerSet.AddEventResponse(new Event(
		"ad_listnames",
		EV_CONSOLE,
		"i",
		"page_num",
		"list names in page_num"
	),
		&PlayerNF::PreAdminListNamesEvent);
	// name ban
	/////////////////////////////////

	/////////////////////////////////
	// protected name

	cerSet.AddEventResponse(new Event(
		"ad_protname",
		EV_CONSOLE,
		"ss",
		"name password",
		"protect specific name with password"
	),
		&PlayerNF::PreAdminProtectNameEvent);

	cerSet.AddEventResponse(new Event(
		"ad_unprotname",
		EV_CONSOLE,
		"s",
		"name",
		"unprotect specific name"
	),
		&PlayerNF::PreAdminUnprotectNameEvent);

	cerSet.AddEventResponse(new Event(
		"ad_listprotnames",
		EV_CONSOLE,
		"i",
		"page_num",
		"list protected names in page_num"
	),
		&PlayerNF::PreAdminListProtectedNamesEvent);
	// protected name
	/////////////////////////////////

	/////////////////////////////////
	// chat ban

	cerSet.AddEventResponse(new Event(
		"ad_chatfilteradd",
		EV_CONSOLE,
		"s",
		"word",
		"ban word from chat"
	),
		&PlayerNF::PreAdminBanWordEvent);

	cerSet.AddEventResponse(new Event(
		"ad_chatfilterremove",
		EV_CONSOLE,
		"s",
		"word",
		"unban specific word from chat"
	),
		&PlayerNF::PreAdminUnbanWordEvent);

	cerSet.AddEventResponse(new Event(
		"ad_listchatfilter",
		EV_CONSOLE,
		"i",
		"page_num",
		"list banned chat words in page_num"
	),
		&PlayerNF::PreAdminListWordsEvent);

	cerSet.AddEventResponse(new Event(
		"ad_dischat",
		EV_CONSOLE,
		"i",
		"client_num",
		"toggle allow chat for client_num"
	),
		&PlayerNF::PreAdminDisableChatEvent);

	cerSet.AddEventResponse(new Event(
		"ad_distaunt",
		EV_CONSOLE,
		"i",
		"client_num",
		"toggle allow taunts for client_num"
	),
		&PlayerNF::PreAdminDisableTauntsEvent);
	// chat ban
	/////////////////////////////////

	/////////////////////////////////
	// misc

	cerSet.AddEventResponse(new Event(
		"ad_map",
		EV_CONSOLE,
		"s",
		"mapname",
		"change map to mapname"
	),
		&PlayerNF::PreAdminChangeMapEvent);


	cerSet.AddEventResponse(new Event(
		"ad_restart",
		EV_CONSOLE,
		NULL,
		NULL,
		"restart map"
	),
		&PlayerNF::PreAdminRestartEvent);


	cerSet.AddEventResponse(new Event(
		"ad_fraglimit",
		EV_CONSOLE,
		"i",
		"fraglimit",
		"set fraglimit"
	),
		&PlayerNF::PreAdminSetFragLimitEvent);


	cerSet.AddEventResponse(new Event(
		"ad_timelimit",
		EV_CONSOLE,
		"i",
		"timelimit",
		"set timelimit"
	),
		&PlayerNF::PreAdminSetTimeLimitEvent);


	cerSet.AddEventResponse(new Event(
		"ad_gametype",
		EV_CONSOLE,
		"i",
		"gametype",
		"set gametype"
	),
		&PlayerNF::PreAdminSetGameTypeEvent);


	cerSet.AddEventResponse(new Event(
		"ad_say",
		EV_CONSOLE,
		"s",
		"message",
		"say message as console"
	),
		&PlayerNF::PreAdminSayEvent);


	cerSet.AddEventResponse(new Event(
		"ad_sayp",
		EV_CONSOLE,
		"is",
		"client_num message",
		"say private message to client_num as console"
	),
		&PlayerNF::PreAdminSayPrivateEvent);


	cerSet.AddEventResponse(new Event(
		"ad_status",
		EV_CONSOLE,
		NULL,
		NULL,
		"print player status"
	),
		&PlayerNF::PreAdminStatusEvent);


	cerSet.AddEventResponse(new Event(
		"ad_listadmins",
		EV_CONSOLE,
		NULL,
		NULL,
		"list loggedin admins"
	),
		&PlayerNF::PreAdminListAdminsEvent);

	cerSet.AddEventResponse(new Event(
		"ad_rcon",
		EV_CONSOLE,
		"s",
		"command",
		"execute command in console"
	),
		&PlayerNF::PreAdminRCONEvent);

	// misc
	/////////////////////////////////
}


void PlayerNF::AdminLoginEvent(Event * ev)
{

	if (ev->NumArgs() != 2)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_login <login> <password>\n\"");
		return;
	}

	str login = ev->GetString(1);
	str password = ev->GetString(2);

	ClientAdmin admin(client->ps.clientNum);

	if (!admin.attemptLogin(login.c_str(), password.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Invalid login or password\n\"");
		return;
	}

	gi->SendServerCommand(client->ps.clientNum, "hudprint \"Admin System> You have been authed as admin \n\"");


	gi->Printf(PATCH_NAME " INFO: %s (%s) (%d) logged IN as admin using login \"%s\" and password \"%s\"\n", GetIPPortFromClient(GetClientByClientNum(client->ps.clientNum)).c_str(), client->pers.netname, client->ps.clientNum, login.c_str(), password.c_str());

}

void PlayerNF::AdminLogoutEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);
	if (!admin.attemptLogout())
	{
		return;
	}

	gi->SendServerCommand(client->ps.clientNum, "hudprint \"Admin System> You have logged out as admin \n\"");
	gi->Printf(PATCH_NAME " INFO: %s (%s) (%d) logged OUT as admin\n", GetIPPortFromClient(GetClientByClientNum(client->ps.clientNum)).c_str(), client->pers.netname, client->ps.clientNum);

}

void PlayerNF::AdminKickEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Kick))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_kick <name>\n\"");
		return;
	}

	gentity_t *gent = G_GetEntityByClientName(ev->GetString(1).c_str());
	if (gent)
	{
		GEntity ge(gent);
		admin.AddKick(GClient(ge->client)->ps.clientNum);
		gi->DropClient(GClient(ge->client)->ps.clientNum, "was kicked");
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client name not in server\n\"");
		return;
	}
}

void PlayerNF::AdminKickReasonEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Kick))
	{
		return;
	}

	if (ev->NumArgs() != 2)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_kickr <name> <reason>\n\"");
		return;
	}

	gentity_t *gent = G_GetEntityByClientName(ev->GetString(1).c_str());
	str reason = ev->GetString(2);
	if (gent)
	{
		GEntity ge(gent);
		admin.AddKick(GClient(ge->client)->ps.clientNum, true, reason.c_str());
		gi->DropClient(GClient(ge->client)->ps.clientNum, ("has been kicked for " + reason).c_str());
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client name not in server\n\"");
		return;
	}
}

void PlayerNF::AdminClientKickEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Kick))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_clientkick <number>\n\"");
		return;
	}

	gentity_t *gent = G_GetEntityByClient(ev->GetInteger(1));
	if (gent)
	{
		GEntity ge(gent);
		admin.AddKick(GClient(ge->client)->ps.clientNum);
		gi->DropClient(GClient(ge->client)->ps.clientNum, "was kicked");
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client num not in server\n\"");
		return;
	}
}

void PlayerNF::AdminClientKickReasonEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Kick))
	{
		return;
	}

	if (ev->NumArgs() != 2)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_clientkickr <number> <reason>\n\"");
		return;
	}

	gentity_t *gent = G_GetEntityByClient(ev->GetInteger(1));
	str reason = ev->GetString(2);
	if (gent)
	{
		GEntity ge(gent);
		admin.AddKick(GClient(ge->client)->ps.clientNum, true, reason.c_str());
		gi->DropClient(GClient(ge->client)->ps.clientNum, ("has been kicked for " + reason).c_str());
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client num not in server\n\"");
		return;
	}
}

void PlayerNF::AdminBanIPEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Ban))
	{
		return;
	}
	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_banip <ip>\n\"");
		return;
	}
	str ip = ev->GetString(1);//TODO: kick all matching ips

	if (!validateIP(ip.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Invalid IP format!\n\"");
		return;
	}

	if (admin.AddIPBan(ip.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"IP %s banned successfully.\n\"", ip.c_str());
		return;
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"IP %s already banned.\n\"", ip.c_str());
		return;
	}

}

//This is weird, reason str is not used, ever.
void PlayerNF::AdminBanIPReasonEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Ban))
	{
		return;
	}
	if (ev->NumArgs() != 2)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_banipr <ip> <reason>\n\"");
		return;
	}
	str ip = ev->GetString(1);
	str reason = ev->GetString(2);//TODO: kick all matching ips with reason
	if (!validateIP(ip.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Invalid IP format!\n\"");
		return;
	}

	if (admin.AddIPBan(ip.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"IP %s banned successfully.\n\"", ip.c_str());
		return;
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"IP %s already banned.\n\"", ip.c_str());
		return;
	}
}

void PlayerNF::AdminClientBanEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Ban))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_banid <number>\n\"");
		return;
	}

	gentity_t *gent = G_GetEntityByClient(ev->GetInteger(1));
	if (gent)
	{
		GEntity ge(gent);
		admin.AddBan(GClient(ge->client)->ps.clientNum);
		gi->DropClient(GClient(ge->client)->ps.clientNum, "was banned");
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client num not in server\n\"");
		return;
	}
}

void PlayerNF::AdminClientBanReasonEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Ban))
	{
		return;
	}

	if (ev->NumArgs() != 2)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_banidr <number> <reason>\n\"");
		return;
	}

	gentity_t *gent = G_GetEntityByClient(ev->GetInteger(1));
	str reason = ev->GetString(2);
	if (gent)
	{
		GEntity ge(gent);
		admin.AddBan(GClient(ge->client)->ps.clientNum, true, reason.c_str());
		gi->DropClient(GClient(ge->client)->ps.clientNum, ("has been banned for " + reason).c_str());
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client num not in server\n\"");
		return;
	}
}

void PlayerNF::AdminUnbanIPEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::RemoveBan))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_unbanip <ip>\n\"");
		return;
	}
	str ip = ev->GetString(1);
	if (admin.RemoveIPBan(ip.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"IP removed from ban filter.\n\"");
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"IP does not exist in ban filter.\n\"");
	}
}

void PlayerNF::AdminListIPsEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || (!admin.hasRight(ClientAdmin::Ban) && !admin.hasRight(ClientAdmin::RemoveBan)))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_listips <page>\n\"");
		return;
	}

	int page_num = ev->GetInteger(1);
	if (page_num < 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Invalid page number.\n\"");
		return;
	}

	string iplist_str = admin.ListIPPage(page_num);
	G_PrintToClient(client->ps.clientNum, iplist_str.c_str());
}

void PlayerNF::AdminBanNameEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Ban))
	{
		return;
	}
	if (ev->NumArgs() < 1 || ev->NumArgs() > 2)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_banname <name> [any=0]\n\"");
		return;
	}
	str name = ev->GetString(1);
	if (name == "")
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Empty name!\n\"");
		return;
	}

	if (ev->NumArgs() == 2)
	{
		bool any = ev->GetBoolean(2);
		if (any)
		{
			name += " ~any";
		}
	}

	if (admin.AddNameBan(name.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Name %s banned successfully.\n\"", name.c_str());
		return;
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Name %s already banned.\n\"", name.c_str());
		return;
	}
}

void PlayerNF::AdminUnbanNameEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::RemoveBan))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_unbanname <name>\n\"");
		return;
	}
	str name = ev->GetString(1);
	if (admin.RemoveNameBan(name.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Name removed from ban filter.\n\"");
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Name does not exist in ban filter.\n\"");
	}
}

void PlayerNF::AdminListNamesEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || (!admin.hasRight(ClientAdmin::Ban) && !admin.hasRight(ClientAdmin::RemoveBan)))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_listnames <page>\n\"");
		return;
	}

	int page_num = ev->GetInteger(1);
	if (page_num < 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Invalid page number.\n\"");
		return;
	}
	string namelist_str = admin.ListNamePage(page_num);
	G_PrintToClient(client->ps.clientNum, namelist_str.c_str());
}

void PlayerNF::AdminProtectNameEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::ProtectName))
	{
		return;
	}
	if (ev->NumArgs() != 2)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_protname <name> <password>\n\"");
		return;
	}
	str name = ev->GetString(1);
	str password = ev->GetString(2);

	if (name == "")
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Empty name!\n\"");
		return;
	}

	if (password == "")
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Empty password!\n\"");
		return;
	}

	if (admin.AddProtectedName(name.c_str(), password.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Name %s protected successfully.\n\"", name.c_str());
		return;
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Name %s already protected.\n\"", name.c_str());
		return;
	}
}

void PlayerNF::AdminUnprotectNameEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::ProtectName))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_unprotname <name>\n\"");
		return;
	}
	str name = ev->GetString(1);
	if (admin.RemoveProtectedName(name.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Name removed from protected filter.\n\"");
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Name does not exist in protected filter.\n\"");
	}
}

void PlayerNF::AdminListProtectedNamesEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::ProtectName))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_listprotnames <page>\n\"");
		return;
	}

	int page_num = ev->GetInteger(1);
	if (page_num < 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Invalid page number.\n\"");
		return;
	}
	string namelist_str = admin.ListProtectedNamePage(page_num);
	G_PrintToClient(client->ps.clientNum, namelist_str.c_str());
}

void PlayerNF::AdminBanWordEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Chat))
	{
		return;
	}
	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_chatfilteradd <word>\n\"");
		return;
	}

	str word = ev->GetString(1);
	if (word == "")
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Empty word!\n\"");
		return;
	}

	if (admin.AddChatBan(word.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Word %s banned from chat successfully.\n\"", word.c_str());
		return;
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Word %s already banned from chat.\n\"", word.c_str());
		return;
	}
}

void PlayerNF::AdminUnbanWordEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Chat))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_chatfilterremove <word>\n\"");
		return;
	}
	str word = ev->GetString(1);
	if (admin.RemoveChatBan(word.c_str()))
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Word removed from chat filter.\n\"");
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Word does not exist in chat filter.\n\"");
	}
}

void PlayerNF::AdminListWordsEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Chat))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_listchatfilter <page>\n\"");
		return;
	}

	int page_num = ev->GetInteger(1);
	if (page_num < 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Invalid page number.\n\"");
		return;
	}
	string wordlist_str = admin.ListChatPage(page_num);
	G_PrintToClient(client->ps.clientNum, wordlist_str.c_str());
}

void PlayerNF::AdminDisableChatEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Chat))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_dischat <client_num>\n\"");
		return;
	}

	int client_num = ev->GetInteger(1);
	bool chatAllowed;
	bool bSuccess = admin.DisableChat(client_num, chatAllowed);
	if (bSuccess)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"%s chat for client %d\n\"", (chatAllowed ? "Enabled" : "Disabled"), client_num);
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client num %d not in server.\n\"", client_num);
	}
}

void PlayerNF::AdminDisableTauntsEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Chat))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_distaunt <client_num>\n\"");
		return;
	}

	int client_num = ev->GetInteger(1);
	bool tauntsAllowed;
	bool bSuccess = admin.DisableTaunts(client_num, tauntsAllowed);
	if (bSuccess)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"%s taunts for client %d\n\"", (tauntsAllowed ? "Enabled" : "Disabled"), client_num);
	}
	else
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client num %d not in server.\n\"", client_num);
	}
}

void PlayerNF::AdminChangeMapEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::MapChange))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_map <mapname>\n\"");
		return;
	}

	str mapname = ev->GetString(1);

	gi->SendConsoleCommand(("map " + mapname + "\n").c_str());
}

void PlayerNF::AdminRestartEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Restart))
	{
		return;
	}
	gi->SendConsoleCommand("restart\n");
}

void PlayerNF::AdminSetFragLimitEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::FragLimit))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_fraglimit <fraglimit>\n\"");
		return;
	}

	int fraglimit = ev->GetInteger(1);

	gi->SendConsoleCommand(("fraglimit " + to_string(fraglimit) + "\n").c_str());
}

void PlayerNF::AdminSetTimeLimitEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::TimeLimit))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_timelimit <timelimit>\n\"");
		return;
	}

	int timelimit = ev->GetInteger(1);

	gi->SendConsoleCommand(("timelimit " + to_string(timelimit) + "\n").c_str());
}

void PlayerNF::AdminSetGameTypeEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::GameType))
	{
		return;
	}

	if (ev->NumArgs() != 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_gametype <gametype>\n\"");
		return;
	}

	int gametype = ev->GetInteger(1);

	gi->SendConsoleCommand(("g_gametype " + to_string(gametype) + "\n").c_str());
}

void PlayerNF::AdminSayEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin())
	{
		return;
	}

	if (ev->NumArgs() < 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_say <message>\n\"");
		return;
	}
	str msgStr;
	for (size_t i = 1; i <= ev->NumArgs(); i++)
	{
		msgStr += ev->GetString(i);
		msgStr += " ";
	}

	msgStr -= 1;//remove last space

	gi->SendConsoleCommand(("say " + msgStr + "\n").c_str());
}

void PlayerNF::AdminSayPrivateEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin())
	{
		return;
	}

	if (ev->NumArgs() < 2)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_sayp <client_num> <message>\n\"");
		return;
	}

	int client_num = ev->GetInteger(1);
	client_t* cl = GetClientByClientNum(client_num);
	if (cl == NULL || Client(cl)->state == CS_FREE)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"Client num not in server.\n\"");
		return;
	}

	str msgStr;
	for (size_t i = 2; i <= ev->NumArgs(); i++)
	{
		msgStr += ev->GetString(i);
		msgStr += " ";
	}

	msgStr -= 1;//remove last space

	SendGameMessage(client_num, HUD_MESSAGE_CHAT_WHITE, ("console: " + msgStr + "\n").c_str());
}

extern int *svs_numclients;
void PlayerNF::AdminStatusEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin())
	{
		return;
	}
	stringstream ss;
	ss << "Num | ";
	ss << "Ping | ";
	ss << "Name | ";
	ss << "IP | ";
	ss << "Port | ";
	ss << "Rate";
	ss << endl;

	client_t * cl_real;
	for (size_t i = 0; i < *svs_numclients; i++)
	{
		cl_real = GetClientByClientNum(i);
		if (!cl_real || Client(cl_real)->state == CS_FREE)
		{
			continue;
		}
		Client cl(cl_real);
		ss << i << " | ";
		ss << cl->ping << " | ";
		ss << cl->name << " | ";
		ss << GetIPFromClient(cl) << " | ";
		ss << GetPortFromClient(cl) << " | ";
		ss << cl->rate << " | ";
		ss << endl;
	}
	ss << "=========================================================" << endl;
	gi->SendServerCommand(client->ps.clientNum, "print \"%s\"\n", ss.str().c_str());

}

void PlayerNF::AdminListAdminsEvent(Event * ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::ListAdmins))
	{
		return;
	}

	G_PrintToClient(client->ps.clientNum, admin.ListOnlineAdmins().c_str());
}

void PlayerNF::AdminRCONEvent(Event* ev)
{
	ClientAdmin admin(client->ps.clientNum);

	if (!admin.isAdmin() || !admin.hasRight(ClientAdmin::Rcon))
	{
		return;
	}

	if (ev->NumArgs() < 1)
	{
		gi->SendServerCommand(client->ps.clientNum, "print \"USAGE: ad_rcon <command>\n\"");
		return;
	}
	str cmdStr;
	for (size_t i = 1; i <= ev->NumArgs(); i++)
	{
		cmdStr += ev->GetString(i);
		cmdStr += " ";
	}

	cmdStr -= 1;//remove last space
	cmdStr += "\n";

	gi->SendConsoleCommand(cmdStr.c_str());
	gi->SendServerCommand(client->ps.clientNum, "print \"Executed RCON command.\n\"");
}
