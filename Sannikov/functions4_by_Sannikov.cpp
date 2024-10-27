#include "functions4.h"
#include "Verification/utils.h"

using namespace std;

BoyerMoore::BoyerMoore(const std::string& pattern) : pattern(pattern) {
    // Инициализация таблицы последнего появления
    for (size_t i = 0; i < pattern.size(); ++i) {
        last_occurrence[pattern[i]] = i;
    }

    // Инициализация таблицы переходов
    jump_table.resize(256, pattern.size());
    for (size_t i = 0; i < pattern.size() - 1; ++i) {
        jump_table[(unsigned char)pattern[i]] = pattern.size() - i - 1;
    }
}

int BoyerMoore::search(const std::string& text) {
    int j = 0;
    for (size_t i = pattern.size() - 1; i < text.size(); ) {
        if (text[i] == pattern[j]) {
            if (j == 0) {
                return i - pattern.size() + 1;
            }
            --j;
            --i;
        }
        else {
            // Используем таблицу переходов
            int jump = jump_table[(unsigned char)text[i]];
            // Используем таблицу последнего появления
            if (last_occurrence.count(text[i])) {
                int last_index = last_occurrence[text[i]];
                if (last_index < jump) {
                    jump = last_index;
                }
            }
            i += jump;
            j = pattern.size() - 1;
        }
    }
    return -1;
}