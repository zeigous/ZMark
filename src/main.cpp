#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

#include "predictor.hpp"
#include "processor.hpp"

using std::string;

void argumentInvalid(string argument) {
    std::cout << std::endl;
    std::cout << "*********************************************" << "\n";
    std::cout << "\"" << argument << "\" is not a valid argument" << "\n";
    std::cout << "*********************************************" << "\n\n";
}

void fileInvalid(string fileName) {
    std::cout << std::endl;
    std::cout << "*********************************************" << "\n";
    std::cout << "\"" << fileName << "\" is not a valid file" << "\n";
    std::cout << "*********************************************" << "\n\n";
}


int main(int argc, char **argv) {
    // File Handling
    std::ifstream traceFile;
    std::ofstream csvFile;

    char currentArg = 0;
    string argument;

    for (int i = 0; i < argc; i++) {
        if (i == 0) continue;

        argument = argv[i];
        if (argument[0] == '-') {
            currentArg = argument[1];
        } else if (currentArg != 0){    
            switch (currentArg) {
                case ('t'):
                    traceFile.open(argument);
                    if (!traceFile.is_open()) {
                        fileInvalid(argument);
                        return 1;
                    }
                    break;

                case ('o'):
                    csvFile.open(argument, std::ios::out);
                    if (!csvFile.is_open()) {
                        fileInvalid(argument);
                        return 1;
                    }
                    break;

                default:
                    argumentInvalid(string(1, currentArg));
            }
            currentArg = 0;
        } else {
            argumentInvalid(argument);
            return 1;
        }
    }

    if (!traceFile.is_open()) {
        std::cout << std::endl;
        std::cout << "*********************************************" << "\n";
        std::cout << "No input trace file specified" << "\n";
        std::cout << "*********************************************" << "\n\n";
        return 1;
    }

    if (csvFile.is_open()) {
        csvFile << "Accurracy After n Branches, " << "Accurracy in %\n";
    }


    // Predictor Stuff
    Predictor predictor;
    Processor processor(&traceFile);
    processor.reset(&predictor);

    uint64_t totalBranches = 0;
    uint64_t correctPredictions = 0;

    int tick = 0;
    do {
        tick = processor.tick();
        totalBranches++;

        if (tick == 0) {
            correctPredictions += 1;
        }
        if (csvFile.is_open() && (totalBranches % 1000) == 0) {
            float percentCorrect = (float)correctPredictions/(float)totalBranches;
            csvFile << totalBranches << ", "<< percentCorrect*100 << "%\n";
        }
    } while (tick != -1);

    // calculate accurracy
    if (csvFile.is_open()) {
        float percentCorrect = (float)correctPredictions/(float)totalBranches;
        csvFile << "\n\nfinal accurracy, " << percentCorrect*100 << "%\n";
    } else {
        float percentCorrect = (float)correctPredictions/(float)totalBranches;
        std::cout << percentCorrect*100 << "%\n";
    }

    // TODO: FIX
    traceFile.close();
}