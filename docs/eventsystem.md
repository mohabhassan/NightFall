

# NightFall Script Event System Documentation

The Script Event System is used to extend scripting capabilities and decrease limitations.

It is extremely similar to [Reborn Events System](http://www.x-null.net/wiki/index.php?title=Reborn_Events_System).

See [registerev](scriptfuncs.md#registerev) and [unregisterev](scriptfuncs.md#unregisterev).

 - [New NightFall events](#New-NightFall-events)
 - [Slightly modified Reborn events](#Slightly-modified-Reborn-events)
 - [Reborn original events](#Reborn-original-events)

## New NightFall events
### dmmessage
| Name | dmmessage |
|--|--|
| Description | Chat message event, occurs when player sends any chat message or taunt. |
| Arguments | `local.player` Player sending chat message/taunt.<br><br> `local.type` message type.<br>  -1 means teamchat (`sayteam`).<br>  0 means normal chat (`say`).<br>  other numbers are private client numbers (`sayprivate` or `sayp`).<br><br>`local.text` an array of message text, it is original message splitted by spaces. |
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
loca.text[0] = "Hello"
loca.text[1] = "I"
loca.text[2] = "am"
loca.text[3] = "noob"
```

If player types in console `sayteam Hello team, I am noob` arguments will be as follows:

```
local.type = -1

local.text.size = 5
loca.text[0] = "Hello"
loca.text[1] = "team,"
loca.text[2] = "I"
loca.text[3] = "am"
loca.text[4] = "noob"
```

If player types in console `sayp 5 Hello dude, I am noob` or `private 5 Hello dude, I am noob` arguments will be as follows:

```
local.type = 5

local.text.size = 5
loca.text[0] = "Hello"
loca.text[1] = "dude,"
loca.text[2] = "I"
loca.text[3] = "am"
loca.text[4] = "noob"
```

**Important Note:** Script callback must not contain long/time consuming operations or `wait` or `waitframe`.  NightFall will error if script does, and message will be allowed.

---
## Slightly modified Reborn events
### damage
| Name | damage |
|--|--|
| Description | Damage event, occurs when any entity is damaged. |
| Arguments | `local.target` - target entity isn't always player or actor entity. It can be a weapon entity or world entity<br>`local.inflictor` - inflictor entity, entity that deals damage<br>`local.damage` - float damage, damage amount<br>`local.position` - vector position<br>`local.direction` - vector direction<br>`local.normal` - vector normal<br>`local.knockback` - int knockback value<br>`local.damageflags` - int damageflags<br>`local.meansofdeath` - int meansofdeath<br>`local.location` - int location id<br>`local.entity` - entity that get's damage, often a player but can be any oder damageable entity<br> |

**Example usage:**
```
local.resullt = registerev "damage" tests/reborn_events.scr::damage


damage local.target local.inflictor local.damage local.position local.direction local.normal local.knockback local.damageflags local.meansofdeath local.location local.entity:

	iprintln ("==========DAMAGED==========")
	iprintln ("Target: " + local.target)
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
**Important Note:** If inflictor entity was NULL, it's considered world.
**Important Note:** If attacker entity was NULL, it's considered world.

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
## Reborn original events

For the sake of not re-inventing the wheel, the rest of the events in NightFall are exactly identical to reborn ones.

Documentation for the original reborn events can be found [here](http://www.x-null.net/wiki/index.php?title=Reborn_Events_System).
