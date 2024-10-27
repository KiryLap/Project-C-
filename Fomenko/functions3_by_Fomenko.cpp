#include "functions3_by_Fomenko.h"
#include "Verification/utils.h"

using namespace std;

// Здесь прописываем, что будет выполнять функция, которая объявлена в .h
// Пример: int fun3(int a, int b) {
            //return a + b;
        //}
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
                break;
            }
        }
    }

    return occurrences;
}

int main() {
    vector<string> texts = {"hello world", "the quick brown fox", "pattern matching"};
    string pattern = "fox";

    vector<pair<int, int>> occurrences = find_all_occurrences(texts, pattern);

    cout << "Индексы текстов, в которых найдена подстрока, и их позиции: " << endl;
    for (auto occurrence : occurrences) {
        cout << "Текст " << occurrence.first << ": позиция " << occurrence.second << endl;
    }

    return 0;
}