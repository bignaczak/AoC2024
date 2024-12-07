//
// Created by Brian Ignaczak on 12/2/24.
//

#include "Day2.h"

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>

#include "GenUtil.h"

namespace Day2 {
    std::vector<std::vector<int>> readFile() {
        std::vector<std::vector<int>> matrix;
        std::ifstream myFile("./input/day2-a.txt");
        if (!myFile.is_open()) {
            std::cerr << "Could not open file " << std::endl;
        }

        std::string line;

        while (std::getline(myFile, line)) {
            std::stringstream ss(line);
            std::vector<int> numbers;
            int number;
            while (ss >> number) {
                numbers.push_back(number);
            }

            // Output the parsed numbers
            // std::cout << "Parsed numbers: ";
            // for (int num : numbers) {
            //     std::cout << num << " ";
            // }
            // std::cout << std::endl;
            matrix.push_back(numbers);
            // break;
        }
        myFile.close();

        std::cout << "Matrix Size: " << matrix.size() << std::endl;
        return matrix;
    }

    std::vector<int> getRotated(std::vector<int> original) {
        // Copy the original vector
        std::vector<int> rotated = original;

        // Rotate the copied vector by 1 position to the left
        std::ranges::rotate(rotated, rotated.begin() + 1);

        // std::cout << "original: ";
        // for (int num : original) {
        //     std::cout << num << " ";
        // }
        // std::cout << std::endl;

        // std::cout << "rotated: ";
        // for (int num : rotated) {
        //     std::cout << num << " ";
        // }
        // std::cout << std::endl;
        return rotated;
    }

    bool isIncreasing(std::vector<int> numbers) {
        bool isIncreasing = true;
        auto rotated = getRotated(numbers);

        for (int i = 0; i < rotated.size() - 1; i++) {
            isIncreasing &= rotated[i] > numbers[i];
            if (!isIncreasing) {
                std::cout << "Not Increasing because " << rotated[i] << " <= " << numbers[i] << std::endl;
                break;
            }
        }
        if (isIncreasing) {
            std::cout << "Increasing!" << std::endl;
        }
        return isIncreasing;
    }

    bool isDecreasing(std::vector<int> numbers) {
        bool isDecreasing = true;
        auto rotated = getRotated(numbers);

        for (int i = 0; i < rotated.size() - 1; i++) {
            isDecreasing &= rotated[i] < numbers[i];
            if (!isDecreasing) {
                std::cout << "Not Decreasing because " << rotated[i] << " >= " << numbers[i] << std::endl;
                break;
            }
        }
        if (isDecreasing) {
            std::cout << "Decreasing!" << std::endl;
        }
        return isDecreasing;
    }

    bool isGradual(std::vector<int> numbers) {
        bool isGradual = true;
        auto rotated = getRotated(numbers);
        for (int i = 0; i < rotated.size() - 1; i++) {
            isGradual = std::abs(rotated[i] - numbers[i]) <= 3;
            if (!isGradual) {
                std::cout << "Not Gradual because " << rotated[i] << " - " << numbers[i] << " too big" << std::endl;
                break;
            }
        }
        if (isGradual) {
            std::cout << "Gradual!" << std::endl;
        }
        return isGradual;
    }

    bool isWithin3(std::vector<int> difs) {
        bool within3 = std::all_of(difs.begin(), difs.end(), [](auto dif) {
            return std::abs(dif) < 4 && dif != 0;
        });
        return within3;
    }

    std::vector<int> getSigns(std::vector<int> numbers) {
        std::vector<int> signs(numbers.size());
        std::ranges::transform(numbers, signs.begin(),[](auto dif) {return GenUtil::signum(dif);});
        return signs;

    }

    int getMeanSign(std::vector<int> signs) {
        return GenUtil::signum(std::accumulate(signs.begin(), signs.end(), 0.0) / signs.size());
    }

    bool isSafe(std::vector<int> difs) {
        return isWithin3(difs) && isSameSign(difs);
    }

    bool isSameSign(std::vector<int> difs) {
        auto signs = getSigns(difs);
        int meanSign = getMeanSign(signs);
        std::cout << "Mean Sign: " << meanSign << std::endl;
        int currentSign = meanSign;
        bool sameSign = std::ranges::all_of(difs, [currentSign](auto dif) {
            return GenUtil::signum(dif) == currentSign;
        });
        return sameSign;
    }

    std::vector<int> getDifs(std::vector<int> numbers) {
        auto rotated = getRotated(numbers);
        GenUtil::printVector(numbers, "original");
        std::vector<int> difs;
        for (int i = 0; i < rotated.size() - 1; i++) {
            difs.push_back((rotated[i] - numbers[i]));
        }
        GenUtil::printVector(rotated, "rotated");

        return difs;
    }

    std::vector<bool> findErrorPositions(std::vector<int> difs, int sign, int difMax) {
        // for each position, see if there is a position matches the target sign
        // note difs length is 1 less than numbers array
        // auto difs = getDifs(numbers);
        auto errors = std::vector<bool>(difs.size(), false);
        std::transform(difs.begin(), difs.end(), errors.begin(), [sign, difMax](int d) {return (GenUtil::signum(d) != sign) | (std::abs(d) > difMax);});

        //error postitons
        std::vector<bool> errorPositions(difs.size() + 1, false);
        for (int i = 0; i < errorPositions.size(); i++) {
            if (i == 0) {
                continue;
            } else {
                errorPositions[i] = errors[i-1];
            }
        }
        return errorPositions;
    }
} // Day2