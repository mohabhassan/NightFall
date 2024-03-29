#pragma once
#include "Listener.h"
#include "ScriptVariable.h"
#include "Class.h"
#include "Director.h"
#include "Entity.h"
#include <cstdint>
class EventDef {
public:
	//int				dummy;//Extra in BT
	str		 		command;
	int				flags;
	const char		*formatspec;
	const char		*argument_names;
	const char		*documentation;
	uint8_t			type;
	//void /*Container<EventArgDef>*/ *definition; //Extra in opm

	//EventDef() { definition = NULL; } //Extra in opm
	/*
		void Error(const char *format, ...);

		void PrintDocumentation(FILE *event_file, bool html);
		void PrintEventDocumentation(FILE *event_file, bool html);

		void DeleteDocumentation(void);
		void SetupDocumentation(void);
	*/
};
//template< typename k = Event * , typename v = EventDef>
class Entry_eventdeflist
{
public:
	Event *						key;
	EventDef					value;
	//unsigned int			index;//Not used in BT
	Entry_eventdeflist			*next;
	/*
public:
	void *operator new(size_t size)
	{

	}
	void operator delete(void *ptr)
	{

	}

	Entry_eventdeflist()
	{

	}
	*/
};
class con_set_eventdeflist
{
	Entry_eventdeflist			**table;
	unsigned int				tableLength;
	unsigned int				threshold;
	unsigned int				count;
	short unsigned int			tableLengthIndex;
	Entry_eventdeflist			*defaultEntry;
public:
	Entry_eventdeflist *findKeyEntry(const Event * key) const
	{
		Entry_eventdeflist *entry;

		entry = table[(int)key % tableLength];

		for (; entry != NULL; entry = entry->next)
		{
			if (entry->key == key) {
				return entry;
			}
		}

		return NULL;
	}
	int getTableLength() const
	{
		return tableLength;
	}
};

class con_map_eventdeflist
{
	con_set_eventdeflist m_con_set;
public:
	const con_set_eventdeflist &getConSet() const
	{
		return m_con_set;
	}
};


// Event flags
#define EV_CONSOLE				(1<<0)		// Allow entry from console
#define EV_CHEAT				(1<<1)		// Only allow entry from console if cheats are enabled
#define EV_CODEONLY				(1<<2)		// Hide from eventlist
#define EV_CACHE				(1<<3)		// This event is used to cache data in
#define EV_TIKIONLY				(1<<4)		// This command only applies to TIKI files
#define EV_SCRIPTONLY			(1<<5)		// This command only applies to SCRIPT files
#define EV_SERVERCMD			(1<<6)		// Client : server command
#define EV_DEFAULT				-1			// default flag


// Event types
#define EV_NORMAL				0	// Normal command
#define EV_RETURN				1	// Return as a function (local.var = local ReturnCommand)
#define EV_GETTER				2	// Return as a variable (local.var = local.listener.some_getter)
#define EV_SETTER				3	// Set as a variable (local.listener.some_setter = "value")

class Event;

//eventInfo has the exact same structure for BT.
typedef struct eventInfo_s
{
	Event		*ev;
	const char	*command;
	int			flags;
	const char	*formatspec;
	const char	*argument_names;
	const char	*documentation;
	int			type;
	struct eventInfo_s	*prev;
} eventInfo_t;

class Event : public Class
{
public:
	qboolean			fromScript;
	short unsigned int	eventnum; //set by game
	short unsigned int	dataSize;
	ScriptVariable		*data;

	static con_map_eventdeflist *eventDefList;
	static int *totalevents;
	static int NumEventCommands();
	//EventDef * getInfo();
	static void(__thiscall *AddListener_Real)(Event* _this, Listener *listener);
	static ScriptVariable*(__thiscall *GetValue_Real)(Event* _this);
	static void Init();

	Event();
	Event
	(
		const char *command,
		int flags,
		const char *formatspec,		// Arguments are : 'e' (Entity) 'v' (Vector) 'i' (Integer) 'f' (Float) 's' (String) 'b' (Boolean).
									// Uppercase arguments means optional.
		const char *argument_names,
		const char *documentation,
		uchar type = EV_NORMAL
	);
	~Event();
	void Clear(void);


	//void		AddContainer(Container< SafePtr< Listener > > *container);
	void		AddEntity(Entity * ent);
	void		AddFloat(float number);
	void		AddInteger(int number);
	void		AddListener(Listener * listener);
	void		AddNil(void);
	void		AddConstString(const_str string);
	void		AddString(str string);
	void		AddToken(str token);
	void		AddTokens(int argc, const char **argv);
	void		AddValue(const ScriptVariable &value);
	void		AddVector(const Vector& vector);

	int				NumArgs();

	bool			GetBoolean(int pos);


	float			GetFloat(int pos);
	int				GetInteger(int pos);


	str				GetString(int pos);
	str				GetToken(int pos);
	Entity			*GetEntity(int pos);
	void			CheckPos(int pos);
	ScriptVariable&	GetValue(int pos);
	ScriptVariable&	GetValue(void);
	Vector			GetVector(int pos);
};

