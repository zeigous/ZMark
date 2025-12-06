#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

#include "predictor.hpp"
#include "processor.hpp"

Processor::Processor(std::ifstream *traceFile) {
    branchTraceFile = traceFile;
}

void Processor::reset(Predictor *predictor) {
    branchTraceFile->clear();
    branchTraceFile->seekg(0);

    if (predictor) {
        internalPredictor = *predictor;
    }

    internalPredictor.reset();
}
int Processor::tick() {
    std::getline(*branchTraceFile, tracePCString, ' ');
    if (branchTraceFile->fail() || branchTraceFile->eof()) return -1;

    int c = branchTraceFile->get();
    if (c == EOF) return -1;
    branchResultChar = static_cast<char>(c);

    int nl = branchTraceFile->get();
    if (nl == EOF) return -1;
    if (nl == '\r') {
        int next = branchTraceFile->peek();
        if (next == '\n') branchTraceFile->get();
    } else if (nl != '\n') {
        return -1;
    }

    tracePC = std::stoull(tracePCString, nullptr, 16);
    branchResult = (branchResultChar == 't');

    bool predictorResult = internalPredictor.predict(tracePC);
    internalPredictor.update(tracePC, branchResult, predictorResult);

    return branchResult ^ predictorResult;
}
