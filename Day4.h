//
// Created by Brian Ignaczak on 12/15/24.
//

#ifndef DAY4_H
#define DAY4_H
#include <vector>

#endif //DAY4_H

class Day4 {
    public:
    void doPartA();

    Day4();

    void doPartB();

    int getRowHits(bool verbose = false);

    int getColHits(bool verbose);

    int getHitsInVector(std::vector<std::string> myVec, bool verbose);

    int getForwardDiagHits(bool verbose);

    int getBackwardDiagHits(bool verbose);

    std::vector<std::string> transposeVector(std::vector<std::string> rows, bool verbose = false);

    std::vector<std::string> getForwardDiags(std::vector<std::string> lines, bool verbose);

    std::vector<std::string> getBackwardDiags(std::vector<std::string> lines, bool verbose);

    static int countHits(std::string line, bool verbose = false);

private:
    std::vector<std::string> lines;

};