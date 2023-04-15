

# NightFall Cvars Documentation

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
### sv_update
| Name | sv_update |
|--|--|
| Description | Enable/disable auto updates. |
| More Info | Update checks are carried at each map end.<br> Set to 1 to enable updates, set to 0 to disable updates. |
---
### sv_store
| Name | sv_store |
|--|--|
| Description | Specify database file name inside main for setproperty and getproperty functions. |
| Default value | `mainta/store.bin` or `maintt/store.bin` |
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
