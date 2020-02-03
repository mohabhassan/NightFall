#include "sv_misc.h"

client_t **svs_clients;
int *svs_numclients;

typedef void(__cdecl *net_oob_print_t) (netSrc_t sock, netAdr_t adr, const char *format, ...);
net_oob_print_t NET_OutOfBandPrint_Real;


client_t * GetClientByClientNum(int clientNum)
{
	if (clientNum >= *svs_numclients || clientNum < 0)
	{
		return NULL;
	}
	else
	{
		return &(*svs_clients)[clientNum];
	}
}

void __cdecl NET_OutOfBandPrint(netSrc_t sock, netAdr_t adr, const char * format, ...)
{
	va_list		argptr;
	char		string[MAX_MSGLEN];
	va_start(argptr, format);
	vsnprintf(string, sizeof(string), format, argptr);
	va_end(argptr);
	NET_OutOfBandPrint_Real(sock, adr, string);
}

void SV_Misc_Init()
{
	svs_clients = reinterpret_cast<client_t**>((int)SVS_CLIENTS_ADDR);
	svs_numclients = reinterpret_cast<int*>((int)SVS_NUMCLIENTS_ADDR);
	NET_OutOfBandPrint_Real = reinterpret_cast<net_oob_print_t>((int)NET_OUTOFBANDPRINT_ADDR);
}
