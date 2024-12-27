//
// Created by Brian Ignaczak on 12/7/24.
//

#ifndef GENUTIL_H
#define GENUTIL_H
#include <fstream>
#include <iostream>
#include <vector>

namespace GenUtil {
    template <typename T>
    void printVector(std::vector<T> v, std::string name, std::string delimiter = " ") {
        std::cout << name << ":" << delimiter;
        for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << delimiter;
        }
        std::cout << std::endl;

    }

    template <typename T>
    int signum(T x) {
            return (x > 0) - (x < 0);
        }

    inline std::vector<std::string> readFile(std::string path) {

        std::vector<std::string> lines;
        // open file
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error opening file " << path << std::endl;
            return lines;
        }
        std::cout << "File opened" << std::endl;

        // read the file
        std::string line;
        while (file >> line) {
            lines.push_back(line);
        }

        file.close();
        return lines;
    }

class GenUtil {

};

} // GenUtil

#endif //GENUTIL_H
