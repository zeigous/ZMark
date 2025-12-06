#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

#include "predictor.hpp"

class Processor {
    public:
        Processor(std::ifstream *traceFile);
        void reset(Predictor *predictor);
        int tick();

    private:
        std::ifstream *branchTraceFile;

        std::string tracePCString;
        char branchResultChar;

        uint64_t tracePC;
        bool branchResult;

        Predictor internalPredictor;

};