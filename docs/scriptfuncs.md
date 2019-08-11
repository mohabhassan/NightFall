
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

See [api_server.md](docs/api_server.md) for server api configuration settings and more info.

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
#### unregister_api_route
	unregister_api_route(string uri, string method)
Un-registers callback handler for give api route/method.

Current allowed values for `method` is `"get"`.

See [api_server.md](docs/api_server.md) for server api configuration settings and more info.

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
#### create_api_request
	create_api_request(string url, string method, string/array scriptname, var userdata)
Creates an http request from the server to url/method combination.

Calls script after request is done.

Url may contain query string.

Current allowed values for `method` is `"get"`.

See [api_client.md](docs/api_client.md) for client api configuration settings and more info.

Example:
```
local.result = create_api_request "http://jsonplaceholder.typicode.com/todos/1" "get" global/api.scr::request_handler "my own data"
```
Result:
```
Creates an http request from the server to url/method combination.

local.result will have one of the following values:

0 = Request created successfully.
1 = Invalid arguments
2 = Client api is not running
3 = Client api error

```
## Slightly modified reborn functions
---

## Reborn original functions
---
