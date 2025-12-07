#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

#include "Predictor.hpp"

class Processor {
    public:
        Processor(std::ifstream *traceFile, const char *luaFilename);
        ~Processor();
        void reset();
        int tick();

    private:
        std::ifstream *branchTraceFile;

        std::string tracePCString;
        char branchResultChar;

        uint64_t tracePC;
        bool branchResult;

        Predictor *internalPredictor;

};