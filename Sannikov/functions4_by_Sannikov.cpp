#include "functions4_by_Sannikov.h"

using namespace std;

int BoyerMoore(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m == 0) return 0; // Пустой паттерн - всегда найдено в начале

    unordered_map<char, int> last_occurrence;
    for (int i = 0; i < m; ++i) {
        last_occurrence[pattern[i]] = i;
    }

    vector<int> jump_table(256, m); // Все символы имеют начальное смещение m
    for (int i = 0; i < m - 1; ++i) {
        jump_table[(unsigned char)pattern[i]] = m - 1 - i;
    }

    int i = m - 1; // Индекс в тексте
    int j = m - 1; // Индекс в паттерне

    while (i < n) {
        if (text[i] == pattern[j]) {
            if (j == 0) {
                cout << "Совпадение найдено на позиции: " << i << " в тексте." << endl;
                return; // Совпадение найдено
            }
            i--;
            j--;
        }
        else {
            int jump = jump_table[(unsigned char)text[i]];
            if (last_occurrence.count(text[i])) {
                int last_index = last_occurrence[text[i]];
                jump = std::max(jump, j - last_index);
            }
            i += jump + 1; // +1 потому что i уже уменьшен на 1
            j = m - 1;
        }
    }
    cout << "Совпадений не найдено." << endl;
    return; // Совпадение не найдено
}