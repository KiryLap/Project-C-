#ifndef FUNCTIONS4_BY_SANNIKOV_H
#define FUNCTIONS4_BY_SANNIKOV_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class BoyerMoore {
public:
    void BoyerMoore(const string& text, const string& pattern);

private:
    std::unordered_map<char, int> last_occurrence;
    std::vector<int> jump_table;
    std::string pattern;
};

#endif 