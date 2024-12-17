#include "functions3_by_Fomenko.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Функция для создания конечного автомата
vector<State> create_automaton(const string& pattern) {
    vector<State> automaton;

    automaton.push_back(State(0, false));

    // Построение автомата
    int state = 0;
    for (char symbol : pattern) {
        // Если переход по символу уже существует, просто обновляем состояние
        if (automaton[state].transitions.find(symbol) != automaton[state].transitions.end()) {
            continue;
        }

        // Создание нового состояния
        automaton.push_back(State(automaton.size(), false));

        // Добавление перехода
        automaton[state].transitions[symbol] = automaton.size() - 1;

        // Обновление текущего состояния
        state = automaton.size() - 1;
    }

    // Пометить последнее состояние как финальное
    automaton[state].is_final = true;

    return automaton;
}

// Функция для поиска подстроки в заданных текстах с помощью конечного автомата
vector<pair<int, int>> find_all_occurrences(const vector<string>& texts, const string& pattern) {
    vector<State> automaton = create_automaton(pattern);
    vector<pair<int, int>> occurrences;

    for (int text_index = 0; text_index < texts.size(); ++text_index) {
        const string& text = texts[text_index];

        int state = 0;

        // Проход по тексту
        for (int i = 0; i < text.length(); ++i) {
            char symbol = text[i];

            // Если переход по символу существует, переходим в новое состояние
            if (automaton[state].transitions.find(symbol) != automaton[state].transitions.end()) {
                state = automaton[state].transitions[symbol];
            } else {
                // Если перехода нет, возвращаемся в начальное состояние
                state = 0;
            }

            // Если текущее состояние является финальным, значит мы нашли совпадение
            if (automaton[state].is_final) {
                occurrences.push_back(make_pair(text_index, i - pattern.length() + 1));
            }
        }
    }

    return occurrences;
}

vector<int> function_by_Fomenko(const string& text, const string& pattern) {
    vector<string> texts = {text}; 
    vector<pair<int, int>> occurrences = find_all_occurrences(texts, pattern);

    vector<int> result_indices;
    if (occurrences.empty()) {
        return result_indices; // Если совпадений не найдено, возвращаем пустой вектор
    } else {
        for (const auto& occurrence : occurrences) {
            result_indices.push_back(occurrence.second); // Добавляем индексы совпадений в результат
        }
    }

    return result_indices; // Возвращаем список индексов совпадений
}