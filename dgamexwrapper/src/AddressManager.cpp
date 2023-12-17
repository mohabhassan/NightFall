#include "AddressManager.h"
#include "AddressDefinitions.h"

using namespace std;
unordered_map<string, AddressEntry> AddressManager::addresses;
unsigned int AddressManager::dllBaseAddress;

void AddressManager::Init(unsigned int dllBaseAddr)
{
	InitAddresses();

	dllBaseAddress = defaultBaseAddr;

	if (dllBaseAddr != dllBaseAddress)
	{
		dllBaseAddress = dllBaseAddr;
		
		for (auto& pair : addresses)
		{
			AddressEntry& e = pair.second;
			if (!e.IsMOHAAAddress())
			{
				e.SetBase(dllBaseAddress);
			}
		}
	}

}

void AddressManager::Shutdown()
{
}

AddressEntry& AddressManager::AddAddress(std::string name, unsigned int address, bool isMOH)
{
	AddressEntry& e = addresses[name];
	e.Init(address, defaultBaseAddr, isMOH);
	return e;
}

AddressEntry& AddressManager::GetAddress(std::string name)
{
	return addresses[name];
}
