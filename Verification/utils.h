#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <algorithm>

using namespace std;

template <typename T>
T read_positive(const string &prompt, const string &error_message, const T max_value = numeric_limits<T>::max());
long number_or_default(const string &input, long default_value = -1);
int input_int_in_range(const string &prompt, int min_value, int max_value);

#endif 