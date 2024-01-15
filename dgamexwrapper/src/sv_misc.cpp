#include "sv_misc.h"
#include "Winsock2.h"
#include "AddressDefinitions.h"

using std::to_string;

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
		if (gameInfo.IsAA())
			return (client_t*)&((clientAA_t*)*svs_clients)[clientNum];
		else
			return (client_t*)&((clientDSH_t*)*svs_clients)[clientNum];

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

string NetAdrToIPString(netAdr_t& adr)
{
	if (adr.type == NA_LOOPBACK)
		return "127.0.0.1";
	else if (adr.type == NA_IP)
		return string(to_string(adr.ip[0]) + "." + to_string(adr.ip[1]) + "." + to_string(adr.ip[2]) + "." + to_string(adr.ip[3]));
	else
		return "";
}

string NetAdrToPortString(netAdr_t& adr)
{
	return to_string(ntohs(adr.port));
}

string NetAdrToIPPortString(netAdr_t& adr)
{
	return NetAdrToIPString(adr) + ":" + NetAdrToPortString(adr);
}

string GetIPFromClient(client_t* cl_actual)
{
	if (!cl_actual)
		return "";
	Client cl(cl_actual);
	return NetAdrToIPString(cl->netchan.remoteAddress);
}

string GetPortFromClient(client_t* cl_actual)
{
	if (!cl_actual)
		return "";
	Client cl(cl_actual);
	return NetAdrToPortString(cl->netchan.remoteAddress);
}

string GetIPPortFromClient(client_t* cl)
{
	if (!cl)
		return "";
	return GetIPFromClient(cl) + ":" + GetPortFromClient(cl);
}

void SV_Misc_Init()
{
	svs_clients = reinterpret_cast<client_t**>((int)SVS_CLIENTS_ADDR);
	svs_numclients = reinterpret_cast<int*>((int)SVS_NUMCLIENTS_ADDR);
	NET_OutOfBandPrint_Real = reinterpret_cast<net_oob_print_t>((int)NET_OUTOFBANDPRINT_ADDR);
}
