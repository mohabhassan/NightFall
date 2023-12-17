#include "sv_commands.h"
#include "ScriptedEvent.h"
#include <vector>
#include "ClientAdmin.h"
#include "g_misc.h"
#include "sv_misc.h"
#include "nf_misc.h"
#include "AddressDefinitions.h"
#include "detours.h"
#include <string>
using namespace std;

vector<ConsoleCommand> ConsoleCommands = {
	{"kick",					SV_Kick2},
	{"kickr",					SV_KickReason},
	{"clientkick",				SV_ClientKick2},
	{"clientkickr",				SV_ClientKickReason},
	{"banip",					SV_BanIP},
	{"banipr",					SV_BanIPReason},
	{"banid",					SV_ClientBan},
	{"banidr",					SV_ClientBanReason},
	{"unbanip",					SV_UnbanIP},
	{"listips",					SV_ListIPs},
	{"banname",					SV_BanName},
	{"unbanname",				SV_UnbanName},
	{"listnames",				SV_ListNames},
	{"protname",				SV_ProtectName},
	{"unprotname",				SV_UnprotectName},
	{"listprotnames",			SV_ListProtectedNames},
	{"chatfilteradd",			SV_BanWord},
	{"chatfilterremove",		SV_UnbanWord},
	{"listchatfilter",			SV_ListWords},
	{"dischat",					SV_DisableChat},
	{"distaunt",				SV_DisableTaunts},
	{"sayp",					SV_SayPrivate},
	{"listadmins",				SV_ListAdmins},
	{"patchver",				SV_PatchVersion},
};

xcommand_t SV_MapRestart_original;
xcommand_t SV_Map_original;
xcommand_t SV_GameMap_original;

xcommand_t SV_Kick_f_original;
xcommand_t SV_KickNum_f_original;

bool Cmd_HookCommand(const char* cmd_name, xcommand_t *oldFunc, xcommand_t newFunc)
{
	static cmd_function_t **cmd_functions = reinterpret_cast<cmd_function_t **>((int)CMDFUNCTIONS_ADDR);
	cmd_function_t	*cmd;
	for (cmd = *cmd_functions; cmd; cmd = cmd->next)
	{
		if (!strcmp(cmd_name, cmd->name))
		{

			/*
			//hook using detours
			*oldFunc = cmd->function;

			bool ok = true;
			ok = ok && (DetourTransactionBegin() == NO_ERROR);
			ok = ok && (DetourUpdateThread(GetCurrentThread()) == NO_ERROR);
			ok = ok && (DetourAttach((PVOID*)(oldFunc), (PVOID)(newFunc)) == NO_ERROR);
			ok = ok && (DetourTransactionCommit() == NO_ERROR);
			return ok;
			*/

			*oldFunc = cmd->function;
			cmd->function = newFunc;
			return true;
		}
	}
	return false;
}

bool Cmd_UnHookCommand(xcommand_t oldFunc, xcommand_t newFunc)
{
	static cmd_function_t **cmd_functions = reinterpret_cast<cmd_function_t **>((int)CMDFUNCTIONS_ADDR);
	cmd_function_t	*cmd;
	for (cmd = *cmd_functions; cmd; cmd = cmd->next)
	{
		if (cmd->function == newFunc)
		{
			cmd->function = oldFunc;
			return true;
		}
	}
	return false;
}

void SV_MapRestart()
{
	ScriptedEvent sev(SEV_INTERMISSION);
	if (sev.isRegistered())
	{
		sev.Trigger({ INTERM_RESTART });
	}

	//need to unhook & redirect using SendConsoleCommand
	//because SV_MapRestart_original actually causes our dll to unload (when mapname!=last_mapname)
	//which will invalidate the function return address in the stack as our dll is unloaded

	if (Cmd_UnHookCommand(SV_MapRestart_original, &SV_MapRestart))
	{
		//string args = gi->Args();
		gi->SendConsoleCommand("restart\n");
	}
	else
		gi->Printf(PATCH_NAME " error: SV_MapRestart could not unhook command!\n");
	//SV_MapRestart_original();
}

void SV_Map()
{
	{
		ScriptedEvent sev(SEV_INTERMISSION);

		if (sev.isRegistered())
		{
			sev.Trigger({ INTERM_MAP });
		}
	}
	//need to unhook & redirect using SendConsoleCommand
	//because SV_Map_original actually causes our dll to unload
	//which will invalidate the function return address in the stack as our dll is unloaded

	if (Cmd_UnHookCommand(SV_Map_original, &SV_Map))
	{
		string args = gi->Args();
		gi->SendConsoleCommand(("map " + args + "\n").c_str());
	}
	else
		gi->Printf(PATCH_NAME " error: SV_Map could not unhook command!\n");
	//SV_Map_original();
}

void SV_GameMap()
{
	ScriptedEvent sev(SEV_INTERMISSION);

	if (sev.isRegistered())
	{
		sev.Trigger({ INTERM_MAP });
	}

	//need to unhook & redirect using SendConsoleCommand
	//because SV_GameMap_original actually causes our dll to unload
	//which will invalidate the function return address in the stack as our dll is unloaded

	if (Cmd_UnHookCommand(SV_GameMap_original, &SV_GameMap))
	{
		string args = gi->Args();
		gi->SendConsoleCommand(("gamemap " + args + "\n").c_str());
	}
	else
		gi->Printf(PATCH_NAME " error: SV_GameMap could not unhook command!\n");
	//SV_GameMap_original();
}


void SV_Commands_Init()
{
	bool success;
	success = Cmd_HookCommand("restart", &SV_MapRestart_original, &SV_MapRestart);
	if (!success)
	{
		gi->Printf(PATCH_NAME " INIT ERROR: failed to hook SV_MapRestart !\n");
	}
	success = Cmd_HookCommand("map", &SV_Map_original, &SV_Map);
	if (!success)
	{
		gi->Printf(PATCH_NAME " INIT ERROR: failed to hook SV_Map !\n");
	}
	success = Cmd_HookCommand("gamemap", &SV_GameMap_original, &SV_GameMap);
	if (!success)
	{
		gi->Printf(PATCH_NAME " INIT ERROR: failed to hook SV_GameMap !\n");
	}
	success = Cmd_HookCommand("kick", &SV_Kick_f_original, &SV_Kick2);
	if (!success)
	{
		gi->Printf(PATCH_NAME " INIT ERROR: failed to hook SV_Kick_f !\n");
	}
	success = Cmd_HookCommand("clientkick", &SV_KickNum_f_original, &SV_ClientKick2);
	if (!success)
	{
		gi->Printf(PATCH_NAME " INIT ERROR: failed to hook SV_KickNum_f !\n");
	}

	//add our stuff
	for (size_t i = 0; i < ConsoleCommands.size(); i++)
	{
		gi->AddCommand(ConsoleCommands[i].GetCommand().c_str(), NULL);
	}
}

bool SV_Commands_HandleCommand()
{
	const char *cmd;
	cmd = gi->Argv(0);

	for (size_t i = 0; i < ConsoleCommands.size(); i++)
	{
		if (stricmp(cmd, ConsoleCommands[i].GetCommand().c_str()) == 0)
		{
			ConsoleCommands[i].Execute();
			return true;
		}
	}
	return false;
}

void SV_Commands_Shutdown()
{
	Cmd_UnHookCommand(SV_Map_original, &SV_Map);
	Cmd_UnHookCommand(SV_GameMap_original, &SV_GameMap);
	Cmd_UnHookCommand(SV_MapRestart_original, &SV_MapRestart);
	
	Cmd_UnHookCommand(SV_Kick_f_original, &SV_Kick2);
	Cmd_UnHookCommand(SV_KickNum_f_original, &SV_ClientKick2);
}

/* same behaviour as normal kicks, but displays to the kicked user that he was kicked. */
/* original game behaviour will display a "server disconnected" message instead of "kicked from server". */
void SV_Kick2()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: kick <name>\n");
		return;
	}

	gentity_t* gent = G_GetEntityByClientName(gi->Argv(1));
	if (gent)
	{
		GEntity ge(gent);
		admin.AddKick(ge->client->ps.clientNum);
		gi->DropClient(ge->client->ps.clientNum, "was kicked");
	}
	else
	{
		gi->Printf("Client name not in server\n");
		return;
	}
}

void SV_KickReason()
{

	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 3)
	{
		gi->Printf("USAGE: kickr <name> <reason>\n");
		return;
	}

	gentity_t *gent = G_GetEntityByClientName(gi->Argv(1));
	if (gent)
	{
		string reason = gi->Argv(2);
		GEntity ge(gent);
		admin.AddKick(ge->client->ps.clientNum, true, reason.c_str());
		gi->DropClient(ge->client->ps.clientNum, ("has been kicked for " + reason).c_str());
	}
	else
	{
		gi->Printf("Client name not in server\n");
		return;
	}
}

/* same behaviour as normal kicks, but displays to the kicked user that he was kicked. */
/* original game behaviour will display a "server disconnected" message instead of "kicked from server". */

void SV_ClientKick2()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: clientkick <num>\n");
		return;
	}

	client_t* cl_actual = GetClientByClientNum(atoi(gi->Argv(1)));
	if (cl_actual && Client(cl_actual)->state != CS_FREE)
	{
		Client cl(cl_actual);
		admin.AddKick(cl->gentity->client->ps.clientNum);
		gi->DropClient(cl->gentity->client->ps.clientNum, "was kicked");
	}
	else
	{
		gi->Printf("Client num not in server\n");
		return;
	}
}

void SV_ClientKickReason()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 3)
	{
		gi->Printf("USAGE: clientkickr <num> <reason>\n");
		return;
	}

	client_t * cl_actual = GetClientByClientNum(atoi(gi->Argv(1)));
	if (cl_actual && Client(cl_actual)->state != CS_FREE)
	{
		string reason = gi->Argv(2);
		Client cl(cl_actual);
		admin.AddKick(cl->gentity->client->ps.clientNum, true, reason.c_str());
		gi->DropClient(cl->gentity->client->ps.clientNum, ("has been kicked for " + reason).c_str());
	}
	else
	{
		gi->Printf("Client num not in server\n");
		return;
	}
}

void SV_BanIP()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: banip <ip>\n");
		return;
	}
	string ip = gi->Argv(1);//TODO: kick all matching ips

	if (!validateIP(ip.c_str()))
	{
		gi->Printf("Invalid IP format!\n");
		return;
	}

	if (admin.AddIPBan(ip.c_str()))
	{
		gi->Printf("IP %s banned successfully.\n", ip.c_str());
		return;
	}
	else
	{
		gi->Printf("IP %s already banned.\n", ip.c_str());
		return;
	}
}

//This is weird, reason str is not used, ever.
void SV_BanIPReason()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 3)
	{
		gi->Printf("USAGE: banipr <ip> <reason\n");
		return;
	}

	string ip = gi->Argv(1);
	if (!validateIP(ip.c_str()))
	{
		gi->Printf("Invalid IP format!\n");
		return;
	}

	string reason = gi->Argv(2);//TODO: kick all matching ips with reason

	if (admin.AddIPBan(ip.c_str()))
	{
		gi->Printf("IP %s banned successfully.\n", ip.c_str());
		return;
	}
	else
	{
		gi->Printf("IP %s already banned.\n", ip.c_str());
		return;
	}
}

void SV_ClientBan()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: banid <num>\n");
		return;
	}

	client_t * cl_actual = GetClientByClientNum(atoi(gi->Argv(1)));
	if (cl_actual && Client(cl_actual)->state != CS_FREE)
	{
		Client cl(cl_actual);
		//string reason = gi->Argv(2);
		admin.AddBan(cl->gentity->client->ps.clientNum, true);
		gi->DropClient(cl->gentity->client->ps.clientNum, "was banned");
	}
	else
	{
		gi->Printf("Client num not in server\n");
		return;
	}
}

void SV_ClientBanReason()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 3)
	{
		gi->Printf("USAGE: banid <num>\n");
		return;
	}

	client_t * cl_actual = GetClientByClientNum(atoi(gi->Argv(1)));
	if (cl_actual && Client(cl_actual)->state != CS_FREE)
	{
		Client cl(cl_actual);
		string reason = gi->Argv(2);
		admin.AddBan(cl->gentity->client->ps.clientNum, true, reason.c_str());
		gi->DropClient(cl->gentity->client->ps.clientNum, ("has been banned for " + reason).c_str());
	}
	else
	{
		gi->Printf("Client num not in server\n");
		return;
	}
}

void SV_UnbanIP()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: unbanip <ip>\n");
		return;
	}
	string ip = gi->Argv(1);
	if (admin.RemoveIPBan(ip.c_str()))
	{
		gi->Printf("IP removed from ban filter.");
	}
	else
	{
		gi->Printf("IP does not exist in ban filter.");
	}
}

void SV_ListIPs()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: listips <page_num>\n");
		return;
	}

	int page_num = atoi(gi->Argv(1));

	if (page_num < 1)
	{
		gi->Printf("Invalid page number.\n");
		return;
	}

	string iplist_str = admin.ListIPPage(page_num);
	gi->Printf("%s\n", iplist_str.c_str());
}

void SV_BanName()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() < 2 || gi->Argc() > 3)
	{
		gi->Printf("USAGE: banname <name> [any=0]\n");
		return;
	}
	string name = gi->Argv(1);
	if (name == "")
	{
		gi->Printf("Empty name\n");
		return;
	}

	if (gi->Argc() == 3)
	{
		bool any = atoi(gi->Argv(2));
		if (any)
		{
			name += " ~any";
		}
	}

	if (admin.AddNameBan(name.c_str()))
	{
		gi->Printf("Name %s banned successfully.\n", name.c_str());
		return;
	}
	else
	{
		gi->Printf("Name %s already banned.\n", name.c_str());
		return;
	}
}

void SV_UnbanName()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: unbanname <name>\n");
		return;
	}
	string name = gi->Argv(1);
	if (admin.RemoveNameBan(name.c_str()))
	{
		gi->Printf("Name removed from ban filter.\n");
	}
	else
	{
		gi->Printf("Name does not exist in ban filter.\n");
	}
}

void SV_ListNames()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: listnames <page_num>\n");
		return;
	}

	int page_num = atoi(gi->Argv(1));
	if (page_num < 1)
	{
		gi->Printf("Invalid page number.\n");
		return;
	}
	string namelist_str = admin.ListNamePage(page_num);
	gi->Printf("%s\n", namelist_str.c_str());
}

void SV_ProtectName()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 3)
	{
		gi->Printf("USAGE: protname <name> <password>\n");
		return;
	}
	string name = gi->Argv(1);
	string password = gi->Argv(2);

	if (name == "")
	{
		gi->Printf("Empty name!\n");
		return;
	}

	if (password == "")
	{
		gi->Printf("Empty password!\n");
		return;
	}

	if (admin.AddProtectedName(name.c_str(), password.c_str()))
	{
		gi->Printf("Name %s protected successfully.\n", name.c_str());
		return;
	}
	else
	{
		gi->Printf("Name %s already protected.\n", name.c_str());
		return;
	}
}

void SV_UnprotectName()
{
	ClientAdmin admin(rconClientNum);


	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: unprotname <name>\n");
		return;
	}

	string name = gi->Argv(1);
	if (admin.RemoveProtectedName(name.c_str()))
	{
		gi->Printf("Name removed from protected filter.\n");
	}
	else
	{
		gi->Printf("Name does not exist in protected filter.\n");
	}
}

void SV_ListProtectedNames()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: listprotnames <page_num>\n");
		return;
	}

	int page_num = atoi(gi->Argv(1));
	if (page_num < 1)
	{
		gi->Printf("Invalid page number.\n");
		return;
	}
	string namelist_str = admin.ListProtectedNamePage(page_num);
	gi->Printf("%s\n", namelist_str.c_str());
}

void SV_BanWord()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: chatfilteradd <word>\n");
		return;
	}


	string word = gi->Argv(1);
	if (word == "")
	{
		gi->Printf("Empty word!\n");
		return;
	}

	if (admin.AddChatBan(word.c_str()))
	{
		gi->Printf("Word %s banned from chat successfully.\n", word.c_str());
		return;
	}
	else
	{
		gi->Printf("Word %s already banned from chat.\n", word.c_str());
		return;
	}
}

void SV_UnbanWord()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: chatfilterremove <word>\n");
		return;
	}


	string word = gi->Argv(1);

	if (admin.RemoveChatBan(word.c_str()))
	{
		gi->Printf("Word removed from chat filter.\n");
		return;
	}
	else
	{
		gi->Printf("Word does not exist in chat filter.\n");
		return;
	}
}

void SV_ListWords()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: listchatfilter <page_num>\n");
		return;
	}

	int page_num = atoi(gi->Argv(1));
	if (page_num < 1)
	{
		gi->Printf("Invalid page number.\n");
		return;
	}
	string wordlist_str = admin.ListChatPage(page_num);
	gi->Printf("%s\n", wordlist_str.c_str());
}

void SV_DisableChat()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: dischat <client_num>\n");
		return;
	}

	int client_num = atoi(gi->Argv(1));
	bool chatAllowed;
	bool bSuccess = admin.DisableChat(client_num, chatAllowed);
	if (bSuccess)
	{
		gi->Printf("%s chat for client %d\n", (chatAllowed ? "Enabled" : "Disabled"), client_num);
	}
	else
	{
		gi->Printf("Client num %d not in server.\n", client_num);
	}
}

void SV_DisableTaunts()
{
	ClientAdmin admin(rconClientNum);

	if (gi->Argc() != 2)
	{
		gi->Printf("USAGE: distaunt <client_num>\n");
		return;
	}

	int client_num = atoi(gi->Argv(1));
	bool tauntsAllowed;
	bool bSuccess = admin.DisableTaunts(client_num, tauntsAllowed);
	if (bSuccess)
	{
		gi->Printf("%s taunts for client %d\n", (tauntsAllowed ? "Enabled" : "Disabled"), client_num);
	}
	else
	{
		gi->Printf("Client num %d not in server.\n", client_num);
	}
}

void SV_SayPrivate()
{
	ClientAdmin admin(rconClientNum);
	if (gi->Argc() < 3)
	{
		gi->Printf("USAGE: sayp <client_num> <message>\n");
		return;
	}

	int client_num = atoi(gi->Argv(1));
	client_t* cl = GetClientByClientNum(client_num);
	if (!cl || Client(cl)->state == CS_FREE)
	{
		gi->Printf("Client num not in server.\n");
		return;
	}

	string msgStr;
	for (size_t i = 2; i < gi->Argc(); i++)
	{
		msgStr += gi->Argv(i);
		msgStr += " ";
	}

	msgStr.pop_back();//remove last space

	SendGameMessage(client_num, HUD_MESSAGE_CHAT_WHITE, ("console: " + msgStr + "\n").c_str());
}

void SV_ListAdmins()
{
	ClientAdmin admin(rconClientNum);

	gi->Printf("%s\n", admin.ListOnlineAdmins().c_str());
}

void SV_PatchVersion()
{
	gi->Printf(PATCH_NAME " version " PATCH_VERSION " (" PATCH_STAGE ")\n");
	gi->Printf("================\n");
}