
# NightFall Filters Documentation

## IP Filter
| Name | IP Filter |
|--|--|
| Description | Responsible for IP address based bans. |
| File | `mainta/ipfilter.cfg` or `maintt/ipfilter.cfg` |
| Allowed values | An IP address. Masks are allowed. |
| Example | `192.168.1.1` or `192.168.*.*` |
| Behaviour | If a player with matching IP address connects, he is disallowed from joining the server. |
---
## Name Filter
| Name | Name Filter |
|--|--|
| Description | Responsible for name based bans. |
| File | `mainta/namefilter.cfg` or `maintt/namefilter.cfg` |
| Allowed values | An IP address. Masks are allowed. |
| Example | `ass` only matches name `ass`. Using `~any` allows matching inside name. `ass ~any` matches any name containing the word `ass`. |
| Behaviour | If a player with matching name connects, he is disallowed from joining the server. |
---
## Protected Name Filter
| Name | Protected Name Filter |
|--|--|
| Description | Responsible for password protecting names. |
| File | `mainta/protectednamefilter.cfg` or `maintt/protectednamefilter.cfg` |
| Allowed values | A protected name entry, consists of name, and password. |
| Example | `name=RyBack password=MyPrivateNamePassword` |
| Usage | To use the password, add this line to your unnamedsoldier.cfg:<br>`setu cl_namepass "MyPrivateNamePassword"` |
| Behaviour | If a player with matching protected name connects without password or with wrong password, he is disallowed from joining the server. |
---
## Chat Filter
| Name | Chat Filter |
|--|--|
| Description | Responsible for filtering chat messages. |
| File | `mainta/chatfilter.cfg` or `maintt/chatfilter.cfg` |
| Allowed values | A chat filter word. |
| Example | `ass` or `fuck` |
| Behaviour | If a player tries to send a message containing a banned word in chat filter, he is warned and message is not sent. If player exceed maximum allowed banned chat word attempts, he is kicked. This limit is specified in [g_badchatlimit](cvars.md#g_badchatlimit). |
---
