#include "Player.h"
#include "g_misc.h"

ResponseDef<Player> *Player::Responses;

CustomEventResponseSet<Player> Player::cerSet{};

Player::Player()
{
}


Player::~Player()
{
}


void Player::Test(Event*ev)
{
	gentity_t *gent = G_GetEntityByClient(0);
	gi.centerprintf(gent,"Player Test success");
}

void Player::Init()
{
	cerSet.AddEventResponse(new Event(
		"ptest",
		EV_DEFAULT,
		NULL,
		NULL,
		"PLAYER TEST COMMAND"
	),
		&Player::Test);


	int rscount = cerSet.size()+1;
	size_t sz = sizeof(ResponseDef<Player>) * rscount;
	//Responses = reinterpret_cast<ResponseDef<Player>*>(gi.Malloc(sz));
	Responses = new ResponseDef<Player>[rscount];
	memset(Responses, 0, sz);

	//Could be added as a member func of cerSet.
	for (size_t i = 0; i < rscount-1; i++)
	{
		const std::string str = cerSet.GetResponseFuncAt(i).target_type().name();
		const std::string str2 = typeid(ResponseDef<Player>::response).name();
		Responses[i].event = cerSet.GetEventAt(i);
		Responses[i].response = *cerSet.GetResponseFuncAt(i).target<void(Player::*)(Event*)>();
	}
}

void Player::Shutdown()
{
	for (size_t i = 0; i < cerSet.size(); i++)
	{
		Event* ev = cerSet.GetEventAt(i);
		if (ev)
		{
			delete ev;
		}
	}
	//gi.Free(Responses);
	delete Responses;
}
