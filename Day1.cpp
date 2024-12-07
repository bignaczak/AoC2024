//
// Created by Brian Ignaczak on 12/1/24.
//

#include "Day1.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <numeric>
// #include <ostream>

Day1::Day1() {
    std::string fileName = "./input/day1-a.txt";

    // open file
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << fileName << std::endl;
        return;
    }
    std::cout << "File opened" << std::endl;

    // read the file
    int v1, v2;
    while (file >> v1 >> v2) {
        col1.push_back(v1);
        col2.push_back(v2);
    }

    file.close();

    std::sort(col1.begin(), col1.end());
    std::sort(col2.begin(), col2.end());


    std::cout << "Column 1: ";
    for (int val: col1) {
        std::cout << val << " - ";
    }

    std::cout << "\nColumn 2: ";
    for (int val: col2) {
        std::cout << val << " - ";
    }
    std::cout << std::endl;

    std::vector<int> result(col1.size());
    std:: transform(col2.begin(), col2.end(), col1.begin(), result.begin(),
        [](int a, int b){return a - b;});

    std::cout << "\nResult: ";
    for (int val: result) {
        std::cout << val << " - ";
    }

    int sum = std::accumulate(result.begin(), result.end(), 0, [](int total, int val){return total + std::abs(val);});
    std::cout << "\nSum: " << sum << std::endl;

    std::vector<int> occurrences(col1.size());
    for (int v: col1) {
        occurrences.push_back(v * getOccurrences(v, col2));
    }

    int sum2 = std::accumulate(occurrences.begin(), occurrences.end(), 0, [](int total, int val){return total + std::abs(val);});
    std::cout << "\nSum2: " << sum2 << std::endl;
}

void Day1::sayHi() {
    printf("Hello World\n");
}

int Day1::getOccurrences(int lookupValue, std::vector<int> lookupList) {
    int numOccurrences = std::accumulate(lookupList.begin(), lookupList.end(), 0, [lookupValue](int total, int val){
        if (val == lookupValue) {
            total++;
            return total;
        }
        return total;
    });
    return numOccurrences;
}
