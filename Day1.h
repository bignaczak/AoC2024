//
// Created by Brian Ignaczak on 12/1/24.
//

#ifndef DAY1_H
#define DAY1_H
#include <vector>


class Day1 {
public:
    Day1();
    static void sayHi();

    static int getOccurrences(int lookupValue, std::vector<int> lookupList);

private:
    std::vector<int> col1, col2;
};



#endif //DAY1_H
