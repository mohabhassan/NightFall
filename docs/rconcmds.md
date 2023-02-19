

# NightFall Rcon Commands Documentation
### kickr
| Name | kickr |
|--|--|
| Arguments | player_name reason |
| Description | Kick player name with reason |
| Example | `kickr RyBack "Abusing admins."` or `kickr RyBack "Noob"` |
---
### clientkickr
| Name | clientkickr |
|--|--|
| Arguments | player_num reason |
| Description | Kick player client num with reason |
| Example | `clientkickr 2 "Abusing admins."` or `clientkickr 2 "Noob"` |
---
### banip
| Name | banip |
|--|--|
| Arguments | ip |
| Description | Ban specified ip. Star mask is supported. |
| Example | `banip 192.168.*.*` or `banip 192.168.1.1` |
---
### banipr
| Name | banipr |
|--|--|
| Arguments | ip reason |
| Description | Ban specified ip with reason. |
| Example | `banip 192.168.*.*` or `banip 192.168.1.1` |
---
### banid
| Name | banid |
|--|--|
| Arguments | clientnum |
| Description | Ban specified clientnum. |
| Example | `banid 1` |
---
### banidr
| Name | banidr |
|--|--|
| Arguments | clientnum reason |
| Description | Ban specified clientnum with reason. |
| Example | `banidr 2 "Abusing admins."` or `banidr 2 "Noob"` |
---
### unbanip
| Name | unbanip |
|--|--|
| Arguments | ip |
| Description | Un-ban specified ip. Star mask is supported. |
| Example | `unbanip 192.168.*.*` or `unbanip 192.168.1.1` |
---
### listips
| Name | listips |
|--|--|
| Arguments | pagenum |
| Description | List ips in page number, page number starts from 1. |
| Example | `listips 5` |
---
### banname
| Name | banname |
|--|--|
| Arguments | name [any=0] |
| Description | Bans full name, to ban partial name, set any to 1 |
| Example | `banname ass` to ban full name "ass" or `banname ass 1` to ban any names that contain "ass" like "assasin" |
---
### unbanname
| Name | unbanname |
|--|--|
| Arguments | name |
| Description | Un-bans name. |
| Example | `unbanname ass` |
---
### listnames
| Name | listnames |
|--|--|
| Arguments | pagenum |
| Description |  List banned names in page number, page number starts from 1. |
| Example | `listnames 6` |
---
### protname
| Name | protname |
|--|--|
| Arguments | name password |
| Description |  Protect specified name with password. |
| Example | `protname RyBack testpassword` or `protname "It's Me, Mario" "Mama Mia"` |
---
### unprotname
| Name | uprotname |
|--|--|
| Arguments | name |
| Description |  Un-protect specified name. |
| Example | `unprotname RyBack` or `unprotname "It's Me, Mario"` |
---
### listprotnames
| Name | listprotnames |
|--|--|
| Arguments | pagenum |
| Description |  List protected names in page number, page number starts from 1. |
| Example | `listprotnames 9` |
---
### chatfilteradd
| Name | chatfilteradd |
|--|--|
| Arguments | word |
| Description |  Ban specified word from chat. |
| Example | `chatfilteradd fuck` |
---
### chatfilterremove
| Name | chatfilterremove |
|--|--|
| Arguments | word |
| Description |  Un-ban specified word from chat. |
| Example | `chatfilterremove fuck` |
---
### listchatfilter
| Name | listchatfilter |
|--|--|
| Arguments | pagenum |
| Description |  List banned chat words in page number, page number starts from 1. |
| Example | `listchatfilter 18` |
---
### dischat
| Name | dischat |
|--|--|
| Arguments | clientnum |
| Description |  Disable chat for specified client number. |
| Example | `dischat 3` |
---
### distaunt
| Name | distaunt |
|--|--|
| Arguments | clientnum |
| Description |  Disable taunts for specified client number. |
| Example | `distaunt 3` |
---
### sayp
| Name | sayp |
|--|--|
| Arguments | clientnum message |
| Description |  Say private message as console to specified client number. |
| Example | `sayp 3 "Hello, Damn you!"` |
---
### listadmins
| Name | listadmins |
|--|--|
| Arguments | none |
| Description |  List currently logged in admins. |
| Example | `listadmins` |
---
### patchver
| Name | patchver |
|--|--|
| Arguments | none |
| Description |  Print current patch version. |
| Example | `patchver` |
---
