#pragma once
#include "Entity.h"
#include "Event.h"

class Animate {};// empty definition to avoid mistakes

/*
 * Class Animate
 * Used as a subclass of other important classes. 
 **/
class AnimateAA : public EntityAA
{
protected:
	int			animFlags[MAX_FRAMEINFOS];//0

	float		syncTime;//16
	float		syncRate;//17
	int			pauseSyncTime;//18


	Event		*doneEvents[MAX_FRAMEINFOS];//18

	float		animtimes[MAX_FRAMEINFOS];//36
	float		frametimes[MAX_FRAMEINFOS];//52

public:
	Vector		frame_delta;//68
};


class AnimateDSH : public EntityDSH
{
protected:
	int			animFlags[MAX_FRAMEINFOS];//0

	float		syncTime;//16
	float		syncRate;//17
	int			pauseSyncTime;//18
	int			dummy1;//19 BT //FIXME: seems bool/qboolean

	Event* doneEvents[MAX_FRAMEINFOS];//18

	float		animtimes[MAX_FRAMEINFOS];//36
	float		frametimes[MAX_FRAMEINFOS];//52

public:
	Vector		frame_delta;//68
	int			dummy2;//71 BT
};

using AnimateDBT = AnimateDSH;
