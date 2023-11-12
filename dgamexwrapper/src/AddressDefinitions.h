#pragma once
#include "AddressManager.h"

#ifdef CLIENT

#ifdef MOHBT

//ClassDef.cpp
AddressEntry& BUILDREPONSELIST_ADDRESS = AddressManager::AddAddress(0x310FDBB0);//string, nEvent system initialized
AddressEntry& ADDNEWKEYENTRY_ADDR = AddressManager::AddAddress(0x310FF160);

//dgamex86.cpp
AddressEntry& BEGININTERMISSION_ADDR = AddressManager::AddAddress(0x3111E910);//string, endnode1
AddressEntry& CMDFUNCTIONS_ADDR = AddressManager::AddAddress(0x6FBED0, true); //string, Cmd_AddCommand

//Director.cpp
AddressEntry& STRINGDICT_ADDR = AddressManager::AddAddress(0x3125B3C4);//string, anim script: %s, anim mode
AddressEntry& DIRECTOR_ADDR = AddressManager::AddAddress(0x31259250);

//Entity.cpp
AddressEntry& DAMAGE_ADDR = AddressManager::AddAddress(0x31112130);

//Event.cpp
AddressEntry& LASTEVENT_ADDR = AddressManager::AddAddress(0x31276F70);
AddressEntry& TOTALEVENTS_ADDR = AddressManager::AddAddress(0x31276ED8);
AddressEntry& EVENTDEFLIST_ADDR = AddressManager::AddAddress(0x31276C80);
AddressEntry& ADDLISTENER_ADDR = AddressManager::AddAddress(0x3113CCE0);
AddressEntry& GETVALUE_ADDR = AddressManager::AddAddress(0x3113CB20);

//Listener.cpp
AddressEntry& EXECUTESCRIPT_ADDR = AddressManager::AddAddress(0x3113EE80);
AddressEntry& EXECUTERETURNSCRIPT_ADDR = AddressManager::AddAddress(0x3113EF20);

//Player.cpp
AddressEntry& RESPAWN_ADDR = AddressManager::AddAddress(0x311530C0);
AddressEntry& KILLED_ADDR = AddressManager::AddAddress(0x31153D60);

//ScriptVariable.cpp
AddressEntry& CLEARINTERNAL_ADDR = AddressManager::AddAddress(0x31058D60);
AddressEntry& LISTENERVALUE_ADDR = AddressManager::AddAddress(0x3105A230);
AddressEntry& SETARRAYATREF_ADDR = AddressManager::AddAddress(0x3105D280);
AddressEntry& STRINGVALUE_ADDR = AddressManager::AddAddress(0x31059160);
AddressEntry& BOOLEANVALUE_ADDR = AddressManager::AddAddress(0x31059D00);
AddressEntry& SETLISENERVALUEVALUE_ADDR = AddressManager::AddAddress(0x31059E60);
AddressEntry& OPERATOREQU_ADDR = AddressManager::AddAddress(0x3105A350);
AddressEntry& OPERATOREQUEQU_ADDR = AddressManager::AddAddress(0x3105A570);
AddressEntry& SETCONSTARRAYVALUE_ADDR = AddressManager::AddAddress(0x3105C9A0);

//Sentient.cpp
AddressEntry& GETACTIVEWEAPON_ADDR = AddressManager::AddAddress(0x31189780);

//sv_misc.cpp
AddressEntry& NET_OUTOFBANDPRINT_ADDR = AddressManager::AddAddress(0x4735C0, true);
AddressEntry& SVS_CLIENTS_ADDR = AddressManager::AddAddress(0xE9A080, true);
AddressEntry& SVS_NUMCLIENTS_ADDR = AddressManager::AddAddress(0xE9A084, true);
#endif // MOHBT

#endif // CLIENT

#ifdef SERVER

#ifdef MOHBT

//ClassDef.cpp
AddressEntry& BUILDREPONSELIST_ADDRESS = AddressManager::AddAddress(0x310FDBB0);//string, nEvent system initialized
AddressEntry& ADDNEWKEYENTRY_ADDR = AddressManager::AddAddress(0x310FF160);

//dgamex86.cpp
AddressEntry& BEGININTERMISSION2_ADDR = AddressManager::AddAddress(0x3111E810);//string, endnode1
AddressEntry& CMDFUNCTIONS_ADDR = AddressManager::AddAddress(0x5E1C38, true); //string, Cmd_AddCommand

//Director.cpp
AddressEntry& STRINGDICT_ADDR = AddressManager::AddAddress(0x3125B3C4);//string, anim script: %s, anim mode
AddressEntry& DIRECTOR_ADDR = AddressManager::AddAddress(0x31259250);

//Entity.cpp
AddressEntry& DAMAGE_ADDR = AddressManager::AddAddress(0x31112130);

//Event.cpp
AddressEntry& LASTEVENT_ADDR = AddressManager::AddAddress(0x31276F70);
AddressEntry& TOTALEVENTS_ADDR = AddressManager::AddAddress(0x31276ED8);
AddressEntry& EVENTDEFLIST_ADDR = AddressManager::AddAddress(0x31276C80);
AddressEntry& ADDLISTENER_ADDR = AddressManager::AddAddress(0x3113CCE0);
AddressEntry& GETVALUE_ADDR = AddressManager::AddAddress(0x3113CB20);

//Listener.cpp
AddressEntry& EXECUTESCRIPT_ADDR = AddressManager::AddAddress(0x3113EE80);
AddressEntry& EXECUTERETURNSCRIPT_ADDR = AddressManager::AddAddress(0x3113EF20);

//Player.cpp
AddressEntry& RESPAWN_ADDR = AddressManager::AddAddress(0x311530C0);
AddressEntry& KILLED_ADDR = AddressManager::AddAddress(0x31153D60);

//ScriptVariable.cpp
AddressEntry& CLEARINTERNAL_ADDR = AddressManager::AddAddress(0x31058D60);
AddressEntry& LISTENERVALUE_ADDR = AddressManager::AddAddress(0x3105A230);
AddressEntry& SETARRAYATREF_ADDR = AddressManager::AddAddress(0x3105D280);
AddressEntry& STRINGVALUE_ADDR = AddressManager::AddAddress(0x31059160);
AddressEntry& BOOLEANVALUE_ADDR = AddressManager::AddAddress(0x31059D00);
AddressEntry& SETLISENERVALUEVALUE_ADDR = AddressManager::AddAddress(0x31059E60);
AddressEntry& OPERATOREQU_ADDR = AddressManager::AddAddress(0x3105A350);
AddressEntry& OPERATOREQUEQU_ADDR = AddressManager::AddAddress(0x3105A570);
AddressEntry& SETCONSTARRAYVALUE_ADDR = AddressManager::AddAddress(0x3105C9A0);

//Sentient.cpp
AddressEntry& GETACTIVEWEAPON_ADDR = AddressManager::AddAddress(0x31189780);

//sv_misc.cpp
AddressEntry& NET_OUTOFBANDPRINT_ADDR = AddressManager::AddAddress(0x4288A0, true);
AddressEntry& SVS_CLIENTS_ADDR = AddressManager::AddAddress(0x9419C0, true);
AddressEntry& SVS_NUMCLIENTS_ADDR = AddressManager::AddAddress(0x9419C4, true);
#endif // MOHBT

//separate section for sh, it's worth noting that SH and BT are the same thing.
#ifdef MOHSH

//ClassDef.cpp
AddressEntry& BUILDREPONSELIST_ADDRESS = AddressManager::AddAddress(0x310FDBB0);//string, nEvent system initialized
AddressEntry& ADDNEWKEYENTRY_ADDR = AddressManager::AddAddress(0x310FF160);

//dgamex86.cpp
AddressEntry& BEGININTERMISSION2_ADDR = AddressManager::AddAddress(0x3111E810);//string, endnode1
AddressEntry& CMDFUNCTIONS_ADDR = AddressManager::AddAddress(0x5E1C38, true); //string, Cmd_AddCommand

//Director.cpp
AddressEntry& STRINGDICT_ADDR = AddressManager::AddAddress(0x3125B3C4);//string, anim script: %s, anim mode
AddressEntry& DIRECTOR_ADDR = AddressManager::AddAddress(0x31259250);

//Entity.cpp
AddressEntry& DAMAGE_ADDR = AddressManager::AddAddress(0x31112130);

//Event.cpp
AddressEntry& LASTEVENT_ADDR = AddressManager::AddAddress(0x31276F70);
AddressEntry& TOTALEVENTS_ADDR = AddressManager::AddAddress(0x31276ED8);
AddressEntry& EVENTDEFLIST_ADDR = AddressManager::AddAddress(0x31276C80);
AddressEntry& ADDLISTENER_ADDR = AddressManager::AddAddress(0x3113CCE0);
AddressEntry& GETVALUE_ADDR = AddressManager::AddAddress(0x3113CB20);

//Listener.cpp
AddressEntry& EXECUTESCRIPT_ADDR = AddressManager::AddAddress(0x3113EE80);
AddressEntry& EXECUTERETURNSCRIPT_ADDR = AddressManager::AddAddress(0x3113EF20);

//Player.cpp
AddressEntry& RESPAWN_ADDR = AddressManager::AddAddress(0x311530C0);
AddressEntry& KILLED_ADDR = AddressManager::AddAddress(0x31153D60);

//ScriptVariable.cpp
AddressEntry& CLEARINTERNAL_ADDR = AddressManager::AddAddress(0x31058D60);
AddressEntry& LISTENERVALUE_ADDR = AddressManager::AddAddress(0x3105A230);
AddressEntry& SETARRAYATREF_ADDR = AddressManager::AddAddress(0x3105D280);
AddressEntry& STRINGVALUE_ADDR = AddressManager::AddAddress(0x31059160);
AddressEntry& BOOLEANVALUE_ADDR = AddressManager::AddAddress(0x31059D00);
AddressEntry& SETLISENERVALUEVALUE_ADDR = AddressManager::AddAddress(0x31059E60);
AddressEntry& OPERATOREQU_ADDR = AddressManager::AddAddress(0x3105A350);
AddressEntry& OPERATOREQUEQU_ADDR = AddressManager::AddAddress(0x3105A570);
AddressEntry& SETCONSTARRAYVALUE_ADDR = AddressManager::AddAddress(0x3105C9A0);

//Sentient.cpp
AddressEntry& GETACTIVEWEAPON_ADDR = AddressManager::AddAddress(0x31189780);

//sv_misc.cpp
AddressEntry& NET_OUTOFBANDPRINT_ADDR = AddressManager::AddAddress(0x4288A0, true);
AddressEntry& SVS_CLIENTS_ADDR = AddressManager::AddAddress(0x9419C0, true);
AddressEntry& SVS_NUMCLIENTS_ADDR = AddressManager::AddAddress(0x9419C4, true);
#endif // MOHSH

#ifdef MOHAA

//ClassDef.cpp
AddressEntry& BUILDREPONSELIST_ADDRESS = AddressManager::AddAddress(0x310B0500);//string, nEvent system initialized
AddressEntry& ADDNEWKEYENTRY_ADDR = AddressManager::AddAddress(0x310B1AB0);

//dgamex86.cpp
AddressEntry& BEGININTERMISSION2_ADDR = AddressManager::AddAddress(0x310D86B0);//string, endnode1
AddressEntry& CMDFUNCTIONS_ADDR = AddressManager::AddAddress(0x5D4438, true); //string, Cmd_AddCommand

//Director.cpp
AddressEntry& STRINGDICT_ADDR = AddressManager::AddAddress(0x31210E64);//string, anim script: %s, anim mode
AddressEntry& DIRECTOR_ADDR = AddressManager::AddAddress(0x3120ECF0);

//Entity.cpp
AddressEntry& DAMAGE_ADDR = AddressManager::AddAddress(0x310CAE10);

//Event.cpp
AddressEntry& LASTEVENT_ADDR = AddressManager::AddAddress(0x31229808);
AddressEntry& TOTALEVENTS_ADDR = AddressManager::AddAddress(0x31229770);
AddressEntry& EVENTDEFLIST_ADDR = AddressManager::AddAddress(0x31229518);
AddressEntry& ADDLISTENER_ADDR = AddressManager::AddAddress(0x310F37A0);
AddressEntry& GETVALUE_ADDR = AddressManager::AddAddress(0x310F35E0);

//Listener.cpp
AddressEntry& EXECUTESCRIPT_ADDR = AddressManager::AddAddress(0x310F5920);
AddressEntry& EXECUTERETURNSCRIPT_ADDR = AddressManager::AddAddress(0x3104CAA0);

//Player.cpp
AddressEntry& RESPAWN_ADDR = AddressManager::AddAddress(0x311152B0);
AddressEntry& KILLED_ADDR = AddressManager::AddAddress(0x311163C0);

//ScriptVariable.cpp
AddressEntry& CLEARINTERNAL_ADDR = AddressManager::AddAddress(0x31053330);
AddressEntry& LISTENERVALUE_ADDR = AddressManager::AddAddress(0x310547E0);
AddressEntry& SETARRAYATREF_ADDR = AddressManager::AddAddress(0x31057830);
AddressEntry& STRINGVALUE_ADDR = AddressManager::AddAddress(0x31053710);
AddressEntry& BOOLEANVALUE_ADDR = AddressManager::AddAddress(0x310542B0);
AddressEntry& SETLISENERVALUEVALUE_ADDR = AddressManager::AddAddress(0x31054410);
AddressEntry& OPERATOREQU_ADDR = AddressManager::AddAddress(0x31054900);
AddressEntry& OPERATOREQUEQU_ADDR = AddressManager::AddAddress(0x31054B20);
AddressEntry& SETCONSTARRAYVALUE_ADDR = AddressManager::AddAddress(0x31056F50);

//Sentient.cpp
AddressEntry& GETACTIVEWEAPON_ADDR = AddressManager::AddAddress(0x31149AC0);

//sv_misc.cpp
AddressEntry& NET_OUTOFBANDPRINT_ADDR = AddressManager::AddAddress(0x424730, true);
AddressEntry& SVS_CLIENTS_ADDR = AddressManager::AddAddress(0x79D5E0, true);
AddressEntry& SVS_NUMCLIENTS_ADDR = AddressManager::AddAddress(0x79D5E4, true);

//DM_Team.cpp
AddressEntry& DMTEAM_ADDKILLS_ADDR = AddressManager::AddAddress(0x310B87E0);//string, you killed yourself
AddressEntry& DMTEAM_ADDDEATHS_ADDR = AddressManager::AddAddress(0x310B8850);// in player's KILLED_ADDR
#endif // MOHAA


#endif // SERVER
