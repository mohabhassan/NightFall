#pragma once
#include "dgamex86.h"

#include <string>

using std::string;

void SV_Misc_Init();


client_t * GetClientByClientNum(int clientNum);

void __cdecl NET_OutOfBandPrint(netSrc_t sock, netAdr_t adr, const char *format, ...);

string NetAdrToIPString(netAdr_t& adr);
string NetAdrToPortString(netAdr_t& adr);
string NetAdrToIPPortString(netAdr_t& adr);

string GetIPFromClient(client_t* cl);
string GetPortFromClient(client_t* cl);
string GetIPPortFromClient(client_t* cl);
