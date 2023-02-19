#include "ClientFilter.h"
#include "CustomCvar.h"

list<ClientFilter> ClientFilter::clients;

constexpr int pingCheckInterval = 10000;
constexpr int pingKickLimit = 5;

list<ClientFilter>::iterator ClientFilter::findClientIndex(int cnum)
{
	list<ClientFilter>::iterator it;
	for (it = clients.begin(); it != clients.end(); it++)
	{
		if (it->client_num == cnum)
		{
			return it;
		}
	}
	return it;
}

ClientFilter::ClientFilter()
{
}

ClientFilter::ClientFilter(int cnum, bool conn)
{
	connected = conn;
	client_num = cnum;
	last_ping_check_time = 0;
	ping_exceeded_count = 0;
}

void ClientFilter::ClientConnected(int cnum, int ms)
{
	list<ClientFilter>::iterator it = findClientIndex(cnum);
	if (it == clients.end())
	{
		clients.emplace_back(cnum, false);
		it = clients.end();
		it--;
	}

	it->SetLastPingCheckTime(ms);
}

void ClientFilter::ClientDisconnected(int cnum)
{
	list<ClientFilter>::iterator it = findClientIndex(cnum);
	if (it != clients.end())
	{
		clients.erase(it);
	}
}

ClientFilter& ClientFilter::GetClient(int cnum)
{
	list<ClientFilter>::iterator it = findClientIndex(cnum);
	return *it;
}

//true: kick player
bool ClientFilter::CheckPingKick(int cnum, int ping, gentity_t * ent)
{
	CustomCvar sv_kickping("sv_kickping", "500", CVAR_ARCHIVE);

	//kick ping check
	if (sv_kickping.GetIntValue() > 0)
	{
		ClientFilter& cli = ClientFilter::GetClient(cnum);
		int currTime = gi.Milliseconds();
		if (currTime > cli.GetLastPingCheckTime() + pingCheckInterval)
		{
			int exceededCount = cli.GetPingExceededCOunt();
			cli.SetLastPingCheckTime(currTime);

			if (ping > sv_kickping.GetIntValue())
			{

				exceededCount++;

				cli.SetPingExceededCOunt(exceededCount);

				//if he's too slow for too long, kick him and don't operate his data anymore
				if (exceededCount > pingKickLimit)
				{
					return true;
				}
				else if (exceededCount == pingKickLimit - 1)
				{
					gi.Printf("%s will be kicked for high ping (> %i ms)\n", ent->client->pers.netname, sv_kickping.GetIntValue());
					gi.centerprintf(ent, "You will be kicked for high ping (> %i ms) shortly.\n", sv_kickping.GetIntValue());
				}
			}
			//if he's lower, decrease/reset the count
			else
			{
				if (exceededCount > 2)
				{
					exceededCount -= 2;
				}
				else
				{
					exceededCount = 0;
				}
				cli.SetPingExceededCOunt(exceededCount);

			}
		}
	}

	return false;
}

int ClientFilter::GetLastPingCheckTime()
{
	return last_ping_check_time;
}

void ClientFilter::SetLastPingCheckTime(int ms)
{
	last_ping_check_time = ms;
}

int ClientFilter::GetPingExceededCOunt()
{
	return ping_exceeded_count;
}

void ClientFilter::SetPingExceededCOunt(int ms)
{
	ping_exceeded_count = ms;
}
