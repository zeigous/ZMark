#include <cstring>
#include <iostream>

#include "Predictor.hpp"
#include "LuaWrapper.hpp"

Predictor::Predictor(const char *luaFilename) {
    
    lua = new LuaWrapper(luaFilename);
    
}

Predictor::~Predictor() {
    
    delete lua;
}

void Predictor::reset() {
    lua->callFunction("reset", 0);
}
bool Predictor::predict(uint64_t PC) {
    int prediction = lua->callFunction("predict", 1, PC);
    return static_cast<bool>(prediction);
}
void Predictor::update(uint64_t branchPC, bool branchResult, bool prediction) {
    int error = lua->callFunction("update", 3, branchPC, branchResult, prediction);
    if (error) exit(1);
}