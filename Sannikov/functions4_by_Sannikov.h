#ifndef FUNCTIONS4_H
#define FUNCTIONS4_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class BoyerMoore {
public:
    BoyerMoore(const std::string& pattern);
    int search(const std::string& text);

private:
    std::unordered_map<char, int> last_occurrence;
    std::vector<int> jump_table;
    std::string pattern;
};

#endif 