#pragma once
#include <stdint.h>

#define GSHARE_GHR_LEN (20)
#define GSHARE_TABLE_LEN (1<<(GSHARE_GHR_LEN))
#define GHSARE_INDEX_MASK (GSHARE_TABLE_LEN-1)

class Predictor {
    public:
        void reset();
        bool predict(uint64_t PC);
        void update(uint64_t branchPC, bool result, bool prediction);

    private:
        uint16_t GHR;
        uint8_t tableEntries[GSHARE_TABLE_LEN];

        WrenConfiguration config;
};