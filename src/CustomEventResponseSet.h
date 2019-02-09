#pragma once
#include "Event.h"
#include "ClassDef.h"
#include <vector>
#include <functional>
using namespace std;
template <class Type>
class CustomEventResponseSet
{
	vector<Event*> cEvents;//Custom Events
	using responseFuncPtr = function<void(Type*, Event*)>;
	vector<responseFuncPtr> cResponseFuncs;//Custom Response FUncs
public:
	void AddEventResponse(Event *ev, responseFuncPtr response)
	{
		if (ev && response)
		{
			cEvents.push_back(ev);
			cResponseFuncs.push_back(response);
		}
	};
	Event *GetEventAt(int i)
	{
		if (i >= 0 && i < cEvents.size())
		{
			return cEvents[i];
		}
		else
		{
			return nullptr;
		}
	}
	responseFuncPtr GetResponseFuncAt(int i)
	{
		if (i >= 0 && i < cResponseFuncs.size())
		{
			return cResponseFuncs[i];
		}
		else
		{
			return nullptr;
		}
	}

	int size()
	{
		return cEvents.size();
	}

	void Clear()
	{
		cEvents.clear();
		cResponseFuncs.clear();
	}
};
