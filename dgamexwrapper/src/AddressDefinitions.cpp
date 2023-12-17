#include "AddressDefinitions.h"


void AddressManager::InitAddresses()
{
	if (gameInfo.IsClient())
	{
		if (gameInfo.IsBT())
		{
			//ClassDef.cpp
			BUILDREPONSELIST_ADDRESS = AddressManager::AddAddress("BUILDREPONSELIST_ADDRESS", 0x310FDBB0);;//string, nEvent system initialized
			ADDNEWKEYENTRY_ADDR = AddressManager::AddAddress("ADDNEWKEYENTRY_ADDR", 0x310FF160);;

			//dgamex86.cpp
			BEGININTERMISSION2_ADDR = AddressManager::AddAddress("BEGININTERMISSION2_ADDR", 0x3111E910);;//string, endnode1
			CMDFUNCTIONS_ADDR = AddressManager::AddAddress("CMDFUNCTIONS_ADDR", 0x6FBED0, true); //string, Cmd_AddCommand

			//Director.cpp
			STRINGDICT_ADDR = AddressManager::AddAddress("STRINGDICT_ADDR", 0x3125B3C4);;//string, anim script: %s, anim mode
			DIRECTOR_ADDR = AddressManager::AddAddress("DIRECTOR_ADDR", 0x31259250);;

			//Entity.cpp
			DAMAGE_ADDR = AddressManager::AddAddress("DAMAGE_ADDR", 0x31112130);;

			//Event.cpp
			LASTEVENT_ADDR = AddressManager::AddAddress("LASTEVENT_ADDR", 0x31276F70);;
			TOTALEVENTS_ADDR = AddressManager::AddAddress("TOTALEVENTS_ADDR", 0x31276ED8);;
			EVENTDEFLIST_ADDR = AddressManager::AddAddress("EVENTDEFLIST_ADDR", 0x31276C80);;
			ADDLISTENER_ADDR = AddressManager::AddAddress("ADDLISTENER_ADDR", 0x3113CCE0);;
			GETVALUE_ADDR = AddressManager::AddAddress("GETVALUE_ADDR", 0x3113CB20);;

			//Listener.cpp
			EXECUTESCRIPT_ADDR = AddressManager::AddAddress("EXECUTESCRIPT_ADDR", 0x3113EE80);;
			EXECUTERETURNSCRIPT_ADDR = AddressManager::AddAddress("EXECUTERETURNSCRIPT_ADDR", 0x3113EF20);;

			//Player.cpp
			RESPAWN_ADDR = AddressManager::AddAddress("RESPAWN_ADDR", 0x311530C0);;
			KILLED_ADDR = AddressManager::AddAddress("KILLED_ADDR", 0x31153D60);;

			//ScriptVariable.cpp
			CLEARINTERNAL_ADDR = AddressManager::AddAddress("CLEARINTERNAL_ADDR", 0x31058D60);;
			LISTENERVALUE_ADDR = AddressManager::AddAddress("LISTENERVALUE_ADDR", 0x3105A230);;
			SETARRAYATREF_ADDR = AddressManager::AddAddress("SETARRAYATREF_ADDR", 0x3105D280);;
			STRINGVALUE_ADDR = AddressManager::AddAddress("STRINGVALUE_ADDR", 0x31059160);;
			BOOLEANVALUE_ADDR = AddressManager::AddAddress("BOOLEANVALUE_ADDR", 0x31059D00);;
			SETLISENERVALUEVALUE_ADDR = AddressManager::AddAddress("SETLISENERVALUEVALUE_ADDR", 0x31059E60);;
			OPERATOREQU_ADDR = AddressManager::AddAddress("OPERATOREQU_ADDR", 0x3105A350);;
			OPERATOREQUEQU_ADDR = AddressManager::AddAddress("OPERATOREQUEQU_ADDR", 0x3105A570);;
			SETCONSTARRAYVALUE_ADDR = AddressManager::AddAddress("SETCONSTARRAYVALUE_ADDR", 0x3105C9A0);;

			//Sentient.cpp
			GETACTIVEWEAPON_ADDR = AddressManager::AddAddress("GETACTIVEWEAPON_ADDR", 0x31189780);;

			//sv_misc.cpp
			NET_OUTOFBANDPRINT_ADDR = AddressManager::AddAddress("NET_OUTOFBANDPRINT_ADDR", 0x4735C0, true);
			SVS_CLIENTS_ADDR = AddressManager::AddAddress("SVS_CLIENTS_ADDR", 0xE9A080, true);
			SVS_NUMCLIENTS_ADDR = AddressManager::AddAddress("SVS_NUMCLIENTS_ADDR", 0xE9A084, true);
		}
	}
	else //SERVER
	{
		if (gameInfo.IsBT())
		{
			//ClassDef.cpp
			BUILDREPONSELIST_ADDRESS = AddressManager::AddAddress("BUILDREPONSELIST_ADDRESS", 0x310FDBB0);//string, nEvent system initialized
			ADDNEWKEYENTRY_ADDR = AddressManager::AddAddress("ADDNEWKEYENTRY_ADDR", 0x310FF160);

			//dgamex86.cpp
			BEGININTERMISSION2_ADDR = AddressManager::AddAddress("BEGININTERMISSION2_ADDR", 0x3111E810);//string, info_player_intermission
			CMDFUNCTIONS_ADDR = AddressManager::AddAddress("CMDFUNCTIONS_ADDR", 0x5E1C38, true); //string, Cmd_AddCommand

			//Director.cpp
			STRINGDICT_ADDR = AddressManager::AddAddress("STRINGDICT_ADDR", 0x3125B3C4);//string, anim script: %s, anim mode
			DIRECTOR_ADDR = AddressManager::AddAddress("DIRECTOR_ADDR", 0x31259250);

			//Entity.cpp
			DAMAGE_ADDR = AddressManager::AddAddress("DAMAGE_ADDR", 0x31112130);

			//Event.cpp
			LASTEVENT_ADDR = AddressManager::AddAddress("LASTEVENT_ADDR", 0x31276F70);
			TOTALEVENTS_ADDR = AddressManager::AddAddress("TOTALEVENTS_ADDR", 0x31276ED8);
			EVENTDEFLIST_ADDR = AddressManager::AddAddress("EVENTDEFLIST_ADDR", 0x31276C80);
			ADDLISTENER_ADDR = AddressManager::AddAddress("ADDLISTENER_ADDR", 0x3113CCE0);
			GETVALUE_ADDR = AddressManager::AddAddress("GETVALUE_ADDR", 0x3113CB20);

			//Listener.cpp
			EXECUTESCRIPT_ADDR = AddressManager::AddAddress("EXECUTESCRIPT_ADDR", 0x3113EE80);
			EXECUTERETURNSCRIPT_ADDR = AddressManager::AddAddress("EXECUTERETURNSCRIPT_ADDR", 0x3113EF20);

			//Player.cpp
			RESPAWN_ADDR = AddressManager::AddAddress("RESPAWN_ADDR", 0x311530C0);
			KILLED_ADDR = AddressManager::AddAddress("KILLED_ADDR", 0x31153D60);

			//ScriptVariable.cpp
			CLEARINTERNAL_ADDR = AddressManager::AddAddress("CLEARINTERNAL_ADDR", 0x31058D60);
			LISTENERVALUE_ADDR = AddressManager::AddAddress("LISTENERVALUE_ADDR", 0x3105A230);
			SETARRAYATREF_ADDR = AddressManager::AddAddress("SETARRAYATREF_ADDR", 0x3105D280);
			STRINGVALUE_ADDR = AddressManager::AddAddress("STRINGVALUE_ADDR", 0x31059160);
			BOOLEANVALUE_ADDR = AddressManager::AddAddress("BOOLEANVALUE_ADDR", 0x31059D00);
			SETLISENERVALUEVALUE_ADDR = AddressManager::AddAddress("SETLISENERVALUEVALUE_ADDR", 0x31059E60);
			OPERATOREQU_ADDR = AddressManager::AddAddress("OPERATOREQU_ADDR", 0x3105A350);
			OPERATOREQUEQU_ADDR = AddressManager::AddAddress("OPERATOREQUEQU_ADDR", 0x3105A570);
			SETCONSTARRAYVALUE_ADDR = AddressManager::AddAddress("SETCONSTARRAYVALUE_ADDR", 0x3105C9A0);

			//Sentient.cpp
			GETACTIVEWEAPON_ADDR = AddressManager::AddAddress("GETACTIVEWEAPON_ADDR", 0x31189780);

			//sv_misc.cpp
			NET_OUTOFBANDPRINT_ADDR = AddressManager::AddAddress("NET_OUTOFBANDPRINT_ADDR", 0x4288A0, true);
			SVS_CLIENTS_ADDR = AddressManager::AddAddress("SVS_CLIENTS_ADDR", 0x9419C0, true);
			SVS_NUMCLIENTS_ADDR = AddressManager::AddAddress("SVS_NUMCLIENTS_ADDR", 0x9419C4, true);
		}
		//separate section for sh, it's worth noting that SH and BT are the same thing.
		else if (gameInfo.IsSH())
		{
			//ClassDef.cpp
			BUILDREPONSELIST_ADDRESS = AddressManager::AddAddress("BUILDREPONSELIST_ADDRESS", 0x310FDBB0);//string, nEvent system initialized
			ADDNEWKEYENTRY_ADDR = AddressManager::AddAddress("ADDNEWKEYENTRY_ADDR", 0x310FF160);

			//dgamex86.cpp
			BEGININTERMISSION2_ADDR = AddressManager::AddAddress("BEGININTERMISSION2_ADDR", 0x3111E810);//string, info_player_intermission
			CMDFUNCTIONS_ADDR = AddressManager::AddAddress("CMDFUNCTIONS_ADDR", 0x5E1C38, true); //string, Cmd_AddCommand

			//Director.cpp
			STRINGDICT_ADDR = AddressManager::AddAddress("STRINGDICT_ADDR", 0x3125B3C4);//string, anim script: %s, anim mode
			DIRECTOR_ADDR = AddressManager::AddAddress("DIRECTOR_ADDR", 0x31259250);

			//Entity.cpp
			DAMAGE_ADDR = AddressManager::AddAddress("DAMAGE_ADDR", 0x31112130);

			//Event.cpp
			LASTEVENT_ADDR = AddressManager::AddAddress("LASTEVENT_ADDR", 0x31276F70);
			TOTALEVENTS_ADDR = AddressManager::AddAddress("TOTALEVENTS_ADDR", 0x31276ED8);
			EVENTDEFLIST_ADDR = AddressManager::AddAddress("EVENTDEFLIST_ADDR", 0x31276C80);
			ADDLISTENER_ADDR = AddressManager::AddAddress("ADDLISTENER_ADDR", 0x3113CCE0);
			GETVALUE_ADDR = AddressManager::AddAddress("GETVALUE_ADDR", 0x3113CB20);

			//Listener.cpp
			EXECUTESCRIPT_ADDR = AddressManager::AddAddress("EXECUTESCRIPT_ADDR", 0x3113EE80);
			EXECUTERETURNSCRIPT_ADDR = AddressManager::AddAddress("EXECUTERETURNSCRIPT_ADDR", 0x3113EF20);

			//Player.cpp
			RESPAWN_ADDR = AddressManager::AddAddress("RESPAWN_ADDR", 0x311530C0);
			KILLED_ADDR = AddressManager::AddAddress("KILLED_ADDR", 0x31153D60);

			//ScriptVariable.cpp
			CLEARINTERNAL_ADDR = AddressManager::AddAddress("CLEARINTERNAL_ADDR", 0x31058D60);
			LISTENERVALUE_ADDR = AddressManager::AddAddress("LISTENERVALUE_ADDR", 0x3105A230);
			SETARRAYATREF_ADDR = AddressManager::AddAddress("SETARRAYATREF_ADDR", 0x3105D280);
			STRINGVALUE_ADDR = AddressManager::AddAddress("STRINGVALUE_ADDR", 0x31059160);
			BOOLEANVALUE_ADDR = AddressManager::AddAddress("BOOLEANVALUE_ADDR", 0x31059D00);
			SETLISENERVALUEVALUE_ADDR = AddressManager::AddAddress("SETLISENERVALUEVALUE_ADDR", 0x31059E60);
			OPERATOREQU_ADDR = AddressManager::AddAddress("OPERATOREQU_ADDR", 0x3105A350);
			OPERATOREQUEQU_ADDR = AddressManager::AddAddress("OPERATOREQUEQU_ADDR", 0x3105A570);
			SETCONSTARRAYVALUE_ADDR = AddressManager::AddAddress("SETCONSTARRAYVALUE_ADDR", 0x3105C9A0);

			//Sentient.cpp
			GETACTIVEWEAPON_ADDR = AddressManager::AddAddress("GETACTIVEWEAPON_ADDR", 0x31189780);

			//sv_misc.cpp
			NET_OUTOFBANDPRINT_ADDR = AddressManager::AddAddress("NET_OUTOFBANDPRINT_ADDR", 0x4288A0, true);
			SVS_CLIENTS_ADDR = AddressManager::AddAddress("SVS_CLIENTS_ADDR", 0x9419C0, true);
			SVS_NUMCLIENTS_ADDR = AddressManager::AddAddress("SVS_NUMCLIENTS_ADDR", 0x9419C4, true);
		}
		else if (gameInfo.IsAA())
		{
			//ClassDef.cpp
			BUILDREPONSELIST_ADDRESS = AddressManager::AddAddress("BUILDREPONSELIST_ADDRESS", 0x310B0500);//string, nEvent system initialized
			ADDNEWKEYENTRY_ADDR = AddressManager::AddAddress("ADDNEWKEYENTRY_ADDR", 0x310B1AB0);

			//dgamex86.cpp
			BEGININTERMISSION2_ADDR = AddressManager::AddAddress("BEGININTERMISSION2_ADDR", 0x310D85B0);//string, info_player_intermission
			CMDFUNCTIONS_ADDR = AddressManager::AddAddress("CMDFUNCTIONS_ADDR", 0x5D4438, true); //string, Cmd_AddCommand

			//Director.cpp
			STRINGDICT_ADDR = AddressManager::AddAddress("STRINGDICT_ADDR", 0x31210E64);//string, anim script: %s, anim mode
			DIRECTOR_ADDR = AddressManager::AddAddress("DIRECTOR_ADDR", 0x3120ECF0);

			//Entity.cpp
			DAMAGE_ADDR = AddressManager::AddAddress("DAMAGE_ADDR", 0x310CAE10);

			//Event.cpp
			LASTEVENT_ADDR = AddressManager::AddAddress("LASTEVENT_ADDR", 0x31229808);
			TOTALEVENTS_ADDR = AddressManager::AddAddress("TOTALEVENTS_ADDR", 0x31229770);
			EVENTDEFLIST_ADDR = AddressManager::AddAddress("EVENTDEFLIST_ADDR", 0x31229518);
			ADDLISTENER_ADDR = AddressManager::AddAddress("ADDLISTENER_ADDR", 0x310F37A0);
			GETVALUE_ADDR = AddressManager::AddAddress("GETVALUE_ADDR", 0x310F35E0);

			//Listener.cpp
			EXECUTESCRIPT_ADDR = AddressManager::AddAddress("EXECUTESCRIPT_ADDR", 0x310F5920);
			EXECUTERETURNSCRIPT_ADDR = AddressManager::AddAddress("EXECUTERETURNSCRIPT_ADDR", 0x310F59C0);

			//Player.cpp
			RESPAWN_ADDR = AddressManager::AddAddress("RESPAWN_ADDR", 0x311152B0);
			KILLED_ADDR = AddressManager::AddAddress("KILLED_ADDR", 0x311163C0);

			//ScriptVariable.cpp
			CLEARINTERNAL_ADDR = AddressManager::AddAddress("CLEARINTERNAL_ADDR", 0x31053330);
			LISTENERVALUE_ADDR = AddressManager::AddAddress("LISTENERVALUE_ADDR", 0x310547E0);
			SETARRAYATREF_ADDR = AddressManager::AddAddress("SETARRAYATREF_ADDR", 0x31057830);
			STRINGVALUE_ADDR = AddressManager::AddAddress("STRINGVALUE_ADDR", 0x31053710);
			BOOLEANVALUE_ADDR = AddressManager::AddAddress("BOOLEANVALUE_ADDR", 0x310542B0);
			SETLISENERVALUEVALUE_ADDR = AddressManager::AddAddress("SETLISENERVALUEVALUE_ADDR", 0x31054410);
			OPERATOREQU_ADDR = AddressManager::AddAddress("OPERATOREQU_ADDR", 0x31054900);
			OPERATOREQUEQU_ADDR = AddressManager::AddAddress("OPERATOREQUEQU_ADDR", 0x31054B20);
			SETCONSTARRAYVALUE_ADDR = AddressManager::AddAddress("SETCONSTARRAYVALUE_ADDR", 0x31056F50);

			//Sentient.cpp
			GETACTIVEWEAPON_ADDR = AddressManager::AddAddress("GETACTIVEWEAPON_ADDR", 0x31149AC0);

			//sv_misc.cpp
			NET_OUTOFBANDPRINT_ADDR = AddressManager::AddAddress("NET_OUTOFBANDPRINT_ADDR", 0x424730, true);
			SVS_CLIENTS_ADDR = AddressManager::AddAddress("SVS_CLIENTS_ADDR", 0x79D5E0, true);
			SVS_NUMCLIENTS_ADDR = AddressManager::AddAddress("SVS_NUMCLIENTS_ADDR", 0x79D5E4, true);

			//DM_Team.cpp
			DMTEAM_ADDKILLS_ADDR = AddressManager::AddAddress("DMTEAM_ADDKILLS_ADDR", 0x310B87E0);//string, you killed yourself
			DMTEAM_ADDDEATHS_ADDR = AddressManager::AddAddress("DMTEAM_ADDDEATHS_ADDR", 0x310B8850);// in player's KILLED_ADDR
		}
	}
}
