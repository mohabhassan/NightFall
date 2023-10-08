#pragma once
#include <list>

constexpr unsigned int defaultBaseAddr = 0x31000000;
class AddressEntry
{
	unsigned int address;
	unsigned int base;
	bool isMOHAA;
public:
	AddressEntry(int addr, int bAddr, bool isMOH)
	{
		address = addr;
		base = bAddr;
		isMOHAA = isMOH;
	}

	bool IsMOHAAAddress() const
	{
		return isMOHAA;
	}

	operator int() const
	{
		return address;
	}

	void SetBase(unsigned int bAddr)
	{
		if (base != bAddr)
		{
			address = address - base + bAddr;
			base = bAddr;
		}
	}
};

class AddressManager
{
	static std::list<AddressEntry>* addresses;
	static unsigned int dllBaseAddress;
public:
	static void Init(unsigned int dllBaseAddr);
	static void Shutdown();
	
	static AddressEntry& AddAddress(unsigned int address, bool isMOH = false);
	
};


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
