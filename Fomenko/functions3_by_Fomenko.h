#ifndef FUNCTIONS3_BY_FOMENKO_H
#define FUNCTIONS3_BY_FOMENKO_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// Структура для представления состояния автомата
struct State {
    int id;
    bool is_final;
    unordered_map<char, int> transitions; // Переходы по символам

    State(int id, bool is_final) : id(id), is_final(is_final) {}
};

vector<State> create_automaton(const string& pattern);

vector<pair<int, int>> find_all_occurrences(const vector<string>& texts, const string& pattern);

#endif 