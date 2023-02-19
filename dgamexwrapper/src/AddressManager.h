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

