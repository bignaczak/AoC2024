//
// Created by Brian Ignaczak on 12/2/24.
//

#ifndef DAY2_H
#define DAY2_H
#include <vector>

namespace Day2 {

    std::vector<std::vector<int>> readFile();
    bool isDecreasing(std::vector<int> numbers);
    bool isIncreasing(std::vector<int> numbers);
    bool isGradual(std::vector<int> numbers);
    std::vector<int> getDifs(std::vector<int>numbers);
    std::vector<bool> findErrorPositions(std::vector<int> numbers, int sign, int difMax);
    bool isWithin3(std::vector<int> difs);
    std::vector<int> getSigns(std::vector<int> numbers);
    bool isSafe(std::vector<int> difs);
    bool isSameSign(std::vector<int> difs);
    int getMeanSign(std::vector<int> signs);
    class Day2 {

    };

} // Day2

#endif //DAY2_H
