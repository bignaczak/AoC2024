//
// Created by Brian Ignaczak on 12/16/24.
//


#ifndef DAY5_H
#define DAY5_H
#include <iostream>
#include <set>
#include <map>
#include <ostream>

class Day5 {
public:

    Day5();
    ~Day5() {
        std::cout << "Day5 destructor has been invoked!!!!" << std::endl;
    }
private:
    std::map<std::set<int>, int> pagesMap;  // key: pair of numbers as set value: which number is sorted first
    std::vector<std::vector<int>> instructions;
    void doPartA();
    void doPartB();

    int sortAndGetMedian(std::vector<int> &v);

    void readFile();

    int checkInstructionsVsOrder(std::vector<int> instructions);
};



#endif //DAY5_H
