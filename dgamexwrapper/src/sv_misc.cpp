#include "sv_misc.h"
#include "Winsock2.h"

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

string GetIPFromClient(client_t* cl)
{
	if (!cl)
		return "";
	if (cl->netchan.remoteAddress.type == NA_LOOPBACK)
		return "127.0.0.1";
	else if (cl->netchan.remoteAddress.type == NA_IP)
		return string(to_string(cl->netchan.remoteAddress.ip[0]) + "." + to_string(cl->netchan.remoteAddress.ip[1]) + "." + to_string(cl->netchan.remoteAddress.ip[2]) + "." + to_string(cl->netchan.remoteAddress.ip[3]));
	else
		return "";
}

string GetPortFromClient(client_t* cl)
{
	if (!cl)
		return "";
	return to_string(ntohs(cl->netchan.remoteAddress.port));
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
