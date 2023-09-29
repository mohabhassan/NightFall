

# NightFall Script Event System Documentation

The Script Event System is used to extend scripting capabilities and decrease limitations.

It is extremely similar to [Reborn Events System](http://www.x-null.net/wiki/index.php?title=Reborn_Events_System).

See [registerev](scriptfuncs.md#registerev) and [unregisterev](scriptfuncs.md#unregisterev).

- [NightFall Script Event System Documentation](#nightfall-script-event-system-documentation)
	- [New NightFall events](#new-nightfall-events)
		- [dmmessage](#dmmessage)
	- [Slightly modified Reborn events](#slightly-modified-reborn-events)
		- [damage](#damage)
		- [keypress](#keypress)
	- [Original Reborn events](#original-reborn-events)
		- [servercommand](#servercommand)
		- [connected](#connected)
		- [disconnected](#disconnected)
		- [kill](#kill)
		- [spawn](#spawn)
		- [intermission](#intermission)
	- [Appendix](#appendix)
		- [Damage Flags Values](#damage-flags-values)
		- [Means Of Death Values](#means-of-death-values)
		- [Location Values](#location-values)

## New NightFall events
### dmmessage
| Name | dmmessage |
|--|--|
| Description | Chat message event, occurs when player sends any chat message or taunt. |
| Arguments | `local.player` Player sending chat message/taunt.<br><br> `local.type` message type.<br>  -1 means teamchat (`sayteam`).<br>  0 means normal chat (`say`).<br>  other numbers are private client numbers (`sayprivate` or `sayp`).<br><br>`local.text` an array of message text, it is original message split by spaces. |
| Return Value | 1 to let the message pass, 0 to deny message. |

**Example usage:**
```
local.result = registerev "dmmessage" tests/reborn_events.scr::dmmessage


dmmessage local.player local.type local.text:
	conprintf ( "player " + local.player.netname + " sent message: \"")
	for(local.i = 0; local.i < local.text.size; local.i++)
	{
		conprintf (local.text[local.i] + " ")
	}
	conprintf ("\"	of type: \n" + local.type)
	iprintln success
end 0
```

If player types in console `say Hello I am noob` arguments will be as follows:

```
local.type = 0

local.text.size = 4
local.text[0] = "Hello"
local.text[1] = "I"
local.text[2] = "am"
local.text[3] = "noob"
```

If player types in console `sayteam Hello team, I am noob` arguments will be as follows:

```
local.type = -1

local.text.size = 5
local.text[0] = "Hello"
local.text[1] = "team,"
local.text[2] = "I"
local.text[3] = "am"
local.text[4] = "noob"
```

If player types in console `sayp 5 Hello dude, I am noob` or `private 5 Hello dude, I am noob` arguments will be as follows:

```
local.type = 5

local.text.size = 5
local.text[0] = "Hello"
local.text[1] = "dude,"
local.text[2] = "I"
local.text[3] = "am"
local.text[4] = "noob"
```

**Important Note:** Script callback must not contain long/time consuming operations or `wait` or `waitframe`.  NightFall will error if script does, and message will be allowed.

---
## Slightly modified Reborn events

These events have the same behavior as reborn but with some non-breaking changes to arguments and/or specific use cases.

Changes are highlighted in notes at the end of each event's documentation.

### damage
| Name | damage |
|--|--|
| Description | Damage event, occurs when any entity is damaged. |
| Arguments | `local.attacker` - attacker entity <br>`local.inflictor` - inflictor entity, entity that deals damage, isn't always player or actor entity. It can be a weapon entity or world entity<br>`local.damage` - float damage, damage amount<br>`local.position` - vector position<br>`local.direction` - vector direction<br>`local.normal` - vector normal<br>`local.knockback` - int knockback value<br>`local.damageflags` - int damageflags<br>`local.meansofdeath` - int meansofdeath<br>`local.location` - int location id<br>`local.entity` - entity that gets damage, often a player but can be any other damageable entity<br> |

**Example usage:**
```
local.result = registerev "damage" tests/reborn_events.scr::damage


damage local.attacker local.inflictor local.damage local.position local.direction local.normal local.knockback local.damageflags local.meansofdeath local.location local.entity:

	iprintln ("==========DAMAGED==========")
	iprintln ("Attacker: " + local.attacker)
	iprintln ("Inflictor: " + local.inflictor)
	iprintln ("Damage: " + local.damage)
	iprintln ("Position: " + local.position)
	iprintln ("Direction: " + local.direction)
	iprintln ("Normal: " + local.normal)
	iprintln ("Knockback: " + local.knockback)
	iprintln ("Damageflags: " + local.damageflags)
	iprintln ("MeansofDeath: " + local.meansofdeath)
	iprintln ("Location: " + local.location)
	iprintln ("Entity: " + local.entity)
	iprintln ("==========================")


end
```
[Damage Flags Values](#damage-flags-values)

[Means Of Death Values](#means-of-death-values)

[Location Values](#location-values)

Differences compared to reborn:

**Important Note:** If inflictor entity was NULL, it's considered world.

**Important Note:** If attacker entity was NULL, it's considered world.

**Important Note:** First argument is attacker, not target.


---
### keypress
| Name | keypress |
|--|--|
| Description | Keypress event, occurs player types keyp #keyid in console. |
| Arguments | `local.player` - Player entity that issued event<br>`local.key` - integer specifying key id  |


**Example usage:**
```
local.result= registerev "keypress" tests/reborn_events.scr::key_press


key_press local.player local.key:
	local.player iprint ("Key Pressed: " + local.key)
end
```

**Important Note:** Try to avoid using key id 0 as it's used as an error indicator.

---
## Original Reborn events

These events are made to match the behavior of original reborn events.

---
### servercommand
| Name | servercommand |
|--|--|
| Description | Server command event, occurs player types `scmd cmd args` in console. |
| Arguments | `local.player` - Player entity that issued event<br>`local.command` - string specifying command<br> `local.args` string containing all the command arguments space-separated as a single string  |


**Example usage:**
```
local.result= registerev "servercommand" tests/reborn_events.scr::scmd


scmd local.player local.command local.args:
	local.player iprint ("Command Typed: " + local.command)
	local.player iprint ("Command Arguments: " + local.args)
end
```
If player types in console `scmd myscmd My special arguments` arguments will be as follows:

```
local.args = "My special arguments"
local.command = "myscmd"
```
---
---
### connected
| Name | connected |
|--|--|
| Description | Connected event, occurs player enters the server. |
| Arguments | `local.player` - Player entity that issued event  |


**Example usage:**
```
local.result= registerev "connected" tests/reborn_events.scr::connected


connected local.player:
	local.player iprint "You have connected!"
end
```
---
---
### disconnected
| Name | disconnected |
|--|--|
| Description | Disconnected event, occurs player leaves the server. |
| Arguments | `local.player` - Player entity that issued event  |


**Example usage:**
```
local.result= registerev "disconnected" tests/reborn_events.scr::disconnected


disconnected local.player:
	local.name = netname local.player
	conprintf("Player " + local.name + " have disconnected from server!\n")
end
```
---
### kill
| Name | kill |
|--|--|
| Description | kill event, occurs when any player is killed. |
| Arguments | `local.attacker` - attacker entity<br>`local.damage` - integer damage <br>`local.inflictor` - inflictor entity, entity that deals damage, isn't always player or actor entity. It can be a weapon entity or world entity damage amount<br>`local.position` - vector position<br>`local.direction` - vector direction<br>`local.normal` - vector normal<br>`local.knockback` - int knockback value<br>`local.damageflags` - int damageflags<br>`local.meansofdeath` - int meansofdeath<br>`local.location` - int location id<br>`local.player` - Player entity that got killed<br> |

**Example usage:**
```
local.resullt = registerev "damage" tests/reborn_events.scr::damage




kill local.attacker local.damage local.inflictor local.position local.direction local.normal local.knockback local.damageflags local.meansofdeath local.location local.player:
	println ("==========KILL==========")
	println ("Attacker: " + local.attacker)
	println ("Damage: " + local.damage)
	println ("Inflictor: " + local.inflictor)
	println ("Position: " + local.position)
	println ("Direction: " + local.direction)
	println ("Normal: " + local.normal)
	println ("Knockback: " + local.knockback)
	println ("Damageflags: " + local.damageflags)
	println ("MeansofDeath: " + local.meansofdeath)
	println ("Location: " + local.location)
	println ("Player: " + local.player)
	println ("==========================")


end
```

[Damage Flags Values](#damage-flags-values)

[Means Of Death Values](#means-of-death-values)

[Location Values](#location-values)

**Important Note:** If inflictor entity was NULL, it's considered world.

**Important Note:** If attacker entity was NULL, it's considered world.

**Important Note:** Argument order is different than [damage](#damage) event. `local.damage` is the second argument, and it's integer here.


---
---
### spawn
| Name | spawn |
|--|--|
| Description | Spawn event, occurs when player spawns (usually right after joining a team and choosing weapons) and when player re-spawn (after death). |
| Arguments | `local.player` - Player entity that issued event  |


**Example usage:**
```
local.result = registerev "spawn" tests/reborn_events.scr::spawn


spawn local.player:
	local.player iprint "You have (re)spawned!"
end
```
**Important Note:** When map restart happens, this event doesn't get triggered, [intermission](#intermission) event gets triggered instead.

---
---
### intermission
| Name | intermission |
|--|--|
| Description | Intermission event, occurs on map change, map restart, and player intermission screen (end of map screen where players see the scoreboard). |
| Arguments | `local.type` - Type of intermission  |


**Example usage:**
```
local.result = registerev "intermission" tests/reborn_events.scr::intermission


intermission local.type:
	$player iprint "Intermission happened!"
end
```

Type Values:
```
0 = Player intermission screen (happens at the end of the map)
1 = Map change (happens after using commands: map, gamemap , but also right after player intermission screen)
2 = Map restart (happens after restart command and at the end of each round for roundbased/objective game types)
```

---

## Appendix
### Damage Flags Values
```
DAMAGE_NONE				0
DAMAGE_RADIUS			1	// damage was indirect
DAMAGE_NO_ARMOR			2	// armour does not protect from this damage
DAMAGE_ENERGY			4	// damage is from an energy based weapon
DAMAGE_NO_KNOCKBACK		8	// do not affect velocity, just view angles
DAMAGE_BULLET			16  // damage is from a bullet (used for ricochets)
DAMAGE_NO_PROTECTION	32  // armor, shields, invulnerability, and have no effect
DAMAGE_NO_SKILL			64  // damage is not affected by skill level
```
### Means Of Death Values
AA/SH/BT Values:
```
0 - none
1 - suicide
2 - crush
3 - crush_every_frame
4 - telefrag
5 - lava
6 - slime
7 - falling
8 - last_self_inflicted
9 - explosion
10 - explodewall
11 - electric
12 - electricwater
13 - thrownobject
14 - grenade
15 - beam
16 - rocket
17 - impact
18 - bullet
19 - fast_bullet
20 - vehicle
21 - fire
22 - flashbang
23 - on_fire
24 - gib
25 - impale
26 - bash
27 - shotgun
```
SH/BT only values:
```
28 - aagun
29 - landmine
```
### Location Values
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