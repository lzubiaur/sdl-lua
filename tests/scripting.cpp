#include "catch.hpp"
#include <iostream>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

TEST_CASE("Simple Lua script exec", "[LUA]") {

    lua_State *L = luaL_newstate();
    luaL_openlibs(L); /* Load Lua libraries */

    int status = luaL_dofile(L, "script.lua");
    if (status) {
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
}
