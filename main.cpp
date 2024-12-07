#include <iostream>
#include <numeric>
#include <set>

#include "Day1.h"
#include "Day2.h"
#include "GenUtil.h"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";


    // Day1::sayHi();
    // auto day1 = Day1();
    auto matrix = Day2::readFile();
    int safeCount = 0;
    int extraSafeCount = 0;
    int safe2 = 0;
    std::vector<std::vector<int>> singleErrors;
    std::vector<std::vector<int>> editedList;
    std::vector<std::vector<bool>> errorPatterns;
    std::vector<std::vector<int>> extrSafeRows;

    for (auto myVec: matrix) {
        // auto isSafe = (Day2::isIncreasing(myVec) | Day2::isDecreasing(myVec)) & Day2::isGradual(myVec);
        // if (isSafe) {safeCount++;}

        auto myDifs = Day2::getDifs(myVec);
        GenUtil::printVector(myDifs, "Difs");

        if (Day2::isSafe(myDifs)) {
            safe2++;
        } else {


            // find error positions Note: errors is same size as myVec (first position assumed good)
            auto errors = Day2::findErrorPositions(myDifs, Day2::getMeanSign(Day2::getSigns(myDifs)), 3);
            errorPatterns.push_back(errors);
            GenUtil::printVector(errors, "errors");

            int numErrors = std::accumulate(errors.begin(), errors.end(), 0, [](int total, int val) {return val + total;});
            std::cout << "Number of errors: " << numErrors << std::endl;
            // for arrays with a single error
            if (numErrors >= 1) {
                singleErrors.push_back(myVec);
                // remove erroneous number
                std::vector<int> edited;
                // find the first error and remove
                for (int i = 0; i < myVec.size(); i++) {
                    if (errors[i] == false){edited.push_back(myVec[i]);}
                }
                editedList.push_back(edited);
                auto editedDifs = Day2::getDifs(edited);
                // GenUtil::printVector(edited, "edited");
                // Now perform see if change is gradual
                if (Day2::isSafe(editedDifs)) {
                    extraSafeCount++;
                    extrSafeRows.push_back(edited);
                }
            } else if (numErrors == 2) {
                std::cout << "!!!!!!!!!!!!!!!!!!   HERE'S ONE    !@!!!!!!!!!!!!!!!!\n";
            }

        }

    }

    std::cout << "Safe Rows: " << safeCount << std::endl;
    std::cout << "Safe2 Rows: " << safe2 << std::endl;
    std::cout << "Extra Safe Rows: " << extraSafeCount << std::endl;
    std::cout << "Total Safe with Extra: " << safe2 + extraSafeCount << std::endl;

    std::cout << "Extra Safes: " << std::endl;
    for (int i = 0; i < extrSafeRows.size(); i++) {
        // GenUtil::printVector(singleErrors[i], "single error");
        // GenUtil::printVector(editedList[i], "edited");
        GenUtil::printVector(extrSafeRows[i], "extra Safe");


    }
    std::cout << std::endl;
    // auto myInts =
    // GenUtil::printVector(std::ranges::transform(errorPatterns, errorPatterns.begin(),[](ep) {}), "error Patterns");


    return 0;
}



// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.