#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <algorithm>

using namespace std;

template <typename T>
T read_positive(const string &prompt, const string &errorMessage, const T maxValue = numeric_limits<T>::max());
long number_or_default(const string &input, long defaultValue = -1);
int input_int_in_range(const string &prompt, int minValue, int maxValue);

#endif 