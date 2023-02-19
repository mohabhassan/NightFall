#include "AddressManager.h"
#include "AddressDefinitions.h"

using namespace std;
list<AddressEntry>* AddressManager::addresses;
unsigned int AddressManager::dllBaseAddress;

void AddressManager::Init(unsigned int dllBaseAddr)
{
	dllBaseAddress = defaultBaseAddr;

	if (dllBaseAddr != dllBaseAddress)
	{
		dllBaseAddress = dllBaseAddr;
		
		for (AddressEntry& e : *addresses)
		{
			if (!e.IsMOHAAAddress())
			{
				e.SetBase(dllBaseAddress);
			}
		}
	}
}

void AddressManager::Shutdown()
{
	if (addresses)
	{
		delete addresses;
	}
}

AddressEntry& AddressManager::AddAddress(unsigned int address, bool isMOH)
{
	if (!addresses)
	{
		addresses = new list<AddressEntry>();
	}
	return addresses->emplace_back(address, defaultBaseAddr, isMOH);
}
