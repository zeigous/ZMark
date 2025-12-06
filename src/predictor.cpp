#include <cstring>
#include <wren.hpp>

#include "predictor.hpp"


void Predictor::reset() {
    GHR = 0;
    std::memset(tableEntries, 0, sizeof(tableEntries));
}
bool Predictor::predict(uint64_t PC) {
    uint32_t index = ((uint32_t)PC & GHSARE_INDEX_MASK) ^ (GHR & GHSARE_INDEX_MASK);

    return (tableEntries[index] < 2) ? false : true;
}
void Predictor::update(uint64_t branchPC, bool branchResult, bool prediction) {
    uint32_t index = ((uint32_t)branchPC & GHSARE_INDEX_MASK) ^ (GHR & GHSARE_INDEX_MASK);

    if (branchResult) {
        if (tableEntries[index] < 3) tableEntries[index]++;
    } else {
        if (tableEntries[index] > 0) tableEntries[index]--;
    }

    GHR = ((GHR<<1) & GHSARE_INDEX_MASK) | (branchResult ? 1 : 0);
}