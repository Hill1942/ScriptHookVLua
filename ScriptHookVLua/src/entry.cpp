/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/


#include "..\inc\natives.h"
#include "..\inc\types.h"
#include "..\inc\enums.h"
#include "..\inc\main.h"
#include "..\lua\lua.hpp"


void ScriptMain()
{	
	lua_State *lua_state;
	lua_state = luaL_newstate();
	// load Lua libraries
	luaL_openlibs(lua_state);
	//tolua_natives_open(lua_state);
	if (luaL_dofile(lua_state, "scripts/main.lua")) {
		fprintf(stderr, "Main.lua: %s\n", lua_tostring(lua_state, -1));
		lua_pop(lua_state, 1);

	}
	lua_pushcfunction(lua_state, &get_key_pressed);
	lua_setglobal(lua_state, "get_key_pressed");
	lua_pushcfunction(lua_state, &wait);
	lua_setglobal(lua_state, "wait");
	//run_function(lua_state, "init");

	lua_getglobal(lua_state, "init");
	int error = lua_pcall(lua_state, 0, 0, 0);
	//return lua_state;
}
