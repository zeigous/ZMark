#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

#include "Predictor.hpp"
#include "Processor.hpp"

Processor::Processor(std::ifstream *traceFile, const char *luaFilename) {
    branchTraceFile = traceFile;
    
    internalPredictor = new Predictor(luaFilename);
    
}

Processor::~Processor() {
    branchTraceFile->close();

    delete internalPredictor;
    internalPredictor = nullptr;
}

void Processor::reset() {
    branchTraceFile->clear();
    branchTraceFile->seekg(0);
    internalPredictor->reset();
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

    bool predictorResult = internalPredictor->predict(tracePC); // ehh
    
    internalPredictor->update(tracePC, branchResult, predictorResult);
    

    return branchResult ^ predictorResult; // 0 on correct prediction
}
