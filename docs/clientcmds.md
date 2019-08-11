
# NightFall Client Admin Commands Documentation
### ad_login
| Name | ad_login |
|--|--|
| Arguments | username password |
| Description | Log in as admin with specified username and password. |
| Example | `ad_login RyBack MySuperPrivatPassword` or `ad_login RyBack "Noob Password"` |
---
### ad_logout
| Name | ad_logout |
|--|--|
| Arguments | none |
| Description | Log out as admin. |
| Example | `ad_logout` |
---
### ad_kick
| Name | ad_kick |
|--|--|
| Arguments | player_name |
| Description | Kick player name |
| Example | `ad_kick RyBack` or `ad_kick "RyBack Noob"` |
---
### ad_kickr
| Name | ad_kickr |
|--|--|
| Arguments | player_name reason |
| Description | Kick player name with reason |
| Example | `ad_kickr RyBack "Abusing admins."` or `ad_kickr RyBack "Noob"` |
---
### ad_clientkick
| Name | ad_clientkick |
|--|--|
| Arguments | player_num |
| Description | Kick player client num |
| Example | `ad_clientkickr 2` |
---
### ad_clientkickr
| Name | ad_clientkickr |
|--|--|
| Arguments | player_num reason |
| Description | Kick player client num with reason |
| Example | `ad_clientkickr 2 "Abusing admins."` or `ad_clientkickr 2 "Noob"` |
---
### ad_banip
| Name | ad_banip |
|--|--|
| Arguments | ip |
| Description | Ban specified ip. Star mask is supported. |
| Example | `ad_banip 192.168.*.*` or `ad_banip 192.168.1.1` |
---
### ad_banipr
| Name | ad_banipr |
|--|--|
| Arguments | ip reason |
| Description | Ban specified ip with reason. |
| Example | `ad_banip 192.168.*.*` or `ad_banip 192.168.1.1` |
---
### ad_banid
| Name | ad_banid |
|--|--|
| Arguments | clientnum |
| Description | Ban specified clientnum. |
| Example | `ad_banid 1` |
---
### ad_banidr
| Name | ad_banidr |
|--|--|
| Arguments | clientnum reason |
| Description | Ban specified clientnum with reason. |
| Example | `ad_banidr 2 "Abusing admins."` or `ad_banidr 2 "Noob"` |
---
### ad_unbanip
| Name | ad_unbanip |
|--|--|
| Arguments | ip |
| Description | Un-ban specified ip. Star mask is supported. |
| Example | `ad_unbanip 192.168.*.*` or `ad_unbanip 192.168.1.1` |
---
### ad_listips
| Name | ad_listips |
|--|--|
| Arguments | pagenum |
| Description | List ips in page number, page number starts from 1. |
| Example | `ad_listips 5` |
---
### ad_banname
| Name | ad_banname |
|--|--|
| Arguments | name [any=0] |
| Description | Bans full name, to ban partial name, set any to 1 |
| Example | `ad_banname ass` to ban full name "ass" or `ad_banname ass 1` to ban any names that contain "ass" like "assasin" |
---
### ad_unbanname
| Name | ad_unbanname |
|--|--|
| Arguments | name |
| Description | Un-bans name. |
| Example | `ad_unbanname ass` |
---
### ad_listnames
| Name | ad_listnames |
|--|--|
| Arguments | pagenum |
| Description |  List banned names in page number, page number starts from 1. |
| Example | `ad_listnames 6` |
---
### ad_protname
| Name | ad_protname |
|--|--|
| Arguments | name password |
| Description |  Protect specified name with password. |
| Example | `ad_protname RyBack testpassword` or `ad_protname "It's Me, Mario" "Mama Mia"` |
---
### ad_unprotname
| Name | ad_uprotname |
|--|--|
| Arguments | name |
| Description |  Un-protect specified name. |
| Example | `ad_unprotname RyBack` or `ad_unprotname "It's Me, Mario"` |
---
### ad_listprotnames
| Name | ad_listprotnames |
|--|--|
| Arguments | pagenum |
| Description |  List protected names in page number, page number starts from 1. |
| Example | `ad_listprotnames 9` |
---
### ad_chatfilteradd
| Name | ad_chatfilteradd |
|--|--|
| Arguments | word |
| Description |  Ban specified word from chat. |
| Example | `ad_chatfilteradd fuck` |
---
### ad_chatfilterremove
| Name | ad_chatfilterremove |
|--|--|
| Arguments | word |
| Description |  Un-ban specified word from chat. |
| Example | `ad_chatfilterremove fuck` |
---
### ad_listchatfilter
| Name | ad_listchatfilter |
|--|--|
| Arguments | pagenum |
| Description |  List banned chat words in page number, page number starts from 1. |
| Example | `ad_listchatfilter 18` |
---
### ad_dischat
| Name | ad_dischat |
|--|--|
| Arguments | clientnum |
| Description |  Disable chat for specified client number. |
| Example | `ad_dischat 3` |
---
### ad_distaunt
| Name | ad_distaunt |
|--|--|
| Arguments | clientnum |
| Description |  Disable taunts for specified client number. |
| Example | `ad_distaunt 3` |
---
### ad_say
| Name | ad_say |
|--|--|
| Arguments | message |
| Description |  Say message as console. |
| Example | `ad_say "Hello, Damn you!"` |
---
### ad_sayp
| Name | ad_sayp |
|--|--|
| Arguments | clientnum message |
| Description |  Say private message as console to specified client number. |
| Example | `ad_sayp 3 "Hello, Damn you!"` |
---
### ad_listadmins
| Name | ad_listadmins |
|--|--|
| Arguments | none |
| Description |  List currently logged in admins. |
| Example | `ad_listadmins` |
---
### ad_map
| Name | ad_map |
|--|--|
| Arguments | mapname |
| Description |  Load map specified by map name. |
| Example | `ad_map dm/mohdm2` |
---
### ad_restart
| Name | ad_restart |
|--|--|
| Arguments | none |
| Description |  Restart current map. |
| Example | `ad_restart` |
---
### ad_fraglimit
| Name | ad_fraglimit |
|--|--|
| Arguments | fraglimit |
| Description |  Set the frag limit. |
| Example | `ad_fraglimit 150` |
---
### ad_timelimit
| Name | ad_timelimit |
|--|--|
| Arguments | timelimit |
| Description |  Set the time limit in minutes. |
| Example | `ad_timelimit 60` |
---
### ad_gametype
| Name | ad_gametype |
|--|--|
| Arguments | gametype |
| Description |  Set the gametype. |
| Example | `ad_gametype 2` |
---
### ad_status
| Name | ad_status |
|--|--|
| Arguments | none |
| Description |  Print player status, similar to rcon status. |
| Example | `ad_status` |
---
