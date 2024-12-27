//
// Created by Brian Ignaczak on 12/16/24.
//

#include "Day5.h"

#include <fstream>
#include <iostream>
#include <numeric>
#include <ostream>
#include <set>
#include <sstream>
#include <__ranges/filter_view.h>
#include <__ranges/views.h>

#include "GenUtil.h"

// #define DEBUG

Day5::Day5() {
    #ifdef DEBUG
    std::cout << "Debug mode activated!" << std::endl;
    #endif
    readFile();
    // doPartA();
    doPartB();

}

void Day5::doPartB() {
    // get the unsorted instructions
    auto unsortedInstructions = std::ranges::filter_view(instructions, [&](auto &instruction) {return checkInstructionsVsOrder(instruction) == -1 ? 1 : 0;});
    std::cout << "Number of unsorted: " << std::ranges::distance(unsortedInstructions) << std::endl;
    for (auto &instruction : unsortedInstructions) {
        GenUtil::printVector(instruction, "unsorted");
    }

    // apply sorting (MOVED TO sortAndGetMedian)
    // to sort, create a set of the two numbers, if exist in map then the map value should be first and return true

#ifdef DEBUG
    // test with the 5th element of the unsorted
    int index = 4;
    auto it = unsortedInstructions.begin();
    std::advance(it, index);
    GenUtil::printVector(*it, "5th Unsorted Instruction");

    auto myVector = *it;
    // The comparator should return true if the first element should come before the second element in the sorted order.
    std::ranges::sort(myVector, [&](auto &a, auto &b) {
        if (auto mySet = std::set<int>{a, b}; pagesMap.contains(mySet)) {
            auto leadPage = pagesMap.at(std::set{a, b});
            return a == leadPage ? true : false;
        }
        return false;
    });
    std::cout << "new order for 5th Unsorted: ";
    GenUtil::printVector(myVector, "5th Resorted");

    // test if the underlying data was mutated
    // std::advance(it, index);
    GenUtil::printVector(*it, "5th Lazy after Sort");
    {
        int unsortedMedianSum = 0;
        unsortedMedianSum += sortAndGetMedian(*it);
        std::cout << "unsorted Median Sum: " << unsortedMedianSum << std::endl;
    }
#endif


    int unsortedMedianSum = 0;
    for (auto it = unsortedInstructions.begin(); it != unsortedInstructions.end(); ++it) {
        unsortedMedianSum += sortAndGetMedian(*it);
    }

    // find medians and sum
    std::cout << "unsorted Median Sum: " << unsortedMedianSum << std::endl;

}

int Day5::sortAndGetMedian(std::vector<int> &v) {
    std::ranges::sort(v, [&](auto &a, auto &b) {
    if (auto mySet = std::set<int>{a, b}; pagesMap.contains(mySet)) {
        auto leadPage = pagesMap.at(std::set{a, b});
        return a == leadPage ? true : false;
    }
    return false;
    });
    GenUtil::printVector(v, "Sorted in function");
    return v[v.size() / 2];
}

void Day5::doPartA() {
    std::set<int> pages = {30, 40};
    std::set<int> pages2 = {30, 41};
    std::set<int> pages3 = {30, 40};

    std::cout << std::boolalpha;
    std::cout << "Equal (No) ? : " << (pages == pages2) << std::endl;
    std::cout << "Equal (Yes) ? : " << (pages == pages3) << std::endl;

    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "pages ";
    for (auto page : pages) {
        std::cout << page << " ";
    }
    std::cout << std::endl;

    // test how the lookup functions work for maps using sets
    std::map<std::set<int>, int> testMap =  {{{7,8},7}, {{10,11},10}};
    auto set1 = std::set{3,4};
    testMap[set1] = 3;
    auto set2 = std::set{5,6};
    testMap[set2] =  5;

    std::cout << "Contains (3,4) ? " << testMap.contains(std::set<int>{3,4}) << std::endl;
    std::cout << "Contains (4,3) ? " << testMap.contains(std::set<int>{4,3}) << std::endl;
    std::cout << "Contains (20,21) ? " << testMap.contains(std::set<int>{20,21}) << std::endl;

#ifdef DEBUG
    for (auto [k,v]: testMap) {
        std::string key;
        for (auto s: k) {
            key += std::to_string(s) + ", ";
        }
        std::cout << key << " " << v << std::endl;
    }
#endif

    // for (auto [first, second] : std::ranges::views::adjacent_view(numbers, 2)) {
    //     // Perform pairwise operation
    //     std::cout << first + second << " ";
    // }

    // std::cout << std::endl;



#ifdef DEBUG
    std::cout << "Read-in file: " << std::endl;
    for (auto [key, value]: pagesMap) {
        for (auto k : key) {
            std::cout << k << ", ";
        }
        std::cout << value;
        std::cout << " || ";
    }
    std::cout << std::endl;

    std::cout << "Instructions...." << std::endl;
    for (auto row: instructions) {
        GenUtil::printVector(row, "order");
    }
#endif
    // loop through all the instructions and count the valid ones
    int validInstructions = 0;
    int checkSum = 0;
    for (auto instruction: instructions) {
        auto midNumber = checkInstructionsVsOrder(instruction);
        auto isValid = midNumber != -1;
        checkSum += isValid ? midNumber : 0;
        if (isValid) validInstructions++;
    }
    auto valid2 = std::ranges::filter_view(instructions, [&](auto &item) {return checkInstructionsVsOrder(item) != -1;});
    auto checkSum2 = std::accumulate(instructions.begin(), instructions.end(), 0, [&](int sum, auto &item) {
        auto midValue = checkInstructionsVsOrder(item);
        if (midValue == -1) return sum;
        return sum + midValue;
    });

    std::cout << "Valid instructions: " << validInstructions << std::endl;
    std::cout << "Length of valid2: " << std::ranges::distance(valid2) << std::endl;
    std::cout << "CheckSum1: " << checkSum << std::endl;
    std::cout << "CheckSum2: " << checkSum2 << std::endl;
    std::cout << "end of Day5::doPartA............" << std::endl;
}

void Day5::readFile() {
    std::string fileName = "./input/day5-a.txt";

    // open file
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << fileName << std::endl;
        return;
    }
    std::cout << "File opened" << std::endl;


    // read the file
    std::string line;
    int lineNo = 0;
    // first read in the order pairwise rules
    while (std::getline(file, line) && !line.empty()) {
        std::istringstream ss(line);
        int p1, p2;
        auto myNums = line.find('|');
        p1 = stoi(line.substr(0, myNums));
        p2 = stoi(line.substr(myNums + 1, line.length()));
#ifdef DEBUG
        std::cout << line << std::endl;
        std::cout << "p1: " << p1 << "   p2: " << p2 << std::endl;
#endif
        auto pageSet = std::set{p1, p2};
        pagesMap[pageSet] = p1;
        lineNo++;
    }

    std::cout << "Now reading the print instructions........." << std::endl;
    while (std::getline(file, line)) {
        std::vector<int> row;               // To store a single row
        std::stringstream lineStream(line); // Create a stringstream from the line
        std::string value;
        while (std::getline(lineStream, value, ',')) {
            row.push_back(std::stoi(value));
        }
        instructions.push_back(row);
#ifdef DEBUG
        std::cout << line << std::endl;
#endif
    }



    file.close();
}

int Day5::checkInstructionsVsOrder(std::vector<int> instruction) {
    bool isValid = true;
    for (int i = 1; i < instruction.size(); i++) {
        for (int j = i+1; j < instruction.size(); j++) {
            // grab the pair of numbers in order
            auto leadPage = instruction[i];
            auto trailingPage = instruction[j];
#ifdef DEBUG
            std::cout << "Lead and Trail: " << leadPage << ", " << trailingPage << std::endl;
#endif
            auto curSet = std::set<int>{leadPage, trailingPage};
            // see if an instruction exists
            if (pagesMap.contains(curSet)) {
                // see if order is valid
                isValid = pagesMap[curSet] == leadPage;
                // break if not
                if (!isValid) return -1;
            }
        }
    }
#ifdef DEBUG
    GenUtil::printVector(instruction, "order");
    std::cout << "Length: " << instruction.size() << " -- Mid Position: " << (instruction.size()/2) <<   "   --Middle Number: " << instruction[instruction.size()/2] << std::endl;
#endif
    return instruction[instruction.size()/2];
}
