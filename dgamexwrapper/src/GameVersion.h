#pragma once
#include "AddressManager.h"
#include "OffsetDefinitions.h"

#ifdef CLIENT

#ifdef MOHBT
#define MAIN_PATH		"maintt"
#define DGAMEX86_PATH	MAIN_PATH"\\gamex86mohbt.dll"
#define SYSTEM86_NAME	"system86tt.dll"

#endif // MOHBT

#endif // CLIENT

#ifdef SERVER

#ifdef MOHBT
#define MAIN_PATH		"maintt"
#define DGAMEX86_PATH	MAIN_PATH"\\dgamex86mohbt.dll"
#define SYSTEM86_NAME	"system86tt.dll"

#endif // MOHBT

//separate section for sh, it's worth noting that SH and BT are the same thing.
#ifdef MOHSH

#define MAIN_PATH		"mainta"
#define DGAMEX86_PATH	MAIN_PATH"\\dgamex86mohsh.dll"
#define SYSTEM86_NAME	"system86ta.dll"

#endif // MOHSH

#ifdef MOHAA

#define MAIN_PATH		"main"
#define DGAMEX86_PATH	MAIN_PATH"\\gamex86mohaa.dll"
#define SYSTEM86_NAME	"system86.dll"

#endif // MOHAA


#endif // SERVER



//ClassDef.cpp
extern AddressEntry& BUILDREPONSELIST_ADDRESS;//string, nEvent system initialized
extern AddressEntry& ADDNEWKEYENTRY_ADDR;

//dgamex86.cpp
extern AddressEntry& BEGININTERMISSION2_ADDR;//string, endnode1
extern AddressEntry& CMDFUNCTIONS_ADDR; //string, Cmd_AddCommand

//Director.cpp
extern AddressEntry& STRINGDICT_ADDR;//string, anim script: %s, anim mode
extern AddressEntry& DIRECTOR_ADDR;

//Entity.cpp
extern AddressEntry& DAMAGE_ADDR;

//Event.cpp
extern AddressEntry& LASTEVENT_ADDR;
extern AddressEntry& TOTALEVENTS_ADDR;
extern AddressEntry& EVENTDEFLIST_ADDR;
extern AddressEntry& ADDLISTENER_ADDR;
extern AddressEntry& GETVALUE_ADDR;

//Listener.cpp
extern AddressEntry& EXECUTESCRIPT_ADDR;
extern AddressEntry& EXECUTERETURNSCRIPT_ADDR;

//Player.cpp
extern AddressEntry& RESPAWN_ADDR;
extern AddressEntry& KILLED_ADDR;

//ScriptVariable.cpp
extern AddressEntry& CLEARINTERNAL_ADDR;
extern AddressEntry& LISTENERVALUE_ADDR;
extern AddressEntry& SETARRAYATREF_ADDR;
extern AddressEntry& STRINGVALUE_ADDR;
extern AddressEntry& BOOLEANVALUE_ADDR;
extern AddressEntry& SETLISENERVALUEVALUE_ADDR;
extern AddressEntry& OPERATOREQU_ADDR;
extern AddressEntry& OPERATOREQUEQU_ADDR;
extern AddressEntry& SETCONSTARRAYVALUE_ADDR;

//Sentient.cpp
extern AddressEntry& GETACTIVEWEAPON_ADDR;

//sv_misc.cpp
extern AddressEntry& NET_OUTOFBANDPRINT_ADDR;
extern AddressEntry& SVS_CLIENTS_ADDR;
extern AddressEntry& SVS_NUMCLIENTS_ADDR;

#ifdef MOHAA

//DM_Team.cpp
extern AddressEntry& DMTEAM_ADDKILLS_ADDR;
extern AddressEntry& DMTEAM_ADDDEATHS_ADDR;

#endif // MOHAA
