//
// Created by Brian Ignaczak on 12/15/24.
//

#include "Day4.h"

#include <regex>

#include "GenUtil.h"



Day4::Day4() {
    lines = GenUtil::readFile("./input/day4-a.txt");
    // GenUtil::printVector(lines, "lines", "\n");
    std::cout << "Matrix size: " << lines.size() << " rows X " << lines[0].size() << " columns" << std::endl;

    // doPartA();
    doPartB();

}

void Day4::doPartA() {
    int rowHits = getRowHits(false);
    std::cout << "row hits: " << rowHits << std::endl;

    int colHits = getColHits(false);
    std::cout << "col hits: " << rowHits << std::endl;

    auto forwardDiagHits = getForwardDiagHits(false);
    std::cout << "forward diag hits: " << forwardDiagHits << std::endl;

    auto backwardDiagHits = getBackwardDiagHits(false);
    std::cout << "backward diag hits: " << backwardDiagHits << std::endl;

    std::cout << "Total Hits: " << rowHits + colHits + forwardDiagHits + backwardDiagHits << std::endl;
}

void Day4::doPartB() {
    int xmasCount = 0;
    for (int i = 1; i < lines.size() - 1; i++) {
        for (int j = 1; j < lines[i].size() - 1; j++) {
            auto anchorStr= lines[i][j];
            if (anchorStr == 'A') {
                // see if is MAS
                auto ulStr = lines[i-1][j-1];
                auto lrStr = lines[i+1][j+1];
                auto urStr = lines[i-1][j+1];
                auto llStr = lines [i+1][j-1];
                bool isMas = (ulStr == 'M' && lrStr == 'S') || (ulStr == 'S' && lrStr == 'M');
                if (isMas) {
                    std::cout << "MAS detected at (" << i << ", " << j << ")"<< std::endl;
                    // check if xmas
                    bool isXmas = (urStr == 'M' && llStr == 'S') || (urStr == 'S' && llStr == 'M');
                    if (isXmas) {
                        std::cout << "XMAS detected at (" << i << ", " << j << ")"<< std::endl;
                        xmasCount++;
                    } else {
                        std::cout << "But not an XMAX" << std::endl;
                    }
                }

            }
        }
    }
    std::cout << "xmas: " << xmasCount << std::endl;
}

int Day4::getRowHits(bool verbose) {
    int totalRowHits = getHitsInVector(lines, false);
    // for (int i = 0; i < lines.size(); i++) {
    //
    //     auto rowHits = countHits(lines[i], false);
    //     if (verbose) std::cout << "row " << i << " hits: " << rowHits << std::endl;
    //     totalRowHits += rowHits;
    // }
    std::cout << "total row hits: " << totalRowHits << std::endl;
    return totalRowHits;
}

int Day4::getColHits(bool verbose) {
    int totalColHits = 0;
    auto transposed = transposeVector(lines);
    if (verbose) GenUtil::printVector(transposed, "\n");
    if (verbose) std::cout << "len transposed: " << transposed.size() << std::endl;

    totalColHits = getHitsInVector(transposed, false);
    if (verbose) std::cout << "Total col hits: " << totalColHits << std::endl;
    return totalColHits;

}

int Day4::getHitsInVector(std::vector<std::string> myVec, bool verbose) {
    int totalHits = 0;
    for (int i = 0; i < myVec.size(); i++) {
        auto hits = countHits(myVec[i], false);
        if (verbose) std::cout << "line " << i << " hits: " << hits << " -- " << myVec[i] << std::endl;
        totalHits += hits;
    }
    if (verbose) std::cout << "Total hits: " << totalHits << std::endl;
    return totalHits;
}

int Day4::getForwardDiagHits(bool verbose) {
    auto transposed = getForwardDiags(lines, false);
    if (verbose) GenUtil::printVector(transposed, "\n");
    std::cout << "len transposed: " << transposed.size() << std::endl;
    return getHitsInVector(transposed, false);
}

int Day4::getBackwardDiagHits(bool verbose) {
    auto transposed = getBackwardDiags(lines, true);
    if (verbose) GenUtil::printVector(transposed, "\n");
    std::cout << "len transposed: " << transposed.size() << std::endl;
    return getHitsInVector(transposed, false);
}

std::vector<std::string> Day4::transposeVector(std::vector<std::string> rows, bool verbose) {
    std::vector<std::string> transposed;
    // transpose the matrix
    int size = lines[0].size();
    for (int i = 0; i < size; i++) {
        std::string col = "";
        for (int j = 0; j < size; j++) {
            col += lines[j][i];
        }
        transposed.push_back(col);
        if (verbose) std::cout << col << "\n";
    }
    return transposed;
}
std::vector<std::string> Day4::getForwardDiags(std::vector<std::string> lines, bool verbose) {
    std::vector<std::string> rowSweep;
    std::vector<std::string> colSweep;
    int maxSize = lines.size();
    // row sweep
    for (int startRow = 0; startRow < maxSize-3; startRow++) {
        std::string line = "";
        int curRow = startRow;
        for (int curCol = 0; curRow < maxSize && curCol < maxSize; curCol++) {
            line += lines[curRow++][curCol];
        }
        if (verbose) std::cout << "line " << startRow << " : " << line << "\n";
        rowSweep.push_back(line);
    }

    for (int startCol = 1; startCol < maxSize-3; startCol++) {
        std::string line = "";
        int curCol = startCol;
        for (int curRow = 0; curRow < maxSize && curCol < maxSize; curRow++) {
            line += lines[curRow][curCol++];
        }
        if (verbose) std::cout << "line " << startCol << " : " << line << "\n";
        colSweep.push_back(line);
    }
    // concat the colSweep vector to end of rowSweep
    rowSweep.insert(rowSweep.end(), colSweep.begin(), colSweep.end());
    return rowSweep;
}

std::vector<std::string> Day4::getBackwardDiags(std::vector<std::string> lines, bool verbose) {
    std::cout << "Inside getBakwardDiag with verbose: " << verbose << "\n";
    std::vector<std::string> rowSweep;
    std::vector<std::string> colSweep;
    int maxSize = lines.size();

    // row sweep
    for (int startRow = 0; startRow < maxSize - 3; startRow++) {
        std::cout << "Insider rowSweep: " << startRow << std::endl;
        std::string line = "";
        int curRow = startRow;
        for (int curCol = maxSize - 1; curRow < maxSize && curCol > -1; curCol--) {
            line += lines[curRow++][curCol];
        }

        if (verbose) std::cout << "line " << startRow << " : " << line << "\n";
        rowSweep.push_back(line);
    }

    for (int startCol = 3; startCol < maxSize - 1; startCol++) {
        std::string line = "";
        int curCol = startCol;
        for (int curRow = 0; curRow < maxSize && curCol > -1; curRow++) {
            line += lines[curRow][curCol--];
        }

        if (verbose) std::cout << "line " << startCol << " : " << line << "\n";
        colSweep.push_back(line);
    }
    // concat the colSweep vector to end of rowSweep
    rowSweep.insert(rowSweep.end(), colSweep.begin(), colSweep.end());
    return rowSweep;
}

int Day4::countHits(std::string line, bool verbose) {
    int hits = 0;
    std::regex forwardPattern(R"(XMAS)");
    std::regex backwardPattern(R"(SAMX)");

    auto matches = std::sregex_iterator(line.begin(), line.end(), forwardPattern);
    auto end = std::sregex_iterator();
    int fhits = std::distance(matches, end);
    if (verbose) { std::cout << "forward hits: " << fhits << std::endl; }

    matches = std::sregex_iterator(line.begin(), line.end(), backwardPattern);
    int bhits = std::distance(matches, end);
    if (verbose) { std::cout << "backward hits: " << bhits << std::endl; }

    return fhits + bhits;

}
