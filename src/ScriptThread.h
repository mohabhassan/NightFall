#pragma once
#include "Event.h"
#include "ClassDef.h"
#include "Listener.h"
#include "CustomEventResponseSet.h"
class ScriptThread : public Listener
{
public:
	ScriptThread();
	~ScriptThread();
	static ResponseDef<ScriptThread>	*Responses;
	static CustomEventResponseSet<ScriptThread> cerSet;

	static void Init();
	static void Shutdown();


	void		PlayerNetNameEvent(Event * ev);
	void		StuffSrvEvent(Event * ev);
	void		PlayerGetIpEvent(Event * ev);
	void		PlayerGetPingEvent(Event * ev);
	void		PlayerGetClientNumEvent(Event * ev);
	void		GetEntityEvent(Event * ev);
	void		iHudDrawAlignEvent(Event * ev);
	void		iHudDrawAlphaEvent(Event * ev);
	void		iHudDrawColorEvent(Event * ev);
	void		iHudDrawFontEvent(Event *ev);
	void		iHudDrawRectEvent(Event *ev);
	void		iHudDrawShaderEvent(Event *ev);
	void		iHudDrawStringEvent(Event *ev);
	void		iHudDrawVirtualSizeEvent(Event *ev);
	void		Test(Event*ev);
};

