#ifndef FUNCTIONS4_BY_SANNIKOV_H
#define FUNCTIONS4_BY_SANNIKOV_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

void function_by_Sannikov(const string& text, const string& pattern);

extern vector<int> last_occurrence;
extern vector<int> jump_table;
extern string pattern;

#endif // FUNCTIONS4_BY_SANNIKOV_H