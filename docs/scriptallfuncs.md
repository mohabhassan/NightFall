# NightFall Script Functions Documentation
## Table of Contents
- [NightFall Script Functions Documentation](#nightfall-script-functions-documentation)
  - [Table of Contents](#table-of-contents)
  - [ScriptThread Date/Time Functions](#scriptthread-datetime-functions)
    - [gettime](#gettime)
    - [gettimezone](#gettimezone)
    - [getdate](#getdate)
  - [ScriptThread Maths Functions](#scriptthread-maths-functions)
    - [sin](#sin)
    - [cos](#cos)
    - [tan](#tan)
    - [atan](#atan)
    - [atan2](#atan2)
    - [asin](#asin)
    - [acos](#acos)
    - [sinh](#sinh)
    - [cosh](#cosh)
    - [tanh](#tanh)
    - [exp](#exp)
    - [frexp](#frexp)
    - [ldexp](#ldexp)
    - [log](#log)
    - [log10](#log10)
    - [modf](#modf)
    - [pow](#pow)
    - [sqrt](#sqrt)
    - [ceil](#ceil)
    - [floor](#floor)
    - [fmod](#fmod)
  - [ScriptThread Miscellaneous Functions](#scriptthread-miscellaneous-functions)
    - [setcvar\_ex](#setcvar_ex)
    - [stuffsrv](#stuffsrv)
    - [conprintf](#conprintf)
    - [md5string](#md5string)
    - [md5file](#md5file)
    - [typeof](#typeof)
    - [setproperty](#setproperty)
    - [getproperty](#getproperty)
    - [constarray](#constarray)
    - [regex\_parse](#regex_parse)
    - [json\_parse](#json_parse)
    - [json\_stringify](#json_stringify)
    - [chartoint](#chartoint)
    - [teamswitchdelay](#teamswitchdelay)
    - [getentity](#getentity)
    - [netname](#netname)
    - [getip](#getip)
    - [getping](#getping)
    - [getclientnum](#getclientnum)
    - [traced](#traced)
    - [ihuddraw\_align](#ihuddraw_align)
    - [ihuddraw\_alpha](#ihuddraw_alpha)
    - [ihuddraw\_color](#ihuddraw_color)
    - [ihuddraw\_font](#ihuddraw_font)
    - [ihuddraw\_rect](#ihuddraw_rect)
    - [ihuddraw\_shader](#ihuddraw_shader)
    - [ihuddraw\_string](#ihuddraw_string)
    - [ihuddraw\_virtualsize](#ihuddraw_virtualsize)
    - [registerev](#registerev)
    - [unregisterev](#unregisterev)
  - [ScriptThread File System Functions](#scriptthread-file-system-functions)
    - [fopen](#fopen)
    - [fclose](#fclose)
    - [feof](#feof)
    - [fseek](#fseek)
    - [ftell](#ftell)
    - [fgetc](#fgetc)
    - [fputc](#fputc)
    - [fgets](#fgets)
    - [fputs](#fputs)
    - [ferror](#ferror)
    - [fflush](#fflush)
    - [fexists](#fexists)
    - [freadall](#freadall)
    - [fsaveall](#fsaveall)
    - [fremove](#fremove)
    - [frename](#frename)
    - [fcopy](#fcopy)
    - [freadpak](#freadpak)
    - [flist](#flist)
    - [fnewdir](#fnewdir)
    - [fremovedir](#fremovedir)
  - [ScriptThread API Functions](#scriptthread-api-functions)
    - [create\_api\_request](#create_api_request)
    - [register\_api\_route](#register_api_route)
    - [unregister\_api\_route](#unregister_api_route)
  - [Player Miscellaneous Functions](#player-miscellaneous-functions)
    - [userinfo](#userinfo)
    - [getkills](#getkills)
    - [getdeaths](#getdeaths)
    - [.secfireheld](#secfireheld)
    - [.runheld](#runheld)
    - [.leanleftheld](#leanleftheld)
    - [.leanrightheld](#leanrightheld)
    - [.inventory](#inventory)
    - [getactiveweap](#getactiveweap)
    - [getconnstate](#getconnstate)
    - [isadmin](#isadmin)
    - [adminrights](#adminrights)
    - [bindweap](#bindweap)
  - [References](#references)
    - [C numerics library](#c-numerics-library)
    - [C standard Input/Output library](#c-standard-inputoutput-library)
    - [Reborn Scripting Commands](#reborn-scripting-commands)
## ScriptThread Date/Time Functions
---
### gettime
	gettime(integer zero)
Gets current time in format: H:M:S

Example:
```
local.time = gettime 0

```
Result:
```
String with current time.
```
---
---
### gettimezone
	gettimezone(integer zero)
Gets current time zone

Example:
```
local.time = gettimezone 0

```
Result:
```
Integer representing time zone offset from GMT
local.result = 2 //GMT+2
local.result = -10 //GMT-10
```
---
---
### getdate
	getdate(integer zero) (1)
	getdate(string format) (2)
(1) Gets current date in format: dd.mm.yyyy

(2) Gets current date in format given as parameter.
> **Note:** Max format length is 512 characters.

Example:
```
local.date1 = getdate 0
local.date2 = getdate "%D"

```
Result:
```
String with current date.

local.date1 = "23.08.2001"
local.date2 = "08/23/01"
```
---

## ScriptThread Maths Functions
---
Most of these functions use their [C numerics library](#c-numerics-library) counterparts under the hood, please refer to [C numerics library](#c-numerics-library) for more information.

---
### sin
	sin(float x)
Returns the sine of an angle of x radians.

> **Warning:** For SH/BT, x is expected to be in degrees.


Example:
```
local.result = sin local.x

```
Result:
```
Sine of x.
```
---
---
### cos
	cos(float x)
Returns the cosine of an angle of x radians.

> **Warning:** For SH/BT, x is expected to be in degrees.


Example:
```
local.result = cos local.x

```
Result:
```
Cosine of x.
```
---
---
### tan
	tan(float x)
Returns the tangent of an angle of x radians.

> **Warning:** For SH/BT, x is expected to be in degrees.


Example:
```
local.result = tan local.x

```
Result:
```
Tangent of x.
```
---
---
### atan
	atan(float x)
Returns the arc tangent of x in radians.

> **Warning:** For SH/BT, result is expected to be in degrees.

> **Note:** If possible, use [atan2](#atan2) as it returns the angle in the proper quadrant.

Example:
```
local.result = atan local.x

```
Result:
```
Arc tangent of x in range [-pi/2,+pi/2].
```
---
---
### atan2
	atan2(float y, float x)
Returns the arc tangent of y/x in radians in the proper quadrant calculated from the signs of y and x.


Example:
```
local.result = atan2 local.y local.x

```
Result:
```
Arc tangent of y/x in range [-pi,+pi].
```
---
---
### asin
	asin(float x)
Returns the arc sine of x in radians.



Example:
```
local.result = asin local.x

```
Result:
```
Arc sine of x in range [-pi/2,+pi/2].
```
---
---
### acos
	acos(float x)
Returns the arc cosine of x in radians.



Example:
```
local.result = acos local.x

```
Result:
```
Arc cosine of x in range [0,pi].
```
---
---
### sinh
	sinh(float x)
Returns the hyperbolic sine of x.


Example:
```
local.result = sinh local.x

```
Result:
```
Hyperbolic sine of x.
```
---
---
### cosh
	cosh(float x)
Returns the hyperbolic cosine of x.


Example:
```
local.result = cosh local.x

```
Result:
```
Hyperbolic cosine of x.
```
---
---
### tanh
	tanh(float x)
Returns the hyperbolic tangent of x.


Example:
```
local.result = tanh local.x

```
Result:
```
Hyperbolic tangent of x.
```
---
---
### exp
	exp(float x)
Returns the base-e exponential function of x, which is e raised to the power x: e<sup>x</sup>.


Example:
```
local.result = exp local.x

```
Result:
```
E raised to the x: e^x.
```
---
---
### frexp
	frexp(float x)
Breaks the floating point number x into its binary significand (a floating point with an absolute value between 0.5(included) and 1.0(excluded)) and an integral exponent for 2, such that:

x = significand * 2 <sup>exponent</sup>


If x is zero, both parts (significand and exponent) are zero.

If x is negative, the significand returned by this function is negative.

Example:
```
local.result = freexp local.x

```
Result:
```
local.result["significand"] - significand part
local.result["exponent"] - exponent part
```
---
---
### ldexp
	ldexp(float significand, integer exponent)
Returns the result of multiplying the significand by 2 raised to the power of exp (the exponent).

x = significand * 2 <sup>exponent</sup>


Example:
```
local.result = freexp local.sig local.exp

```
Result:
```
returns the number x=(significand*(2^exponent))
```
---
---
### log
	log(float x)
Returns the Natural (base-e) logarithm of x.


Example:
```
local.result = log local.x

```
Result:
```
Natural logarithm of x.
```
---
---
### log10
	log10(float x)
Returns the common (base-10) logarithm of x.


Example:
```
local.result = log10 local.x

```
Result:
```
Common logarithm of x.
```
---
---
### modf
	modf(float x)

Breaks x into an integral and a fractional part.

Both parts have the same sign as x.

Example:
```
local.result = modf local.x

```
Result:
```
local.result["intpart"] - integer part
local.result["fractional"] - fractional part
```
---
---
### pow
	pow(float x, integer exp)

Raises x to the power exp.

Example:
```
local.result = pow local.x local.exp

```
Result:
```
X raised to the exponent.
```
---
---
### sqrt
	sqrt(float x)

Returns the square root of x.

Example:
```
local.result = sqrt local.x

```
Result:
```
Square root of x.
```
---
---
### ceil
	ceil(float x)

Rounds x upward, returning the smallest integral value that is not less than x.

Example:
```
local.result = ceil local.x

```
Result:
```
X rounded up.
```
---
---
### floor
	floor(float x)

Rounds x downward, returning the largest integral value that is not greater than x.

Example:
```
local.result = floor local.x

```
Result:
```
X rounded down.
```
---
---
### fmod
	fmod(float numerator, f loat denominator )

Returns the floating-point remainder of numerator/denominator (rounded towards zero):

fmod = numer - tquot * denom

Where tquot is the truncated (i.e., rounded towards zero) result of: numer/denom.

Example:
```
local.result = fmod local.num local.denom

```
Result:
```
Floating-point remainder of num/denom.
```
---
## ScriptThread Miscellaneous Functions
### setcvar_ex
	setcvar_ex(string cvar, string value, [string options="", integer flags=0])
Sets the `cvar` to `value` using the specified `options` and `flags`.
Currently supported `options`:
```
"s" or "S"        set cvar silently (will not print to log even if developer is set)
```
`flags` is reserved for future use

Example:
```
setcvar_ex "fraglimit" "1" "s" 0
or
setcvar_ex "fraglimit" "1" "S" 0

```
Result:
```
Changes fraglimit to 1 without printing "Cvar_Set2: fraglimit 1" to console/logfile
```
---
### stuffsrv
	stuffsrv(string cmd)
Executes command in server console.



Example:
```
stuffsrv restart

```
Result:
```
Server restarts
```
---
### conprintf
	conprintf(string text)
Prints text in server console.



Example:
```
conprintf test_print

```
Result:
```
Prints test_print to console.
```
---
---
### md5string
	md5string(string text)
Returns MD5 hash/checksum of text.



Example:
```
local.checksum = md5string test_md5

```
Result:
```
MD5 checksum of "test_md5".
```
---
---
### md5file
	md5file(string filename)
Returns MD5 hash/checksum of file.



Example:
```
local.checksum = md5file "test.txt"

```
Result:
```
MD5 checksum of file "test.txt".
```
---
---
### typeof
	typeof(variable var)
Returns type of var as string.



Example:
```
local.checksum = typeof local.var

```
Result:
```
Type of var as string.
```
Possible type names:
```
"none"
"string"
"int"
"float"
"char"
"const string"
"listener"
"ref"
"array"
"const array"
"pointer"
"vector"
"double"
```
---
---
### setproperty
	setproperty(string key, string value)
Sets property in local storage to given value.

Key and value can't be NULL. If you want to clear the value, you have to set it to empty string.


Example:
```
local.res = setproperty "my_mod_settings" "abcdefgh"

```
Result:
```
Returns integer value:

0 - Success
< 0 - Error
```
---
---
### getproperty
	getproperty(string key)
Gets property saved in local storage for given key.

Key can't be NULL.


Example:
```
local.res = getproperty "my_mod_settings"

```
Result:
```
Returns value as string or error code as integer.
```
---
---
### constarray
	constarray(array var)
Cast existing array to constarray.

A constarray variable's size cannot be changed, it has starting index of 1.

Example:
```
local.arr[1] = xtesddfgsf;//local.arr is a hasttable array
local.arr[2] = 2222;//local.arr is a hasttable array
local.result = constarray local.arr //local.result is a constarray
//above code is equivalent to
local.result = xtesddfgsf::2222
```
Result:
```
local.result will have one of the following values:

Nil if variable can't be converted.
Proper constarray value otherwise.
```
---
---
### regex_parse
	regex_parse(string pattern, string search_string, boolean whole_match)
Perform a regular expression search using pattern on string search_string.

If whole_match is set, parser will fail if whole string doesn't match the regex pattern.

> **Note:** In order to produce proper pattersn you must escape every backslash insde script, `\d+` becomes `"\\d+"` in script, `\\` becomes `"\\\\"` in script which matches a single backslash in string.
> 
Example:
```
local.result = regex_parse "a(a)*b" "baaaby" 0

```
Result:
```

local.result will be an array having the following structure:

local.result[success]: integer, 1 if regex is successfull, 0 if not.
local.result[matches]: array of strings containing capture group matches.

local.result[success] = 1
local.result[matches][0] = aaab
local.result[matches][1] = a
```

This option uses standard c++ library regex parser, regex_match is used when `whole_match` is 1 otherwise regex_search is used. Visit [cppreference](https://en.cppreference.com/w/cpp/regex) for more info.


---
---
### json_parse
	json_parse(string json_string)
Parse given `json_string` into a variable.
Returns NULL on failure

Example:
```
local.result = json_parse "{ \"happy\": true, \"pi\": 3.141 }"

```
Result:
```

local.result will be an array having the following structure:
local.result.size = 2
local.result[happy]: 1
local.result[pi]: 3.141
```
---
---
### json_stringify
	json_stringify(variable var)
Convert given `var` into a json string.

Resulting string will desribe a JSON object containing 2 keys: `content` and `type`.


Example:
```
local.result = json_stringify aaa::bb::cc

```
Result:
```
local.result = json_stringify aaa::bb::cc
local.result = {"content":[{"content":"aaa","type":"string"},{"content":"bb","type":"string"},{"content":"cc","type":"string"}],"type":"array"}
```

**IMPORTANT NOTE:** Non constant arrays have string indices instead of integer indices. Use [constarray](scriptfuncs.md#constarray) to convert an array to a constant array which will have integer indices.

**IMPORTANT NOTE:** Some variable types are not supported for conversion to JSON, these include: 

 - container, an array of listeners, $player for example
 - safe container, an array of listeners, $player for example
 - pointer, not usually used in scripts
 - reference, a reference to array, usually not used in scripts
---
---
### chartoint
	chartoint(string ch)
Return integer (corresponding ASCII value) representation of `ch`.

Example:
```
local.result = chartoint "a"
```
Result:
```
local.result = 97
```
---
---
### teamswitchdelay
	teamswitchdelay(integer delay)
Sets minimum delay `delay` to switch between teams.
This command is equivalent to `setcvar_ex "g_teamswitchdelay" delay "s" 0`
Example:
```
teamswitchdelay 50
```
Result:
```
Players will have to wait 50 seconds before switching to a new team.
```
---
---
### getentity
	getentity(integer entnum)
Get entity whose entity number is entnum.

For SH/BT, this is equivalent to `getentbyentnum`.

For player entites, `clientnum` is the same as `entnum`.

Entities with numbers from `0` to `sv_maxclients-1` are reserved for all players.

Entities with numbers from `0` to `sv_privateClients-1` are reserved for private password players, other players get an entity num from  `sv_privateClients` to `sv_maxclients-1`

For example, if `sv_privateClients` is `3` and the first non private player connects, his entity number will be 3, the next non private player will have entity number of 4, and so on.

If a private player connects, he will start at entity number 0.


Example:
```
local.player = getentity 1

```
Result:
```
Player entity with entity num 1
```
---
---
### netname
	netname(Entity player)
Return player's name.



Example:
```
local.result = netname local.player

```
Result:
```
Player's name as string
```
---
---
### getip
	getip(Entity player)
Return player's ip:port as string.

Example:
```
local.result = getip local.player

```
Result:
```
Player's getip as string
```
---
---
### getping
	getping(Entity player)
Return player's ping as integer.

Will return -1 on error.

Example:
```
local.result = getping local.player

```
Result:
```
Player's getping as integer
```
---
---
### getclientnum
	getclientnum(Entity player)
Return player's client number as integer.

Will return -1 on error.

Example:
```
local.result = getclientnum local.player

```
Result:
```
Player's client number as integer
```
---
---
### traced
	traced(vector start, vector end, [integer pass_entity = -1], [vector mins = (0 0 0)], [vector maxs = (0 0 0)], [integer mask = 0])

Perform a ray box trace from start to end, ignoring pass_enty if given. Box size along the line (relative) is defined by providing optional mins and maxs.

Example:
```
local.trace = traced local.start local.end
//or
local.trace = traced local.start local.end local.pass_entities local.mins
//or
local.trace = traced local.start local.end local.pass_entities local.mins local.maxs local.mask
```
Result:
```
Array holding detailed information about trace:

local.trace["allSolid"] 	//Integer : it tells whether the entire trace was inside of a solid object
local.trace["startSolid"] 	//Integer : it tells wheter trace started in solid object
local.trace["fraction"] 	//Float : how much along the trace have we walked, 1.0 means we reached end, 0.5 means halfway between start and end.
local.trace["endPos"] 		//Vector : position where trace finished because it may finish before it reaches end point specified by caller when it hits object with specified mask before it reaches end point
local.trace["surfaceFlags"] //Integer: see below
local.trace["shaderNum"] 	//Integer: number of the surface's shader that was hit
local.trace["contents"] 	//Integer: see below
local.trace["entityNum"] 	//Integer : entity number that was hit
local.trace["location"] 	//Integer: if entity is sentient, location in it's body, or LOCATION_MISS if trace missed or LOCATION_GENERAL if trace hit. See below for location values.
local.trace["entity"] 		//Entity : entity that was hit by the trace
```
Surface Flags:
```
SURF_NODAMAGE: 	     1
SURF_SLICK: 		 2
SURF_SKY: 			 4
SURF_LADDER: 		 8
SURF_NOIMPACT: 	     16
SURF_NOMARKS: 		 32
SURF_CASTSHADOW: 	 64
SURF_NODRAW: 		 128
SURF_NOLIGHTMAP: 	 256
SURF_ALPHASHADOW: 	 512
SURF_NOSTEPS: 		 1024
SURF_NONSOLID: 	     2048
SURF_OVERBRIGHT: 	 4096
SURF_PAPER: 		 8192
SURF_WOOD: 		     16384
SURF_METAL: 		 32768
SURF_ROCK: 		     65536
SURF_DIRT: 		     131072
SURF_GRILL: 		 262144
SURF_GRASS: 		 524288
SURF_MUD: 			 1048576
SURF_PUDDLE: 		 2097152
SURF_GLASS: 		 4194304
SURF_GRAVEL: 		 8388608
SURF_SAND: 		     16777216
SURF_FOLIAGE: 		 33554432
SURF_SNOW: 		     67108864
SURF_CARPET: 		 134217728
SURF_BACKSIDE: 	     268435456
SURF_NODLIGHT: 	     536870912
SURF_HINT: 		     1073741824
```
Content Flags:
```
CONTENTS_SOLID: 			1
CONTENTS_LADDER: 			2
CONTENTS_LAVA: 				8
CONTENTS_SLIME: 			16
CONTENTS_WATER: 			32
CONTENTS_FOG: 				64
CONTENTS_NOTTEAM			128
CONTENTS_NOTTEAM			256
CONTENTS_BBOX: 				256
CONTENTS_NOBOTCLIP: 		512
CONTENTS_FENCE: 			8192
CONTENTS_AREAPORTAL: 		32768
CONTENTS_PLAYERCLIP: 		65536
CONTENTS_MONSTERCLIP: 		131072
CONTENTS_WEAPONCLIP: 		262144
CONTENTS_VEHICLECLIP: 		524288
CONTENTS_SHOOTONLY: 		1048576
CONTENTS_OBSCURING: 		2097152
CONTENTS_ORIGIN: 			16777216
CONTENTS_BODY: 				33554432
CONTENTS_CORPSE: 			67108864
CONTENTS_DETAIL: 			134217728
CONTENTS_STRUCTURAL: 		268435456
CONTENTS_TRANSLUCENT: 		536870912
CONTENTS_WINDOW: 			1073741824
CONTENTS_NODROP: 			2147483648
```

Location Values:
```
LOCATION_MISS				-2
LOCATION_GENERAL			-1
LOCATION_HEAD				0
LOCATION_HELMET				1
LOCATION_NECK				2
LOCATION_TORSO_UPPER		3
LOCATION_TORSO_MID			4
LOCATION_TORSO_LOWER		5
LOCATION_PELVIS				6
LOCATION_R_ARM_UPPER		7
LOCATION_L_ARM_UPPER		8
LOCATION_R_LEG_UPPER		9
LOCATION_L_LEG_UPPER		10
LOCATION_R_ARM_LOWER		11
LOCATION_L_ARM_LOWER		12
LOCATION_R_LEG_LOWER		13
LOCATION_L_LEG_LOWER		14
LOCATION_R_HAND				15
LOCATION_L_HAND				16
LOCATION_R_FOOT				17
LOCATION_L_FOOT				18
```
---
---
### ihuddraw_align
	ihuddraw_align(entity player, integer hud_index, string h_align, string v_align)
Sets the alignment of a huddraw element for individual player.

```
h_align = "left", "center", "right"
v_align = "bottom", "center", "top"
index = index of huddraw element to be set
player = entity of player that will have his huddraw element set
```


Example:
```
ihuddraw_align $player[1] 15 right top
```
---
---
### ihuddraw_alpha
	ihuddraw_align(entity player, integer hud_index, float alpha)
Sets the alpha of a huddraw element for individual player.

```
index = index of huddraw element to be set
player = entity of player that will have his huddraw element set
```

Example:
```
ihuddraw_alpha $player[1] 15 0.5
```
---
---
### ihuddraw_color
	ihuddraw_align(entity player, integer hud_index, float red, float green, float blue)
Sets the color for a huddraw element for individual player.

```
index = index of huddraw element to be set
player = entity of player that will have his huddraw element set
```

Example:
```
ihuddraw_color $player[1] 15 1 1 1
```
---
---
### ihuddraw_font
	ihuddraw_font(entity player, integer hud_index, string font)
Sets the font for a huddraw element for individual player.

```
index = index of huddraw element to be set
player = entity of player that will have his huddraw element set
```

Example:
```
ihuddraw_font $player[1] 15 "verdana-14"
```
---
---
### ihuddraw_rect
	ihuddraw_rect(entity player, integer hud_index, int x, int y, int width, int height)
Sets the size and position for a huddraw element for individual player.

```
index = index of huddraw element to be set
player = entity of player that will have his huddraw element set
```

Example:
```
ihuddraw_rect $player[1] 15 -140 65 0 0
```
---
---
### ihuddraw_shader
	ihuddraw_shader(entity player, integer hud_index, string shader)
Sets the shadeer for a huddraw element for individual player.

```
index = index of huddraw element to be set
player = entity of player that will have his huddraw element set
```

Example:
```
ihuddraw_shader $player[1] 15 "textures/hud/axis"
```
---
---
### ihuddraw_string
	ihuddraw_string(entity player, integer hud_index, string shader)
Sets the string for a huddraw element for individual player.

```
index = index of huddraw element to be set
player = entity of player that will have his huddraw element set
```

Example:
```
ihuddraw_string $player[1] 15 "Example hud string"
```
---
---
### ihuddraw_virtualsize
	ihuddraw_string(entity player, integer hud_index, integer virtual)
Sets if the huddraw element (for individual player) should use virutal screen resolution for positioning and size.
```
index = index of huddraw element to be set
player = entity of player that will have his huddraw element set
```

Example:
```
//enable
ihuddraw_virtualsize $player[1] 15 1
//or disable
ihuddraw_virtualsize $player[1] 15 0
```
---
---
### registerev
	registerev(string eventname, string/array scriptname)

Registers script callback handler for given event type.

**NOTE:** Event behaviour is slightly different from reborn and more events are added. See [eventsystem.md](eventsystem.md) for more info.
Example:
```
local.result = registerev "connected" global/eventhandlers.scr::connected

```
Result:
```
When given event type will occur, EventSystem engine will execute given script.

local.result can have one of the following values:

0 = Registering event callback handler was successful
1 = Event callback handler is already registered for given event
3 = Invalid script passed
```
---
---
### unregisterev
	unregisterev(string eventname)

Un-registers script callback handler for given event type.

**NOTE:** Event behaviour is slightly different from reborn and more events are added. See [eventsystem.md](eventsystem.md) for more info.
Example:
```
local.result = unregisterev "connected"

```
Result:
```
local.result can have one of the following values:

0 = Un-registering event callback handler was successful
1 = Event callback handler is already not registered for given event
```
---
## ScriptThread File System Functions

Most of the following functions map to their respective cstdio library counterparts, please review [C standard Input/Output library](#c-standard-inputoutput-library) for more info.

---
### fopen
	fopen(string file_path, string access_type, [integer share_flags=0])
Opens file with file_path using access_type.

share_flags specify whether to allow other processes and threads to open your file for reading/writing.
This command increments value of [sv_scriptfiles](cvars.md#sv_scriptfiles) by one.
Maximum supported concurrent open files count is 32.

Example:
```
local.result = fopen "test.txt" "r+"
//or
local.result = fopen "main/test.txt" "r+" 1
```
Result:
```
Returns file handle on open success, 0 otherwise.
```

Share Flags:
```
0 - No sharing
1 - share read : allow other processes to read from file, denies write
2 - share write : allow other processes to write to file, denies read
3 - share read and write combined
```
---
---
### fclose
	fclose(integer file_handle)
Closes file.
This command decrements value of [sv_scriptfiles](cvars.md#sv_scriptfiles) by one.

Example:
```
local.result = fclose local.file


```
Result:
```
Returns 0 on success. In case of failure, result is nonzero.
```
---
---
### feof
	feof(integer file_handle)
Check if end of file is reached.

Example:
```
local.result = feof local.file
```
Result:
```
Returns nonzero if EOF is reached, returns 0 otherwise.
```
---
---
### fseek
	fseek(integer file_handle, integer offset, integer origin_type)
Change position indicator in file to offset from origin with origin_type.

Origin values:
```
0 : SEEK_SET, file beginning
1 : SEEK_CUR, current position in file
2 : SEEK_END, end of file
```

Example:
```
local.result = fseek local.file 5 0
```
Result:
```
Returns 0 on success, nonzero on failure.
```
---
---
### ftell
	ftell(integer file_handle)
Return the current position indicator in the file.

Example:
```
local.result = ftell local.file
```
Result:
```
Returns -1 on failure, current position indicator (0 or more) on success.
```
---
---
### fgetc
	fgetc(integer file_handle)
Read 1 character from file and advance the position indicator.

If -1 is returned, either [ferror](#ferror) or [feof](#feof) will be set.

Example:
```
local.result = fgetc local.file
```
Result:
```
Returns character cast to integer on success, or -1 in case of failure or reaching EOF.
```
---
---
### fputc
	fputc(integer file_handle, string character)
Write one character to file at current position and advance position indicator.

If -1 is returned, [ferror](#ferror) will be set.

Example:
```
local.result = fputc local.file "a"
```
Result:
```
Returns character cast to integer on success, or -1 in case of failure.
```
---
---
### fgets
	fgets(integer file_handle, integer maxbuffsize)
Read a string from file at current position.

maxbuffsize is the maximum size of the internal buffer used to read the line.

String stops at newline, or when maxbuffsize-1 characters are read, or when end of file is reached.

If error is returned, either [ferror](#ferror) or [feof](#feof) will be set.

Example:
```
local.result = fgets local.file 256
```
Result:
```
Returns string containing full line on success, -1 on memory allocation error, and 0 on other erors.
```
---
---
### fputs
	fputs(integer file_handle, string text)
Write string text to file.

If error is returned, either [ferror](#ferror) will be set.

Example:
```
local.result = fputs local.file "my string"
```
Result:
```
Returns nonegative integer on success, -1 on error.
```
---
---
### ferror
	ferror(integer file_handle, string text)
Returns error indicator set on file.

Example:
```
local.result = ferror local.file
```
Result:
```
Returns nonzero integer if error indicator is set, and if no errors, returns 0.
```
---
---
### fflush
	fflush(integer file_handle)
Flushes given file. Writes all unsaved data from stream buffer to stream.

Example:
```
local.result = fflush local.file
```
Result:
```
Returns -1 on error, and if no errors, returns 0.
```
---
---
### fexists
	fexists(string filepath)
Check if given file exists.

Example:
```
local.result = fexists "test.txt"
```
Result:
```
Returns 1 if file exists, and 0 if not.
```
---
---
### freadall
	freadall(integer filehandle)
Reads whole file into a string at once.

File **does NOT need** to be opened in binary mode (rb, rb+).


Example:
```
local.content = freadall local.file

```
Result:
```
Function returns file content as string.
```
---
---
### fsaveall
	fsaveall(integer filehandle, string text)
Writes string to file.

File **does NOT need** to be opened in binary mode (wb, wb+).


Example:
```
local.content = fsaveall local.file local.test

```
Result:
```
Function returns length of written content as integer.
```
---
---
### fremove
	fremove(string filepath)
Remove fille of given path.



Example:
```
local.content = fremove "test.txt"

```
Result:
```
Returns 0 on success, nonzero on error.
```
---
---
### frename
	frename(string oldfilepath, string newfilepath)
Renames file from old path to new path.

You can use this function to move files.

Example:
```
local.content = frename "test.txt" "test2.txt"

```
Result:
```
Returns 0 on success, nonzero on error.
```
---
---
### fcopy
	fcopy(string filepath, string copypath)
Creates a copy of file `filepath` into `copypath`.


Example:
```
local.result = fcopy local.filepath local.copypath

```
Result:
```
-1 = error occured
0 = copy operation succeeded
```
---
---
### freadpak
	freadpak(string filepakpath)
Reads content of file inside pk3 with path `filepakpath` as string.


Example:
```
local.result = freadpak "global/DMprecache.scr"

```
Result:
```
string content of pak file, or -1 on failure.
```
---
---
### flist
	flist(string path, string extension, integer recursive)
Scan all files in `path` and return the list of file/folder names as a 0-indexed array array.

`extension` is used to specify file extensions, or you can use it as a suffix filter for files.

`recursive` specifies whether the function should also recursively scan subdirectories. To enable, set it to 1. To disable set it to 0.

This function also lists files inside pk3s.

Example:
```
local.result = flist "global/" ".scr" 0
//or
local.result = flist "global/" ".scr" 1


```
Result:
```
Array containing list of file/folder names.
```
---
---
### fnewdir
	fnewdir(string dirpath)
Creates new empty directory with path `dirpath`.


Example:
```
local.result = fnewdir "main/mynewdir"

```
Result:
```
0 on success or if directory already exists.
nonzero on failure or if one of dirpath parent directories does not exist.
```
---
---
### fremovedir
	fremovedir(string dirpath)
Removes **empty** directory with path `dirpath`.


Example:
```
local.result = fremovedir "main/mynewdir"

```
Result:
```
0 on success or  if directory does not exist.
nonzero on failure or if directory is not emtpy.
```
---
## ScriptThread API Functions
### create_api_request
	create_api_request(string url, string method, string/array scriptname, var userdata)
Creates an http request from the server to url/method combination.

Calls script after request is done.

Url may contain query string for GET requests.

Current allowed values for `method` are `"get"` and `"post"`.

For GET requests, user_data is simply passed to the handle script.

For POST requests, user_data is json-parsed (via [json_stringify](scriptfuncs.md#json_stringify)) and used as the HTTP POST request body. It's also passed to the handle script.

See [API Client Documentation](api_client.md) for client api configuration settings and more info.

Example:
```
local.result = create_api_request "http://jsonplaceholder.typicode.com/todos/1" "get" global/api.scr::request_handler "my own data"
```
Result:
```
Creates an http request from the server to url/method combination.

local.result will have one of the following values:

0 = Request queued successfully
1 = Invalid arguments
2 = Client api is not running
3 = Client api error

```
---
### register_api_route
	register_api_route(string uri, string method, string/array scriptname)
Registers callback handler for give api route/method.

Current allowed values for `method` are `"get"` and `"post"`.

See [API Server Documentation](api_server.md) for server api configuration settings and more info.

Example:
```
local.result = register_api_route "/" "get" global/api.scr::get_handler
```
Result:
```
When specified uri/method route is called/requested, api will call the specified callback  script.
The api response is the value returned by script.

local.result will have one of the following values:

0 = Route registered successfully
1 = Route already registered
2 = Invalid arguments
3 = Server api is not running
4 = Server api error

```
---
### unregister_api_route
	unregister_api_route(string uri, string method)
Un-registers callback handler for give api route/method.

Current allowed values for `method` are `"get"` and `"post"`.

See [API Server Documentation](api_server.md) for server api configuration settings and more info.

Example:
```
local.result = unregister_api_route "/" "get"
```
Result:
```
Removes api callback handler for specified uri/method route.

local.result will have one of the following values:

0 = Route unregistered successfully
1 = Route is already not registered
2 = Invalid arguments
3 = Server api is not running
4 = Server api error

```
---
## Player Miscellaneous Functions
---
### userinfo
	userinfo(void)
Return player's userinfo string.


Example:
```
local.result = local.player.userinfo

```
Result:
```
Player's userinfo string
```
---
### getkills
	getkills(void)
Return player's kill count.


Example:
```
local.result = local.player getkills

```
Result:
```
Player's kill count as integer
```
---
---
### getdeaths
	getdeaths(void)
Return player's death count.


Example:
```
local.result = local.player getdeaths

```
Result:
```
Player's death count as integer
```
---
---
### .secfireheld
	.secfireheld
Return player's secondary fire button status.


Example:
```
local.result = local.player.secfireheld

```
Result:
```
Returns 1 if player is holding secondary fire button (usually right click), 0 otherwise.
```
---
---
### .runheld
	.runheld
Return player's run button status.


Example:
```
local.result = local.player.runheld

```
Result:
```
Returns 1 if player is holding run (even if player is not moving), 0 otherwise (when left shift is held/player is walking).
```
---
---
### .leanleftheld
	.leanleftheld
Return player's lean left button status.


Example:
```
local.result = local.player.leanleftheld

```
Result:
```
Returns 1 if player is holding lean left button (Z), 0 otherwise.
```
---
---
---
### .leanrightheld
	.leanrightheld
Return player's lean right button status.


Example:
```
local.result = local.player.leanrightheld

```
Result:
```
Returns 1 if player is holding lean right button (C), 0 otherwise.
```
---
---
### .inventory
	.inventory
Return player's inventory as array.


Example:
```
local.result = local.player.inventory

```
Result:
```
Returns array of entites in the inventory (usually Weapon and InventoryItem).
```
---
---
### getactiveweap
	getactiveweap(integer hand_id)
Return player's active weapon from hand_id.


> **Note:** Maximum allowed hand index is 1.

Example:
```
local.result = local.player getactiveweap 0


```
Result:
```
Returns weapon entity.
```
---
---
### getconnstate
	getconnstate(void)
Return player's connection state.

Example:
```
local.result = local.player getconnstate


```
Result:
```
Returns integer value:
0 = CS_FREE - given player slot is free
1 = CS_ZOMBIE - given player slot is in zombie state (his data is still kept after he disconnected or lost connection)
2 = CS_CONNECTED - player has connected to server, but he's not yet in the game
3 = CS_PRIMED - player has passed through authorization checks and finished downloading any missing files
4 = CS_ACTIVE - player is in game and can start playing
```
---
---
### isadmin
	isadmin(void)
Returns whether player is logged in as admin.

Example:
```
local.result = local.player isadmin


```
Result:
```
Returns integer value: 1 if logged in as admin (using ad_login), 0 otherwise.
```
---
---
### adminrights
	.adminrights
Returns rights for player.

Example:
```
local.result = local.player.adminrights


```
Result:
```
Returns integer value: -1 if NOT logged in as admin (using ad_login).
If logged in, returns the integer value for admin rights, which is located inside admins.ini
```
---
---
### bindweap
	bindweap(Entity weapon)
> **NOTE:** This command is supported for AA only.

Binds weapon to player. Sets him as weapon owner.
2nd use of the command will unbind the weapon from player.

Example:
```
$player[1] bindweap local.weapon
local.weapon anim fire
$player[1] bindweap local.weapon

```
Result:
```
Sets player as weapon owner.
```

> **Warning:** This is sort of a hack&trick scripting command. It should only be used by experienced users and only like shown in the example - just before firing the weapon and just after, to unbind it from the player. Otherwise you can have errors, weapon model glued to player, or server crashes. It should be used only for some kind of remote turrets etc.
---

## References
### [C numerics library](https://cplusplus.com/reference/cmath)
### [C standard Input/Output library](https://cplusplus.com/reference/cstdio/)
### [Reborn Scripting Commands](http://www.x-null.net/wiki/index.php?title=Reborn_Scripting_Commands)