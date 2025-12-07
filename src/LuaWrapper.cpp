#include <iostream>
#include <cstdarg>
#include "lua/lua.hpp"

#include "LuaWrapper.hpp"


LuaWrapper::LuaWrapper(const char *luaFilename) {
    luaVM = luaL_newstate();
    luaL_openlibs(luaVM);

    if (luaL_dofile(luaVM, luaFilename) == LUA_OK) {
        std::cout << "[C] Initiated: " << luaFilename << "\n";
    } else {
        std::cout << "[C] Error reading script\n";
        luaL_error(luaVM, "Error: %s\n", lua_tostring(luaVM, -1));
    }

}

LuaWrapper::~LuaWrapper() {
    lua_close(luaVM);
}

int LuaWrapper::callFunction(const char *funcName, int count, ...) {
    va_list args;
    va_start(args, count);
    lua_Number result;

    lua_getglobal(luaVM, funcName);
    if (lua_isfunction(luaVM, -1)) {
        for (int i = 0; i < count; i++) {
            uint64_t argument = va_arg(args, uint64_t);
            lua_pushinteger(luaVM, (lua_Integer)argument);
        }
        lua_pcall(luaVM, count, 1, 0);
        result = lua_tonumber(luaVM, -1);
        lua_pop(luaVM, 1);
    } else { 
        std::cout << "[C] Error: didn't find a function on top of Lua stack\n";
        exit(1);
    }

    va_end(args);
    return static_cast<int>(result);
}

