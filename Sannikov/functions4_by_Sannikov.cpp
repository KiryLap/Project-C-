#include "functions4_by_Sannikov.h"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void function_by_Sannikov(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    // Проверка на пустой паттерн
    if (m == 0) {
        cout << "Пустой паттерн. Совпадение найдено на позиции: 0 в тексте." << endl;
        return; // Пустой паттерн - считается найденным в начале
    }

    unordered_map<char, int> last_occurrence; // Локальная переменная
    for (int i = 0; i < m; ++i) {
        last_occurrence[pattern[i]] = i; // Запомним последнюю позицию каждого символа
    }

    vector<int> jump_table(256, m); // Начальное смещение для всех символов
    for (int i = 0; i < m - 1; ++i) {
        jump_table[(unsigned char)pattern[i]] = m - 1 - i; // Заполняем таблицу смещений
    }

    int i = m - 1; // Индекс в тексте
    int j = m - 1; // Индекс в паттерне

    while (i < n) {
        if (text[i] == pattern[j]) {
            if (j == 0) {
                cout << "Совпадение найдено на позиции: " << (i) << " в тексте." << endl;
                return; // Совпадение найдено
            }
            i--;
            j--;
        }
        else {
            int jump = jump_table[(unsigned char)text[i]]; // Расчёт смещения
            if (last_occurrence.count(text[i])) {
                int last_index = last_occurrence[text[i]];
                jump = max(jump, j - last_index); // Учитываем последнее появление символа
            }
            i += jump; // Увеличиваем индекс i на размер прыжка
            j = m - 1; // Сброс j на последний символ паттерна
        }
    }
    cout << "Совпадений не найдено." << endl; // Если не нашли совпадения
}