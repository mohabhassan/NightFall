

# NightFall Cvars Documentation
- [NightFall Cvars Documentation](#nightfall-cvars-documentation)
    - [sv\_crashrpt\_poll\_delay](#sv_crashrpt_poll_delay)
    - [sv\_crashrpt\_hang\_wait](#sv_crashrpt_hang_wait)
    - [sv\_api](#sv_api)
    - [sv\_api\_numthreads](#sv_api_numthreads)
    - [sv\_api\_ports](#sv_api_ports)
    - [sv\_api\_acl](#sv_api_acl)
    - [sv\_api\_client](#sv_api_client)
    - [sv\_update\_optionals](#sv_update_optionals)
    - [sv\_store](#sv_store)
    - [sv\_scriptfiles](#sv_scriptfiles)
    - [sv\_disablechat](#sv_disablechat)
    - [sv\_disabletaunt](#sv_disabletaunt)
    - [sv\_filterchat](#sv_filterchat)
    - [g\_badchatlimit](#g_badchatlimit)
    - [g\_teamswitchdelay](#g_teamswitchdelay)
    - [sv\_maxconnperip](#sv_maxconnperip)
    - [sv\_kickping](#sv_kickping)
    - [sv\_kickbadcmd](#sv_kickbadcmd)
    - [sv\_packetantiflood](#sv_packetantiflood)
    - [sv\_packetflooddelay](#sv_packetflooddelay)
  - [| Supported Games | MOHAA Only |](#-supported-games--mohaa-only-)
    - [sv\_remotetoolip](#sv_remotetoolip)
  - [| Supported Games | MOHAA Only |](#-supported-games--mohaa-only--1)
    - [sv\_antistwh](#sv_antistwh)
  - [| Supported Games | MOHAA Only |](#-supported-games--mohaa-only--2)
    - [sv\_rebornloader](#sv_rebornloader)
  - [| Remarks | Inside the script, self will be Director (ScriptMaster) |](#-remarks--inside-the-script-self-will-be-director-scriptmaster-)

### sv_crashrpt_poll_delay
| Name | sv_crashrpt_poll_delay |
|--|--|
| Description | Amount in seconds to regularly check if MOHAA/SH/BT is hung. |
| More Info | [sv_crashrpt_poll_delay](crash_reporter.md#sv_crashrpt_poll_delay)|


---
### sv_crashrpt_hang_wait
| Name | sv_crashrpt_hang_wait |
|--|--|
| Description | Amount in seconds to comfirm that MOHAA/SH/BT is hung. |
| More Info | [sv_crashrpt_hang_wait](crash_reporter.md#sv_crashrpt_hang_wait)|

---
### sv_api
| Name | sv_api |
|--|--|
| Description | Enable/disable API server. |
| More Info | [sv_api](api_server.md#sv_api)|

---
### sv_api_numthreads
| Name | sv_api_numthreads |
|--|--|
| Description | Set number of worker threads for API server. |
| More Info | [sv_api_numthreads](api_server.md#sv_api_numthreads)|

---
### sv_api_ports
| Name | sv_api_ports |
|--|--|
| Description | Set ports to listen to for API server. |
| More Info | [sv_api_ports](api_server.md#sv_api_ports)|

---
### sv_api_acl
| Name | sv_api_acl |
|--|--|
| Description | Set access control list for API server. |
| More Info | [sv_api_acl](api_server.md#sv_api_acl)|

---
### sv_api_client
| Name | sv_api_client |
|--|--|
| Description | Enable/disable API client. |
| More Info | [sv_api_client](api_client.md#sv_api_client)|

---
### sv_update_optionals
| Name | sv_update_optionals |
|--|--|
| Description | Enable/disable optional updates. |
| More Info | Update checks are carried at each map end.<br> Set to 1 to enable updating optional files, set to 0 to disable updating them. |

---
### sv_store
| Name | sv_store |
|--|--|
| Description | Specify database file name inside main for setproperty and getproperty functions. |
| Default value | `mainta/store.bin` or `maintt/store.bin` |

---
### sv_scriptfiles
| Name | sv_scriptfiles |
|--|--|
| Description | Specifies the amount of currently open script files (opened with [fopen](scriptallfuncs.md#fopen)). |
| Default value | `main/store.bin` or `mainta/store.bin` or `maintt/store.bin` |
| More Info | When you successfully open files with [fopen](scriptallfuncs.md#fopen), sv_scriptfiles increases.<br>When you close already opened files with [fclose](scriptallfuncs.md#fclose), sv_scriptfiles decreases. |

---
### sv_disablechat
| Name | sv_disablechat |
|--|--|
| Description | Specify whether or not to disable all chat. |
| Allowed values | 0 to enable chat, 1 to disable chat |

---
### sv_disabletaunt
| Name | sv_disabletaunt |
|--|--|
| Description | Specify whether or not to disable all taunts. |
| Allowed values | 0 to enable taunts, 1 to disable taunts |

---
### sv_filterchat
| Name | sv_filterchat |
|--|--|
| Description | Specify whether or not to enable chat filter. |
| Allowed values | 0 to disable chat filter, 1 to enable chat filter |

---
### g_badchatlimit
| Name | g_badchatlimit |
|--|--|
| Description | Specifies amount of times a use can enter bad chat filter words before being kicked. |
| Allowed values | 0 or more |

---
### g_teamswitchdelay
| Name | g_teamswitchdelay |
|--|--|
| Description | Specifies amount of seconds a player must wait before switching to a new team. |
| More Info | This is equivalent to script function [teamswitchdelay](scriptallfuncs.md#teamswitchdelay) and using the script function changes the value of this cvar silently. |
| Allowed values | any integer value |

---
### sv_maxconnperip
| Name | sv_maxconnperip |
|--|--|
| Description | Specifies the maximum number of users with the same ip allowed. |
| Allowed values | 0 or more |
| Remarks | use -1 to disable |

---
### sv_kickping
| Name | sv_kickping |
|--|--|
| Description | Specifies the maximum ping a user is allowed to exceed before getting kicked. |
| Allowed values | 1 or more |
| Remarks | user is warned 1 time before getting kicked |

---

---
### sv_kickbadcmd
| Name | sv_kickbadcmd |
|--|--|
| Description | Specifies whether players who enter bad commands should be kicked. |
| Allowed values | 0 or 1 |
| Remarks | when someone types a bad command that is used for crashing the server, they will be kicked if the cvar is non-zero |
| Supported Games | MOHAA Only |

---

---
### sv_packetantiflood
| Name | sv_packetantiflood |
|--|--|
| Description | Enable/disable packet anti-flood system |
| Allowed values | 0 or 1 |
| Supported Games | MOHAA Only |

---

---
### sv_packetflooddelay
| Name | sv_packetflooddelay |
|--|--|
| Description | Specify packet flood delay in milliseconds. |
| Allowed values | any non-negative number |
| Remarks | Specifies the minimum delay in milliseconds between two consecutive packets originating from the same IP to be processed. This is only for connectionless packets (players that already joined the game won't be affected). |
| Supported Games | MOHAA Only |
---

---
### sv_remotetoolip
| Name | sv_remotetoolip |
|--|--|
| Description | Specify IP for whitelisted remote tool IP. |
| Allowed values | any valid IP address |
| Remarks | This IP will not be affected by anti-flood system. |
| Supported Games | MOHAA Only |
---

---
### sv_antistwh
| Name | sv_antistwh |
|--|--|
| Description | Enable/Disable anti-STWH. |
| Allowed values | 0 or 1 |
| Remarks | Enables/Disables anti-Shoot Through Walls Hack(STWH) system. |
| Supported Games | MOHAA Only |
---

---
### sv_rebornloader
| Name | sv_rebornloader |
|--|--|
| Description | Specifies script that will be loaded at the start of the map. |
| Allowed values | script path |
| Remarks | Inside the script, self will be Director (ScriptMaster) |
---