#define INCL_DOSMODULEMGR
#include "dgamex86.h"
#include "misc.h"
#include "ihuddraw.h"
#include "detours.h"
#include "ClassDef.h"
#include "Player.h"
#include "ScriptThread.h"
#include "Director.h"
#include "ScriptedEvent.h"
#include "CustomCvar.h"
#include "ClientAdmin.h"
#include "IPFilter.h"
#include "NameFilter.h"
#include "ChatFilter.h"
#include "sv_commands.h"
#include "HTTPServer.h"
#include "HTTPClient.h"
#include "UpdateClient.h"
#include "ClientFilter.h"


//#include "hooks/script.h"

#ifdef _WIN32
	HMODULE hmod = NULL; //Windows
	HMODULE systemHMOD = NULL;
#else
	#define _GNU_SOURCE
	void *hmod = 0; //*Nix
#endif


/*
//------------------	Global Variables	------------------\\
*/

typedef void *(*pGetGameAPI_spec)( void *import );
pGetGameAPI_spec pGetGameAPI;


typedef void (__cdecl*pG_BeginIntermission2_spec)();
pG_BeginIntermission2_spec G_BeginIntermission2_original;

typedef void *(*pMemoryMalloc_spec)(int size);
pMemoryMalloc_spec pMemoryMalloc;

typedef void (*pMemoryFree_spec)(void *);
pMemoryFree_spec pMemoryFree;


GameImport	gi;
shared_ptr<BaseGameExport> globals;
BaseGameExport	globals_backup;

clientdata_t clients[32];
// GLOBALS NEEDED FOR NO-RECOIL DETECTION
int frames = 0;
int lastAnim = VMA_NUMANIMATIONS; //initializing
int start, middle, end;


extern DirectorClass* Director;
/*
//-----------------------	    End	   -----------------------\\
*/

/*
===========
RunFrame

Called per each frame, 20 times a second.
============
*/
void G_RunFrame(int svsTime, int frameTime)
{
	globals_backup.RunFrame()(svsTime, frameTime);

	//Server stuff
	//first: handle new requests
	HTTPServer::HandleNextAPIRequest();

	//second: check if older requests are processed.
	HTTPServer::HandleNextAPIResponse();

	//Client stuff:
	HTTPClient::HandleNextAPIResponse();
}

/*
===========
ClientBegin

called when a client has finished connecting, and is ready
to be placed into the level.  This will happen every level load,
and on transition between teams, but doesn't happen on respawns
============
*/
void G_ClientBegin(GEntity &gent, userCmd_t *cmd )
{

	//sizeof(playerState_t);//676
	//sizeof(entityState_t);
	//sizeof(gentity_t);
	//sizeof(int);		  //4
						  //1350
	//sizeof(client_persistant_t);//1588
	//gi.centerprintf(ent, "Welcome %s, have fun!", ent->client->pers.netname); //not working ?
	gi.centerprintf(gent, "Welcome %s, have fun!", gent->client->pers.netname);
	//gi.Printf("Player Name: %s : %d\n", ent->client->pers.netname, ent->client->ps.clientNum);

	globals_backup.ClientBegin()(gent, cmd );

	ScriptedEvent sev(SEV_CONNECTED);

	if (sev.isRegistered())
	{
		sev.Trigger({ (Entity*)gent->entity });
	}
}

/*
===========
ClientConnect

Called when a player begins connecting to the server.
Called again for every map change or tournement restart.

The session information will be valid after exit.

Return NULL if the client should be allowed, otherwise return
a string with the reason for denial.

Otherwise, the client will be sent the current gamestate
and will eventually get to ClientBegin.

firstTime will be qtrue the very first time a client connects
to the server machine, but qfalse on map changes and tournement
restarts.
============
*/

char* G_ClientConnect_Internal(int clientNum, qboolean firstTime)
{
	char* reason = NULL;
	client_t* cl = GetClientByClientNum(clientNum);
	if (!cl)
	{
		gi.Printf(PATCH_NAME " connect error: NULL client %d on G_ClientConnect_Internal! Ignoring...\n", clientNum);
		reason = NULL;
	}
	else
	{

		//IP related checks
		char* ip = Info_ValueForKey(cl->userinfo, "ip");
		if (ip == "")
		{
			gi.Printf(PATCH_NAME " connect error: empty client ip %d on G_ClientConnect_Internal! Ignoring...\n", clientNum);
			reason = NULL;
		}
		else
		{
			IPFilter filter;
			if (!filter.CanConnect(ip))
			{
				reason = "Banned IP.";
			}
			else if (!filter.CanConnectMaxConnections(clientNum))
			{
				reason = "Too many connection attempts from one IP.";
			}
			else
			{
				reason = NULL;
			}
		}

		//name related checks:
		if (reason == NULL)
		{
			char* name = Info_ValueForKey(cl->userinfo, "name");
			char* namepass = Info_ValueForKey(cl->userinfo, "cl_namepass");
			if (name == "")
			{
				gi.Printf(PATCH_NAME " connect error: empty client name %d on G_ClientConnect_Internal! Ignoring...\n", clientNum);
				reason = NULL;
			}
			else
			{
				NameFilter filter;
				if (!filter.CanConnect(name))
				{
					reason = "disallowed name or disallowed word in name.";
				}
				else if (!filter.CanConnectProtected(name, namepass))
				{
					reason = "using protected name w/o permission.";
				}
				else
				{
					reason = NULL;
				}
			}
		}

		//_fps skin bug check:
		if (reason == NULL)
		{
			if (CheckFPSSkin(cl->userinfo))
			{
				reason = "Your skins are invalid.\nPlease go to multiplayer options and change them.\n";
			}
			else
			{
				ClientFilter filter;
				filter.ClientConnected(clientNum, gi.Milliseconds());
			}
		}


	}

	if (reason == NULL)
	{
		ChatFilter filter;
		filter.ClientConnected(clientNum);
		return reason;
	}
	else
	{
		return reason;
	}
}

char* G_ClientConnect(int clientNum, qboolean firstTime, int a3)
{
	char* reason = G_ClientConnect_Internal(clientNum, firstTime);
	if (reason == NULL)
	{
		return globals_backup.ClientConnect()(clientNum, firstTime, a3);
	}
	else
	{
		return reason;
	}
}

char* G_ClientConnect(int clientNum, qboolean firstTime)
{
	char* reason = G_ClientConnect_Internal(clientNum, firstTime);
	if (reason == NULL)
	{
		auto actual_ClientConnect = (char* (*)(int, qboolean)) ((void*)globals_backup.ClientConnect());
		return actual_ClientConnect(clientNum, firstTime);
	}
	else
	{
		return reason;
	}
}

void G_ClientDisconnect(GEntity &ent)
{
	if (ent == NULL || ent->client == NULL || ent->entity == NULL)
	{
		globals_backup.ClientDisconnect()(ent);
		return;
	}

	ScriptedEvent sev(SEV_DISCONNECTED);

	if (sev.isRegistered())
	{
		sev.Trigger({ (Entity*)ent->entity });
	}
	int clientNum = ent->client->ps.clientNum;

	ClientAdmin admin(clientNum);
	admin.HandlePreDisconnect();
	globals_backup.ClientDisconnect()(ent);
	admin.HandlePostDisconnect();

	{
		ChatFilter filter;
		filter.ClientDisconnected(clientNum);
	}

	{
		ClientFilter filter;
		filter.ClientDisconnected(clientNum);
	}
}
/*
==============
ClientThink

This will be called once for each client frame, which will
usually be a couple times for each server frame on fast clients.

If "g_synchronousClients 1" is set, this will be called exactly
once for each server frame, which makes for smooth demo recording.
==============
*/
void G_ClientThink(GEntity &ent, userCmd_t *ucmd, userEyes_t *eyeInfo )
{
	ClientFilter filter;
	if (filter.CheckPingKick(ent->client->ps.clientNum, ent->client->ps.ping, ent))
	{
		ClientAdmin admin(internalClientNum);
		admin.AddKick(ent->client->ps.clientNum, true, "too high ping");
		gi.DropClient(ent->client->ps.clientNum, "has been kicked for too high ping");
	}

	globals_backup.ClientThink()( ent, ucmd, eyeInfo);
	
}



void  G_ClientCommand (GEntity &ent ){
	//gi.Argv(0) dmmessage Gi.Argv(1) 0 gi,Argv(2) blah gi.Args() 0 blah test
	//gi.Printf("\ngi.Argv(0) %s Gi.Argv(1) %s gi,Argv(2) %s gi.Args() %s\n", gi.Argv(0) ,gi.Argv(1) ,gi.Argv(2) ,gi.Args());
	char *cmd = gi.Argv(0);
	if (!strcmp(cmd, "keyp"))
	{
		char *idStr = gi.Argv(1);
		if (idStr)
		{
			long int id = strtol(idStr, NULL, 0);
			if (errno == ERANGE)
			{
				id = 0;
			}

			ScriptedEvent sev(SEV_KEYPRESS);

			if (sev.isRegistered())
			{
				sev.Trigger({ (Entity*)ent->entity, id});
			}
		}
	}
	else if (!strcmp(cmd, "scmd"))
	{
		int numArgs = gi.Argc();
		str cmdStr = gi.Argv(1);
		if (cmdStr)
		{
			str argsStr = "";
			for (size_t i = 2; i < numArgs; i++)
			{
				argsStr += gi.Argv(i);
				argsStr += " ";
			}
			argsStr -= 1;//remove last space

			ScriptedEvent sev(SEV_SERVERCOMMAND);

			if (sev.isRegistered())
			{
				sev.Trigger({ (Entity*)ent->entity, cmdStr, argsStr });
			}
		}
	}
	else if (!strcmp(cmd, "dmmessage"))
	{
			int numArgs = gi.Argc();
			if (numArgs >= 3)
			{
				vector<string> args;
				//sayteam test1 test2 test3 test4 test5 sdfgfsg
				//args are:
				//clientnum part1 part2 part3 part4 ...
				//example:
				//1 test1 test2 test3 test4 ...
				//
				//test1 is arg 2
				//sayteam is -1
				//normal say is 0
				//sayprivate & sayone: clientnum is actualy clientnum (it's a bit fuzzy when using sv_privateclients)
				for (size_t i = 2; i < numArgs; i++)
				{
					args.push_back(gi.Argv(i));
				}
				
				bool shouldKick;
				string reason;
				ChatFilter filter;
				if (!filter.CanSend(args, ent->client->ps.clientNum, shouldKick, reason))
				{
					if (shouldKick)
					{
						ClientAdmin admin(internalClientNum);
						admin.AddKick(ent->client->ps.clientNum, true, reason.c_str());
						gi.DropClient(ent->client->ps.clientNum, ("has been kicked for " + reason).c_str());
					}
					else
					{
						gi.SendServerCommand(ent->client->ps.clientNum, "hudprint \"%s\n\"", reason.c_str());
					}
					return;
				}

				try
				{
					int target = stoi(gi.Argv(1));
					if (!filter.CheckScriptCallback(args, ent, target))
					{
						return;
					}
				}
				catch (const std::exception&)
				{
					gi.Printf(PATCH_NAME " dmmessage error: invalid chat target %s or invalid script return value ! Ignoring...\n", gi.Argv(1));
				}
			}
	}
	globals_backup.ClientCommand()(ent);
}

void G_ClientUserinfoChanged(GEntity &gent, char *userInfo)
{
	char * name = Info_ValueForKey(userInfo, "name");
	if (name == "")
	{
		gi.Printf(PATCH_NAME " userinfo error: empty client name on G_ClientUserinfoChanged! Ignoring...\n");
	}
	else
	{
		char* namepass = Info_ValueForKey(userInfo, "cl_namepass");
		NameFilter filter;
		if (!filter.CanConnect(name))
		{
			ClientAdmin admin(internalClientNum);
			string reason = "disallowed name or disallowed word in name.";
			admin.AddKick(gent->client->ps.clientNum, true, reason.c_str());
			gi.DropClient(gent->client->ps.clientNum, ("has been kicked for " + reason).c_str());
			return;
		}
		else if(!filter.CanConnectProtected(name, namepass))//check for protected name filter
		{
			ClientAdmin admin(internalClientNum);
			string reason = "using protected name w/o permission.";
			admin.AddKick(gent->client->ps.clientNum, true, reason.c_str());
			gi.DropClient(gent->client->ps.clientNum, ("has been kicked for " + reason).c_str());
			return;
		}
		//let this be for MOHAA only, for now
		//fps check is done in Daven's pk3
#ifdef MOHAA
		else if (CheckFPSSkin(userInfo))
		{
			ClientAdmin admin(internalClientNum);
			string reason = "invalid/crash _fps skin";
			admin.AddKick(gent->client->ps.clientNum, true, reason.c_str());
			gi.DropClient(gent->client->ps.clientNum, ("has been kicked for " + reason).c_str());
			return;
		}
		else if (CheckCommentSlashesInName(name))
		{
			ClientAdmin admin(internalClientNum);
			string reason = "disallowed comment slashes in the name";
			admin.AddKick(gent->client->ps.clientNum, true, reason.c_str());
			gi.DropClient(gent->client->ps.clientNum, ("has been kicked for " + reason).c_str());
			return;
		}
#endif

	}

	globals_backup.ClientUserinfoChanged()(gent,userInfo);
}

void __cdecl G_BeginIntermission2()
{

	ScriptedEvent sev(SEV_INTERMISSION);

	if (sev.isRegistered())
	{
		sev.Trigger({ INTERM_SCREEN });
	}
	G_BeginIntermission2_original();
}

void __cdecl G_CleanUp(qboolean samemap)
{
	globals_backup.Cleanup()(samemap);
}

void initScriptHooks()
{

	AddressManager::Init((unsigned int) hmod);

	G_BeginIntermission2_original = reinterpret_cast<pG_BeginIntermission2_spec>((int)BEGININTERMISSION2_ADDR);
	SV_Commands_Init();
	Event::Init();
	ClassDef::Init();
	Listener::Init();
	DirectorClass::Init();
	Sentient::Init();
	ScriptVariable::Init();

	Entity::Init();
	DM_Team::Init();
	Player::Init();
	ScriptThread::Init();
	HTTPServer::Init();
	HTTPClient::Init();


	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourAttach(&(PVOID&)(ClassDef::BuildResponseList_Orignal), (PVOID)(&BuildResponseListHook));
	ret = DetourTransactionCommit();

	ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourAttach(&(PVOID&)(G_BeginIntermission2_original), (PVOID)(&G_BeginIntermission2));
	ret = DetourTransactionCommit();


}

void shutdownScriptHooks()
{
	SV_Commands_Shutdown();

	Entity::Shutdown();
	Player::Shutdown();
	ScriptThread::Shutdown();
	ScriptedEvent::Shutdown();
	
	HTTPServer::Shutdown();
	HTTPClient::Shutdown();

	LONG ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourDetach(&(PVOID&)(ClassDef::BuildResponseList_Orignal), (PVOID)(&BuildResponseListHook));
	ret = DetourTransactionCommit();

	ret = DetourTransactionBegin();
	ret = DetourUpdateThread(GetCurrentThread());
	ret = DetourDetach(&(PVOID&)(G_BeginIntermission2_original), (PVOID)(&G_BeginIntermission2));
	ret = DetourTransactionCommit();

	AddressManager::Shutdown();
}


void initConsoleCommands()
{
	ClientAdmin::Init();
	IPFilter::Init();
	NameFilter::Init();
	ChatFilter::Init();
	SV_Misc_Init();
}

void shutdownConsoleCommands()
{
	ClientAdmin::Shutdown();
	IPFilter::Shutdown();
	NameFilter::Shutdown();
	ChatFilter::Shutdown();
}

void startCrashReporter()
{
	gi.Printf(PATCH_NAME ": starting crash reporter \n");
	if (IsDebuggerPresent())
	{
		gi.Printf("crash reporter already running\n");
		return;
	}

	CustomCvar sv_crashrpt_poll_delay("sv_crashrpt_poll_delay", "5", CVAR_ARCHIVE);//in seconds
	CustomCvar sv_crashrpt_hang_wait("sv_crashrpt_hang_wait", "30", CVAR_ARCHIVE);//in seconds

	HANDLE hLocalProc = GetCurrentProcess();
	HANDLE hGlobalProc;

	if (!DuplicateHandle(hLocalProc,
		hLocalProc,
		hLocalProc,
		&hGlobalProc,
		0,
		TRUE,
		DUPLICATE_SAME_ACCESS))
	{
		gi.Printf("Start crash reporter error 1: %u\n", GetLastError());
		return;
	}

	STARTUPINFOW si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	auto mainPath = fs::current_path() / MAIN_PATH;
	auto crashRptPath = mainPath / "CrashReporter.exe";
	WCHAR cmdline[2048];
	DWORD pollDelay = sv_crashrpt_poll_delay.GetIntValue() * 1000, hungDelay = sv_crashrpt_hang_wait.GetIntValue() * 1000;
	wsprintfW(cmdline, L"%s %p %u %u", crashRptPath.c_str(), hGlobalProc, pollDelay, hungDelay);
	if (!CreateProcessW(NULL,   // No module name (use command line)
		cmdline,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		TRUE,           
		0,              // No creation flags
		NULL,           // Use parent's environment block
		mainPath.c_str(), 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		gi.Printf("Start crash reporter error 2: %u\n", GetLastError());
	}
	else
	{
		gi.Printf("Start crash reporter success\n", GetLastError());
	}
}

/*
============
G_InitGame

This will be called when the dll is first loaded, which
only happens when a new game is begun
============
*/
void G_InitGame( int startTime, int randomSeed )
{
	gi.Printf("==== " PATCH_NAME " Wrapper InitGame ==== \n");

	#ifndef _WIN32
	initsighandlers();  // init our custom signal handlers  (linux only)
	#endif

	initScriptHooks();

	initConsoleCommands();

	startCrashReporter();
	globals_backup.Init()( startTime, randomSeed );
	//gi.Printf("Class count: %d", classcount);
	gi.Printf(PATCH_NAME " Wrapper inited \n");
	
}

/*
============
G_Precache

Calls precache scripts
================
*/
void G_Precache()
{
	//keep reborn.scr mohaa only for now, might make it for all games later.
#ifdef MOHAA
	CustomCvar sv_rebornloader("sv_rebornloader", "reborn/reborn_loader.scr", CVAR_ARCHIVE);
	char* scriptLbl = sv_rebornloader.GetStringValue();
	if (scriptLbl != NULL && strlen(scriptLbl) > 0)
	{
		Event ev;
		ScriptVariable script;
		script.setStringValue(scriptLbl);
		ev.AddValue(script);
		try
		{
			Director->ExecuteScript(&ev);
		}
		catch (ScriptException&e)
		{
			gi.Printf(PATCH_NAME " Precache Error: Couldn't load reborn loader script, error message: %s\n", e.string.c_str());
		}
	}
#endif // MOHAA

	globals_backup.Precache()();
}

qboolean G_ConsoleCommand()
{
	if (SV_Commands_HandleCommand())
	{
		return qtrue;
	}
	else
	{
		return globals_backup.ConsoleCommand()();
	}
}

/*
SHUTDOWN game
Needed to unload fgamededmohaa.so on mapchange!
*/
void	G_Shutdown (void)
{

	gi.Printf("==== " PATCH_NAME " Wrapper Shutdown ==== \n");
	
	shutdownScriptHooks();
	shutdownConsoleCommands();
	CustomCvar sv_update("sv_update", "1", CVAR_ARCHIVE);
	
	if (sv_update.GetIntValue())
	{
		UpdateClient uc;
		uc.CheckForUpdate();
	}

	globals_backup.Shutdown()();

	#ifndef _WIN32
		// linux
		dlerror();
		if ( dlclose(hmod) )
			add_log(LOG_ERROR,"dlclose failed. reason: \"%s\"", dlerror() );
			
		resetsighandlers();  // reset to the original signal handlers
			
	#endif	
}

//input: gameImport_T* , output: gameExport_t*
void* __cdecl GetGameAPI( void *import_actual )
{
	/****** Linux: Load fgamededmohaa.so ******/
	#ifndef _WIN32

	dlerror();

	hmod = dlopen( "./fgamededmohaa.so", RTLD_LAZY|RTLD_LOCAL );
	if( !hmod ) 
	{
		printf( "dlopen failed. Reason: \"%s\"\n", dlerror() );
	}

	pGetGameAPI = ( pGetGameAPI_spec ) dlsym( hmod, "GetGameAPI" );

	if( !pGetGameAPI )	
		printf( "dlsym failed. reason: \"%s\"\n", dlerror() );

	#endif
	shared_ptr<BaseGameImport> import = GameImportFactory::GetGameImport(import_actual);

	bool nullRet = false;
	if (!hmod)
	{
		import->Printf((PATCH_NAME " Fatal error: could not load " + DGAMEX86_PATH + " properly. Exiting...\n").c_str());
		nullRet = true;
	}
	if (!systemHMOD)
	{
		import->Printf((PATCH_NAME " Fatal error: could not load " + SYSTEM86_NAME + " properly. Exiting...\n").c_str());
		nullRet = true;
	}

	if (!pGetGameAPI && hmod)
	{
		import->Printf(PATCH_NAME " Fatal error: could not find GetGameAPI. Exiting...\n");
		nullRet = true;
	}

	if (nullRet)
	{
		return NULL;
	}

	gi = *import;
//	import->Argv					= argv;
	globals							= GameExportFactory::GetGameExport(pGetGameAPI( import_actual ));
	globals_backup					= *globals;

	/*if (!systemHMOD)
	{
		gi.Error(ERR_DROP, PATCH_NAME ": Failed to load memory management routines!");
		return NULL;
	}*/
	/*Game Exports*/
/*
	globals->AllowPaused			= G_AllowPaused;	
*/
#ifdef CLIENT
#ifdef MOHBT
	globals->apiVersion = 15;
#endif // MOHBT


#endif // CLIENT
	/*
	globals->SetArchiveFloat(G_ArchiveFloat);
	globals->SetArchiveInteger(G_ArchiveInteger);
	globals->SetArchivePersistant(G_ArchivePersistant);
	globals->SetArchiveString(G_ArchiveString);
	globals->SetArchiveSvsTime(G_ArchiveSvsTime);
	globals->SetBotBegin(G_BotBegin);
	globals->SetBotThink(G_BotThink);
	*/
	globals->SetCleanup(G_CleanUp);
	globals->SetClientBegin([](gentity_t* ent, userCmd_t* cmd) {return G_ClientBegin(GEntity(ent), cmd); });


	globals->SetClientCommand([](gentity_t* ent) {return G_ClientCommand(GEntity(ent)); });
	if (gameInfo.GetExpansion() == gameInfo.AA)
	{
		globals->SetClientConnect([](int clientNum, qboolean firstTime, int a3) -> char* {return G_ClientConnect(clientNum, firstTime); }); //todo: handle for AA/SH/BT
	}
	else
	{
		globals->SetClientConnect([](int clientNum, qboolean firstTime, int a3) -> char* {return G_ClientConnect(clientNum, firstTime, a3); }); //todo: handle for AA/SH/BT
	}

	globals->SetClientDisconnect([](gentity_t* ent) {return G_ClientDisconnect(GEntity(ent)); });
	globals->SetClientThink([](gentity_t* ent, userCmd_t* cmd, userEyes_t* eyeInfo) {return G_ClientThink(GEntity(ent), cmd, eyeInfo); });

	globals->SetClientUserinfoChanged([](gentity_t* ent, char* userInfo) {return G_ClientUserinfoChanged(GEntity(ent), userInfo); });
	globals->SetConsoleCommand(G_ConsoleCommand);

	/*	
	globals->SetDebugCircle(G_DebugCircle);
	globals->SeterrorMessage(G_errorMessage);
	globals->Setgentities(G_gentities);
	globals->SetgentitySize(G_gentitySize);
	*/
	globals->SetInit(G_InitGame);
	/*
	globals->SetLevelArchiveValid(G_LevelArchiveValid);
	globals->SetmaxEntities(G_maxEntities);
	globals->SetnumEntities(G_numEntities);
	*/
	globals->SetPrecache(G_Precache);
	/*
	globals->SetPrepFrame(G_PrepFrame);
	globals->SetprofStruct(G_profStruct);
	globals->SetReadLevel(G_ReadLevel);
	globals->SetRegisterSounds(G_RegisterSounds);
	globals->SetRestart(G_Restart);
	*/
	globals->SetRunFrame(G_RunFrame);

	/*	
	globals->SetServerSpawned(G_ServerSpawned);
	globals->SetSetFrameNumber(G_SetFrameNumber);
	globals->SetSetMap(G_SetMap);
	globals->SetSetTime(G_SetTime);
	*/
	globals->SetShutdown(G_Shutdown);
	/*
	globals->SetSoundCallback(G_SoundCallback);
	globals->SetSpawnEntities(G_SpawnEntities);
	globals->SetTIKI_Orientation(G_TIKI_Orientation);
	globals->SetWriteLevel(G_WriteLevel);
	*/
	//TODO: supress DavenExtra for BT.
	//sizeof(Player);
	return globals->GetRealGameExport();
}

#ifdef _WIN32

void __cdecl upon_exit()
{
	if (hmod)
	{
		FreeLibrary(hmod);
		hmod = NULL;
	}
	if (systemHMOD)
	{
		FreeLibrary(systemHMOD);
		systemHMOD = NULL;
	}
}

BOOL WINAPI DllMain( HINSTANCE hModule, DWORD dwReason, PVOID lpReserved ) 
{
//	char path[MAX_PATH];
//	int i;
//	DWORD dwSize;
//	DWORD dwAddr;
		
	if( dwReason == DLL_PROCESS_ATTACH ) 
    { 
		//atexit(&upon_exit);
//		DisableThreadLibraryCalls( hModule );
		
		/*dwSize = GetModuleFileName( hModule, path, 2048 );

		if(!dwSize || GetLastError() == ERROR_INSUFFICIENT_BUFFER) 
		{
			path[0] = 0;
		}

		else
		{
			char* pszDir = &path[dwSize];

			while( *pszDir != '\\' ) 
			{
				pszDir--;

				if(!*pszDir) 
				{
					break;
				}
			}

			if( *pszDir == '\\' ) 
			{
				*(pszDir+1) = '\0';
			}

			else 
			{
				path[0] = 0;
			}
		}
			
		for( i=strlen(path); i>0; i-- ) 
		{
			if (path[i] == '\\') 
			{
				path[i+1] = 0;
				break;
			}
		}
		*/

		hmod = LoadLibraryA(DGAMEX86_PATH.c_str());

		if(hmod)
		{
			pGetGameAPI = (pGetGameAPI_spec)GetProcAddress(hmod, "GetGameAPI");
		}
		
		systemHMOD = GetModuleHandleA(SYSTEM86_NAME.c_str());
		if (systemHMOD)
		{
			pMemoryMalloc = (pMemoryMalloc_spec)GetProcAddress(systemHMOD, "MemoryMalloc");
			pMemoryFree = (pMemoryFree_spec)GetProcAddress(systemHMOD, "MemoryFree");
		}
		
		//initscriptfuncs();

		return TRUE; 
	}
	else if( dwReason == DLL_THREAD_DETACH ) 
    {
		return TRUE;
    }
	else if( dwReason == DLL_PROCESS_DETACH ) 
    {
		if (hmod)
		{
			FreeLibrary(hmod);
			hmod = NULL;
		}
		
		/*
		if (systemHMOD)
		{
			FreeLibrary(systemHMOD);
			systemHMOD = NULL;
		}
		*/
		return TRUE;
    }



	return TRUE;
}

#endif


void *MemoryMalloc(int size)
{
	//FIXEME: linux stuff
	return pMemoryMalloc(size);
}

void MemoryFree(void *ptr)
{
	//FIXEME: linux stuff
	pMemoryFree(ptr);
}

