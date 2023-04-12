#include "ScriptThread.h"

void ScriptThread::MathsInit()
{
#ifdef MOHAA
	cerSet.AddEventResponse(new Event(
		"sin",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the sine of an angle of x radians.",
		EV_RETURN
	),
		&ScriptThread::MSinEvent);

	cerSet.AddEventResponse(new Event(
		"cos",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the cosine of an angle of x radians.",
		EV_RETURN
	),
		&ScriptThread::MCosEvent);
	cerSet.AddEventResponse(new Event(
		"tan",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the tangent of an angle of x radians.",
		EV_RETURN
	),
		&ScriptThread::MTanEvent);

	cerSet.AddEventResponse(new Event(
		"atan",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the arc tangent of an angle of x radians. Use atan2 instead.",
		EV_RETURN
	),
		&ScriptThread::MATanEvent);
#endif

	cerSet.AddEventResponse(new Event(
		"asin",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the arc sine of an angle of x radians.",
		EV_RETURN
	),
		&ScriptThread::MASinEvent);

	cerSet.AddEventResponse(new Event(
		"acos",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the arc cosine of an angle of x radians.",
		EV_RETURN
	),
		&ScriptThread::MACosEvent);


	cerSet.AddEventResponse(new Event(
		"atan2",
		EV_DEFAULT,
		"ff",
		"y x",
		"Returns the principal value of the arc tangent of y/x, expressed in radians.",
		EV_RETURN
	),
		&ScriptThread::MATan2Event);

	cerSet.AddEventResponse(new Event(
		"sinh",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the hyperbolic sine of x.",
		EV_RETURN
	),
		&ScriptThread::MSinhEvent);

	cerSet.AddEventResponse(new Event(
		"cosh",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the hyperbolic cosine of x.",
		EV_RETURN
	),
		&ScriptThread::MCoshEvent);

	cerSet.AddEventResponse(new Event(
		"tanh",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the hyperbolic tangent of x.",
		EV_RETURN
	),
		&ScriptThread::MTanhEvent);

	cerSet.AddEventResponse(new Event(
		"exp",
		EV_DEFAULT,
		"f",
		"x",
		"Returns e to the power of x.",
		EV_RETURN
	),
		&ScriptThread::MExpEvent);

	cerSet.AddEventResponse(new Event(
		"frexp",
		EV_DEFAULT,
		"f",
		"x",
		"Get significand and exponent.",
		EV_RETURN
	),
		&ScriptThread::MFrexpEvent);

	cerSet.AddEventResponse(new Event(
		"ldexp",
		EV_DEFAULT,
		"fi",
		"x exponent",
		"Generate number from significand and exponent.",
		EV_RETURN
	),
		&ScriptThread::MLdexpEvent);

	cerSet.AddEventResponse(new Event(
		"log",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the natural logarithm of x.",
		EV_RETURN
	),
		&ScriptThread::MLogEvent);

	cerSet.AddEventResponse(new Event(
		"log10",
		EV_DEFAULT,
		"f",
		"x",
		"Returns logarithm of x to the base 10.",
		EV_RETURN
	),
		&ScriptThread::MLog10Event);

	cerSet.AddEventResponse(new Event(
		"modf",
		EV_DEFAULT,
		"f",
		"x",
		"Break into fractional and integral parts.",
		EV_RETURN
	),
		&ScriptThread::MModfEvent);

	cerSet.AddEventResponse(new Event(
		"pow",
		EV_DEFAULT,
		"fi",
		"x exponent",
		"Returns x raised to the power of exponent.",
		EV_RETURN
	),
		&ScriptThread::MPowEvent);

	cerSet.AddEventResponse(new Event(
		"sqrt",
		EV_DEFAULT,
		"f",
		"x",
		"Returns the square root of x.",
		EV_RETURN
	),
		&ScriptThread::MSqrtEvent);

	cerSet.AddEventResponse(new Event(
		"ceil",
		EV_DEFAULT,
		"f",
		"x",
		"Round up value.",
		EV_RETURN
	),
		&ScriptThread::MCeilEvent);

	cerSet.AddEventResponse(new Event(
		"floor",
		EV_DEFAULT,
		"f",
		"x",
		"Round down value.",
		EV_RETURN
	),
		&ScriptThread::MFloorEvent);

	cerSet.AddEventResponse(new Event(
		"fmod",
		EV_DEFAULT,
		"ff",
		"num denom",
		"Compute remainder of division.",
		EV_RETURN
	),
		&ScriptThread::MFmodEvent);
}

void ScriptThread::MSinEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for sin!\n");
		return;
	}

	ev->AddFloat(sin(ev->GetFloat(1)));
}

void ScriptThread::MCosEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for cos!\n");
		return;
	}

	ev->AddFloat(cos(ev->GetFloat(1)));
}

void ScriptThread::MTanEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for tan!\n");
		return;
	}

	ev->AddFloat(tan(ev->GetFloat(1)));
}

void ScriptThread::MASinEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for asin!\n");
		return;
	}

	ev->AddFloat(asin(ev->GetFloat(1)));
}

void ScriptThread::MACosEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for acos!\n");
		return;
	}

	ev->AddFloat(acos(ev->GetFloat(1)));
}

void ScriptThread::MATanEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for atan!\n");
		return;
	}

	ev->AddFloat(atan(ev->GetFloat(1)));
}

void ScriptThread::MATan2Event(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for atan2!\n");
		return;
	}

	ev->AddFloat(atan2(ev->GetFloat(1),ev->GetFloat(2)));
}

void ScriptThread::MSinhEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for sinh!\n");
		return;
	}

	ev->AddFloat(sinh(ev->GetFloat(1)));
}

void ScriptThread::MCoshEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for cosh!\n");
		return;
	}

	ev->AddFloat(cosh(ev->GetFloat(1)));
}

void ScriptThread::MTanhEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for tanh!\n");
		return;
	}

	ev->AddFloat(tanh(ev->GetFloat(1)));
}

void ScriptThread::MExpEvent(Event*ev)
{
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for exp!\n");
		return;
	}

	ev->AddFloat(exp(ev->GetFloat(1)));
}

void ScriptThread::MFrexpEvent(Event*ev)
{
	float sig;
	int expon = 0;
	int argnum = ev->NumArgs();
	ScriptVariable array;
	ScriptVariable index, value;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for frexp!\n");
		return;
	}

	sig = frexp(ev->GetFloat(1), &expon);

	index.setStringValue("significand");
	value.setFloatValue(sig);
	array.setArrayAtRef(index, value);

	index.setStringValue("exponent");
	value.setIntValue(expon);
	array.setArrayAtRef(index, value);

	ev->AddValue(array);
}

void ScriptThread::MLdexpEvent(Event *ev)
{
	float sig = 0;
	int expon = 0;
	int argnum = ev->NumArgs();

	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for ldexp!\n");
		return;
	}

	sig = ev->GetFloat(1);
	expon = ev->GetInteger(2);

	ev->AddFloat(ldexp(sig, expon));
}

void ScriptThread::MLogEvent(Event *ev)
{
	float x = 0;
	int argnum = ev->NumArgs();

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for log!\n");
		return;
	}

	x = ev->GetFloat(1);

	ev->AddFloat(log(x));
}

void ScriptThread::MLog10Event(Event *ev)
{
	float x = 0;
	int argnum = ev->NumArgs();

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for log10!\n");
		return;
	}

	x = ev->GetFloat(1);

	ev->AddFloat(log10(x));
}

void ScriptThread::MModfEvent(Event*ev)
{
	float frac;
	float intpart = 0;
	int argnum = ev->NumArgs();
	ScriptVariable array;
	ScriptVariable index, value;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for modf!\n");
		return;
	}

	frac = modf(ev->GetFloat(1), &intpart);

	index.setStringValue("intpart");
	value.setIntValue(intpart);
	array.setArrayAtRef(index, value);

	index.setStringValue("fractional");
	value.setFloatValue(frac);
	array.setArrayAtRef(index, value);

	ev->AddValue(array);
}

void ScriptThread::MPowEvent(Event *ev)
{
	float x = 1;//safety
	int exponent = 0;
	int argnum = ev->NumArgs();

	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for pow!\n");
		return;
	}

	x = ev->GetFloat(1);
	exponent = ev->GetInteger(2);

	ev->AddFloat(pow(x,exponent));
}

void ScriptThread::MSqrtEvent(Event *ev)
{
	float x = 0;
	int argnum = ev->NumArgs();

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for sqrt!\n");
		return;
	}

	x = ev->GetFloat(1);

	ev->AddFloat(sqrt(x));
}

void ScriptThread::MCeilEvent(Event *ev)
{
	float x = 0;
	int argnum = ev->NumArgs();

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for ceil!\n");
		return;
	}

	x = ev->GetFloat(1);

	ev->AddFloat(ceil(x));
}

void ScriptThread::MFloorEvent(Event *ev)
{
	float x = 0;
	int argnum = ev->NumArgs();

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for floor!\n");
		return;
	}

	x = ev->GetFloat(1);

	ev->AddFloat(floor(x));
}

void ScriptThread::MFmodEvent(Event *ev)
{
	float num = 0;
	float denom = 1;
	int argnum = ev->NumArgs();

	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fmod!\n");
		return;
	}

	num = ev->GetFloat(1);
	denom = ev->GetFloat(2);

	ev->AddFloat(fmod(num, denom));
}