#pragma once
#include "AddressManager.h"
#include "GameVersion.h"
//ClassDef.cpp
inline AddressEntry BUILDREPONSELIST_ADDRESS;
inline AddressEntry ADDNEWKEYENTRY_ADDR;

//dgamex86.cpp
inline AddressEntry BEGININTERMISSION2_ADDR;
inline AddressEntry CMDFUNCTIONS_ADDR;

//Director.cpp
inline AddressEntry STRINGDICT_ADDR;
inline AddressEntry DIRECTOR_ADDR;

//Entity.cpp
inline AddressEntry DAMAGE_ADDR;

//Event.cpp
inline AddressEntry LASTEVENT_ADDR;
inline AddressEntry TOTALEVENTS_ADDR;
inline AddressEntry EVENTDEFLIST_ADDR;
inline AddressEntry ADDLISTENER_ADDR;
inline AddressEntry GETVALUE_ADDR;

//Listener.cpp
inline AddressEntry EXECUTESCRIPT_ADDR;
inline AddressEntry EXECUTERETURNSCRIPT_ADDR;

//Player.cpp
inline AddressEntry RESPAWN_ADDR;
inline AddressEntry KILLED_ADDR;

//ScriptVariable.cpp
inline AddressEntry CLEARINTERNAL_ADDR;
inline AddressEntry LISTENERVALUE_ADDR;
inline AddressEntry SETARRAYATREF_ADDR;
inline AddressEntry STRINGVALUE_ADDR;
inline AddressEntry BOOLEANVALUE_ADDR;
inline AddressEntry SETLISENERVALUEVALUE_ADDR;
inline AddressEntry OPERATOREQU_ADDR;
inline AddressEntry OPERATOREQUEQU_ADDR;
inline AddressEntry SETCONSTARRAYVALUE_ADDR;

//Sentient.cpp
inline AddressEntry GETACTIVEWEAPON_ADDR;

//sv_misc.cpp
inline AddressEntry NET_OUTOFBANDPRINT_ADDR;
inline AddressEntry SVS_CLIENTS_ADDR;
inline AddressEntry SVS_NUMCLIENTS_ADDR;

//MOHAA only:
//DM_Team.cpp
inline AddressEntry DMTEAM_ADDKILLS_ADDR;
inline AddressEntry DMTEAM_ADDDEATHS_ADDR;
