//
// Created by Brian Ignaczak on 12/8/24.
//

#include "Day3.h"

#include <fstream>
#include <iostream>
#include <numeric>
#include <ostream>
#include <regex>

#include "GenUtil.h"

Day3::Day3() {
    std::string fileName = "./input/day3-a.txt";
    std::cout << "Reading file: " << fileName << std::endl;
    readFile(fileName);
    GenUtil::printVector(lines, "Lines");
    std::cout << "length lines: " << lines.size() << std::endl;
    // doPartA();
    for (auto line : lines) {
        std::cout << line << std::endl;
    }
    doPartB();
}

void Day3::readFile(std::string path) {
    // open file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }
    std::cout << "File opened" << std::endl;

    // read the file
    std::string line;
    while (file >> line) {
        lines.push_back(line);
    }

    file.close();
}

void Day3::doPartA() {
    std::regex myPattern(R"(mul\s*[(]\s*(\d+)\s*,\s*(\d+)[)])");
    std::cout << "Number of lines: " << lines.size() << std::endl;

    int allLines = 0;
    for (int i = 0; i < lines.size(); i++) {
        auto line = lines[i];
        std::cout << "First line: " << line << std::endl;
        // Create a regex iterator to iterate through all matches
        auto begin = std::sregex_iterator(line.begin(), line.end(), myPattern);
        // auto lineSum = std::accumulate(std::sregex_iterator(line.begin(), line.end(), myPattern),)
        auto lineSum = getLineSum(begin, true);
        std::cout << "Line " << i << " sum: " << lineSum << std::endl;
        allLines += lineSum;
    }
    std::cout << "All lines: " << allLines << std::endl;
}

/**
 * Convert regex matchstring to sum
 * @param begin
 * @param end
 * @return
 */
int Day3::getLineSum(std::sregex_iterator begin, bool verbose) {
    auto end = std::sregex_iterator();
    int sum = 0;
    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;
        int num1 = std::stoi(match.str(1));
        int num2 = std::stoi(match.str(2));
        sum += num1 * num2;
        if (verbose) std::cout << "num1: " << num1 << "\tnum2: " << num2 << "\tproduct: " << num1 * num2 << "\tsum: " << sum << std::endl;
    }
    return sum;

}

void Day3::doPartB() {
    // algorithm overview
    // combine lines into a single string
    // capture the beginning --> perform math
    // capture between do and don't --> perform math
    // get the string after the last don't --> capture everything after do() --> perform math
    // 88844908 too low

    // combine lines to a single string
    std::string allLines = "";
    for (const auto& line: lines) {
        allLines += line;
    }

    // capture beginning
    std::regex beginningPattern(R"(^(.*?)(?=(?:don't\(\))|(?:do\(\))))");
    auto begin = std::sregex_iterator(allLines.begin(), allLines.end(), beginningPattern);
    auto end = std::sregex_iterator();
    int total = 0;
    std::vector<int> matchSums;

    for (std::regex_iterator it = begin; it != end; ++it) {
        std::smatch outerMatch = *it;
        std::cout << "Beginning match:  " << outerMatch.str() << std::endl;
        int matchSum = parseOuterMatch(outerMatch.str());
        std::cout << "beginning  sum: " << matchSum << std::endl;
        matchSums.push_back(matchSum);
        total += matchSum;
    }

    // capture the do --> don't
    std::regex outerPattern(R"(do[(][)].*?don't[(][)])");
    begin = std::sregex_iterator(allLines.begin(), allLines.end(), outerPattern);
    // for all the matches within a line
    int j = 0;
    for (std::sregex_iterator it = begin; it != end; ++it) {
        std::smatch outerMatch = *it;
        std::cout << "Match " << j << ": " << outerMatch.str() << std::endl;
        int matchSum = parseOuterMatch(outerMatch.str());
        std::cout << "match " << j++ << " sum: " << matchSum << std::endl;
        matchSums.push_back(matchSum);
        total += matchSum;
    }
    std::cout << "line sum: " << total << std::endl;

    // capture after the final don't
    std::regex trailingPattern(R"(.*(?:don't\(\))(.*))");
    begin = std::sregex_iterator(allLines.begin(), allLines.end(), trailingPattern);
    for (std::sregex_iterator it = begin; it != end; ++it) {
        std::smatch outerMatch = *it;
        auto trailingString = outerMatch.str(1);
        std::cout << "Trailing Match " << j++ << ": " << trailingString << std::endl;
        // get the stuff after do()
        std::regex finalDoPattern(R"(do\(\)(.*))");
        auto beginFinal = std::sregex_iterator(trailingString.begin(), trailingString.end(), finalDoPattern);
        std::smatch finalMatch = *beginFinal;
        std::cout << "Final Match: " << finalMatch.str() << std::endl;
        int matchSum = parseOuterMatch(finalMatch.str());
        std::cout << "Final match sum: " << matchSum << std::endl;
        matchSums.push_back(matchSum);
        total += matchSum;
    }
    std::cout << "Grand Total: " << total << std::endl;

    GenUtil::printVector(matchSums, "match sums");
    int checkSum = std::accumulate(matchSums.begin(), matchSums.end(), 0);
    std::cout << "Checksum: " << checkSum << std::endl;
    // allSum += lineSum;
        // break;
    // }
    // std::cout << "All lines: " << allSum << std::endl;



}

int Day3::parseOuterMatch(std::string outerMatchString) {
    // within the capture, perform regex to part numbers
    std::regex innerPattern(R"(mul\s*[(]\s*(\d+)\s*,\s*(\d+)[)])");
    auto innerBegin = std::sregex_iterator(outerMatchString.begin(), outerMatchString.end(), innerPattern);
    int matchSum = getLineSum(innerBegin, false);
    return matchSum;

}
