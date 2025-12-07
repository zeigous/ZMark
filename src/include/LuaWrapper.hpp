#pragma once
#include <cstdarg>

#include "lua/lua.hpp"

class LuaWrapper {
    public:
        LuaWrapper(const char *luaFilename);
        ~LuaWrapper();
        int callFunction(const char *funcName, int count, ...);

    private:
        lua_State *luaVM;
};