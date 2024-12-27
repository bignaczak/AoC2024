//
// Created by Brian Ignaczak on 12/8/24.
//

#ifndef DAY3_H
#define DAY3_H
#include <regex>
#include <string>
#include <vector>


class Day3 {
public:
    Day3();

private:
    void readFile(std::string path);
    std::vector<std::string> lines;
    void doPartA();

    int getLineSum(std::sregex_iterator begin, bool verbose);

    void doPartB();

    int parseOuterMatch(std::string outerMatchString);
};



#endif //DAY3_H
