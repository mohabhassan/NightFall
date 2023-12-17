#pragma once
#include <list>
#include <string>
#include <unordered_map>

constexpr unsigned int defaultBaseAddr = 0x31000000;
class AddressEntry
{
	unsigned int address;
	unsigned int base;
	bool isMOHAA;
public:
	AddressEntry()
	{}
	void Init(int addr, int bAddr, bool isMOH)
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
	static std::unordered_map<std::string, AddressEntry> addresses;
	static std::unordered_map<std::string, unsigned int> dgamex_offsets;
	static unsigned int dllBaseAddress;
public:
	static void InitAddresses();
	static void Init(unsigned int dllBaseAddr);
	static void Shutdown();
	
	static AddressEntry& AddAddress(std::string name, unsigned int address, bool isMOH = false);
	static AddressEntry& GetAddress(std::string name);
	
};

