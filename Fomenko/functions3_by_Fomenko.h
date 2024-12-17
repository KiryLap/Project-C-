#ifndef FUNCTIONS3_BY_FOMENKO_H
#define FUNCTIONS3_BY_FOMENKO_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Структура для представления состояния автомата
struct State {
    int id;
    bool is_final;
    unordered_map<char, int> transitions; // Переходы по символам

    State(int id, bool is_final) : id(id), is_final(is_final) {}
};

vector<State> create_automaton(const string& pattern);

vector<pair<int, int>> find_all_occurrences(const vector<string>& texts, const string& pattern);

vector<int> function_by_Fomenko(const string& text, const string& pattern);

#endif 