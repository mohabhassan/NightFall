#pragma once
#include "Event.h"
#include "ClassDef.h"
#include "Class.h"
#include "CustomEventResponseSet.h"
class Player : public Class
{
public:
	Player();
	~Player();
	void Test(Event * ev);
	static ResponseDef<Player>	*Responses;
	static CustomEventResponseSet<Player> cerSet;
	static void Init();
	static void Shutdown();
};

