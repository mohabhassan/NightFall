#pragma once
#include "dgamex86.h"

void SV_Misc_Init();


client_t * GetClientByClientNum(int clientNum);

void __cdecl NET_OutOfBandPrint(netSrc_t sock, netAdr_t adr, const char *format, ...);