#pragma once
#include "dgamex86.h"
#include <string>
using namespace std;
class ConsoleCommand
{
	string command;
	xcommand_t func;
public:
	ConsoleCommand(string cmd, xcommand_t fn)
	{
		command = cmd;
		func = fn;
	}

	string GetCommand() const
	{
		return command;
	}

	void Execute()
	{
		func();
	}

};

void SV_Commands_Init();
bool SV_Commands_HandleCommand();
void SV_Commands_Shutdown();



void SV_Kick2();
void SV_KickReason();
void SV_ClientKick2();
void SV_ClientKickReason();
void SV_BanIP();
void SV_BanIPReason();
void SV_ClientBan();
void SV_ClientBanReason();
void SV_UnbanIP();
void SV_ListIPs();
void SV_BanName();
void SV_UnbanName();
void SV_ListNames();
void SV_ProtectName();
void SV_UnprotectName();
void SV_ListProtectedNames();
void SV_BanWord();
void SV_UnbanWord();
void SV_ListWords();
void SV_DisableChat();
void SV_DisableTaunts();
void SV_SayPrivate();
void SV_ListAdmins();
void SV_PatchVersion();