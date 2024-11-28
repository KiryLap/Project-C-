#include "functions2_by_Muratov.h"
#include "Verification/utils.h"

using namespace std;

vector<int> function_by_Muratov(const string& text, string& pattern) {
    const int BASE = 31;        // Основание для хеш-функции
    const int MOD = 1e9 + 7;    // Большое простое число для модуля
    int text_len = text.length();
    int pattern_len = pattern.length();

    if (pattern_len > text_len) {
        return {}; // Если шаблон длиннее текста, совпадений нет
    }

    // Вычисляем хеш шаблона и первого окна текста
    long long pattern_hash = 0, current_hash = 0, basePower = 1;

    for (int i = 0; i < pattern_len; ++i) {
        pattern_hash = (pattern_hash * BASE + pattern[i]) % MOD;
        current_hash = (current_hash * BASE + text[i]) % MOD;
        if (i > 0) basePower = (basePower * BASE) % MOD;
    }

    vector<int> positions;

    // Сканируем текст
    for (int i = 0; i <= text_len - pattern_len; ++i) {
        // Если хеши совпадают, проверяем подстроку
        if (current_hash == pattern_hash && text.substr(i, pattern_len) == pattern) {
            positions.push_back(i);
        }

        // Обновляем хеш для следующего окна текста
        if (i < text_len - pattern_len) {
            current_hash = (current_hash - text[i] * basePower % MOD + MOD) % MOD;
            current_hash = (current_hash * BASE + text[i + pattern_len]) % MOD;
        }
    }

    return positions;
}