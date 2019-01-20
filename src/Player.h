#pragma once
#include "Event.h"
#include "ClassDef.h"
#include "CustomEventResponseSet.h"
#include "Sentient.h"
class Player : public Sentient
{
public:
	Player();
	~Player();
	static ResponseDef<Player>	*Responses;
	static CustomEventResponseSet<Player> cerSet;
	static void Init();
	static void Shutdown();

	void Test(Event * ev);
};

