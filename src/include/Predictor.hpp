#pragma once
#include <stdint.h>
#include "LuaWrapper.hpp"

#define GSHARE_GHR_LEN (20)
#define GSHARE_TABLE_LEN (1<<(GSHARE_GHR_LEN))
#define GHSARE_INDEX_MASK (GSHARE_TABLE_LEN-1)

class Predictor {
    public:
        Predictor(const char *luaFilename);
        ~Predictor();
        void reset();
        bool predict(uint64_t PC);
        void update(uint64_t branchPC, bool result, bool prediction);

    private:
        LuaWrapper *lua;
};