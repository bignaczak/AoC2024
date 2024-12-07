//
// Created by Brian Ignaczak on 12/7/24.
//

#ifndef GENUTIL_H
#define GENUTIL_H
#include <iostream>
#include <vector>

namespace GenUtil {
    template <typename T>
    void printVector(std::vector<T> v, std::string name) {
        std::cout << name << ": ";
        for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;

    }

    template <typename T>
    int signum(T x) {
            return (x > 0) - (x < 0);
        }

class GenUtil {

};

} // GenUtil

#endif //GENUTIL_H
