#include <iostream>
#include <chrono>
#include "Verification/utils.h"
#include "Cheremshanov/functions1_by_Cheremshanov.h"
#include "Muratov/functions2_by_Muratov.h"
#include "Fomenko/functions3_by_Fomenko.h"
#include "Sannikov/functions4_by_Sannikov.h"
#include <vector>
#include <utility>
#include <string>
#include <functional>


void setupLocale() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

void measure_time(const function<vector<int>(const string&, const string&)>& func, const string& text, const string& pattern) {
    auto start = chrono::high_resolution_clock::now();
    vector<int> result = func(text, pattern);
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double, milli> duration = end - start;

    if (result.empty()) {
        cout << "Совпадений не найдено.";
    } else {
        cout << "Найдено совпадений на позициях: ";
        for (int index : result) {
            cout << index << " ";
        }
    }
    cout << "\nВремя выполнения: " << duration.count() << " мс\n";
}

void run(const function<vector<int>(const string&, const string&)>& test_function) {
    vector<pair<string, string>> tests = {
        // Длинный текст, где паттерны находятся в начале
        { "pattern1" + string(1000000, 'a') + "pattern2" + string(1000000, 'b') + "pattern3", "pattern1" }, // Тест 1

        // Длинный текст, где паттерны находятся в конце
        { string(1000000, 'a') + "pattern1" + string(1000000, 'b') + "pattern2" + "pattern3", "pattern3" }, // Тест 2

        // Паттерны с множеством повторений в длинном тексте
        { "pattern1" + string(5000, 'a') + "pattern2" + string(5000, 'b') + "pattern3", "pattern2" }, // Тест 3

        // Длинный текст без паттернов
        { string(20000, 'x') + "pattern1" + "pattern2" + "pattern3", "pattern1" }, // Тест 4

        // Паттерны равны тексту
        { "pattern1pattern2pattern3", "pattern3" }, // Тест 5

        // Текст с разными символами, паттерн в середине
        { "aaaaabbbbcccccdddddeeeeepatterbbn1pattern2", "bb" }, // Тест 6

        // Паттерн расположен в середине большого количества одинаковых символов
        { string(10000, 'a') + "pattern1pattern2" + string(10000, 'a'), "pattern1" }, // Тест 7

        // Паттерны отсутствуют в длинном тексте
        { "Тек", "pattern1" }, // Тест 8

        // Небольшой текст с многими повторами, где особенность Рабина-Карпа будет полезна
        { "aaaaaaaabaaaabaaaaaaapattern1", "ab" }, // Тест 9

        // Сложный случай, где лучше работает Бойер-Мур
        { "the quick brown fox jumps over the lazy pattern1 dog and pattern2", "fox" }, // Тест 10

        // Длинный текст с многоразовыми символами для теста на эффективность
        { "pattern2" + string(50000, 'a') + "pattern1" + "pattern2" + string(50000, 'b'), "pattern2" }, // Тест 11

        // Паттерн с уникальными символами и текст
        { "abcdefgabcdefgabcdefgpattern1pattern2", "cde" }, // Тест 12
    };

    // Проход по всем тестам и выполнение их
    for (size_t i = 0; i < tests.size(); ++i) {
        const string& text = tests[i].first;
        const string& pattern = tests[i].second;
        cout << "\n" << "Тест " << (i + 1) << ": ";
        measure_time(test_function, text, pattern);
    }
}

int main() {
    setupLocale();
    int choice;
    while (true) {
        cout << "---------------------------------" << endl;
        cout << "|            Меню:              |" << endl;
        cout << "| 1. Алгоритм Ахо-Корасик       |" << endl;
        cout << "| 2. Алгоритм  Рабина-Карпа     |" << endl;
        cout << "| 3. Поиск с конечным автоматом |" << endl;
        cout << "| 4. Алгоритм Бойера-Мура       |" << endl;
        cout << "| 5. Запуск всех функций        |" << endl;
        cout << "| 0. Выход                      |" << endl;
        cout << "---------------------------------" << endl;
        choice = input_int_in_range("Выберете действие: ", 0, 5);
        cout << "-----------------------------" << endl;
        switch (choice) {
            case 1:
                run(function_by_Cheremshanov); 
                break;
            case 2:
                run(function_by_Muratov);      
                break;
            case 3:
                run(function_by_Fomenko); 
                break;
            case 4:
                run(function_by_Sannikov);
                break;
            case 5:
                cout << "\n" << "---------------------------------" << "\n" <<  "1. Алгоритм Ахо-Корасик" << "\n" << "---------------------------------" << endl;
                run(function_by_Cheremshanov); 
                cout << "\n" << "---------------------------------" << "\n" <<  "2. Алгоритм  Рабина-Карпа" << "\n" << "---------------------------------" << endl;
                run(function_by_Muratov);
                cout << "\n" <<"---------------------------------" << "\n" << "3. Поиск с конечным автоматом" << "\n" << "---------------------------------" << endl;
                run(function_by_Fomenko);
                cout << "\n" << "---------------------------------" << "\n" << "4. Алгоритм Бойера-Мура" << "\n" << "---------------------------------" << endl;
                run(function_by_Sannikov);
                break;
            case 0:
                cout << "Выход из программы." << endl;
                exit( 1 );
            default:
                cout << "Неверный выбор, попробуйте снова." << endl;
                break;
        }
    }
    return 0;
}