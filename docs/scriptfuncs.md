
## Scripting Functions Documentation

 - [New NightFall functions](#New-NightFall-functions)
 - [Slightly modified reborn functions](#Slightly-modified-reborn-unctions)
 - [Reborn original functions](#Reborn-original-functions)
---
## New NightFall functions

#### register_api_route
	register_api_route(string uri, string method, string/array scriptname)
Registers callback handler for give api route/method.
Current allowed values for `method` is `"get"`.
See [api_server.md](docs/api_server.md#configuration) for server api configuration settings.
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
## Slightly modified reborn functions
---

## Reborn original functions
---
