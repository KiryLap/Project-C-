#include <iostream>
#include <chrono>
#include "Verification/utils.h"
#include "Cheremshanov/functions1_by_Cheremshanov.h"
#include "Muratov/functions2_by_Muratov.h"
#include "Fomenko/functions3_by_Fomenko.h"
#include "Sannikov/functions4_by_Sannikov.h"
#include <chrono>

void setupLocale() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
}

template <typename Func>
void measure_time(Func function, const string& text, const string& pattern) {
    auto start = chrono::high_resolution_clock::now();
    function(text, pattern);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Время выполнения: " << duration.count() << " сек." << endl;
}

void run(void(*test_function)(const string&, const string&)) {
    // Список тестов, каждый тест представлен парой строк
    vector<pair<string, string>> tests = {
        // Длинный текст, где шаблон находится в начале
        { "pattern" + string(1000000, 'a'), "pattern" }, // Тест 1

        // Длинный текст, где шаблон находится в конце
        { string(1000000, 'a') + "pattern", "pattern" }, // Тест 2

        // Шаблон с множеством повторений в длинном тексте
        { "pattern" + string(5000, 'a') + "pattern" + string(5000, 'b') + "pattern", "pattern" }, // Тест 3

        // Длинный текст без шаблона
        { string(20000, 'x'), "pattern" }, // Тест 4

        // Шаблон равен тексту
        { "pattern", "pattern" }, // Тест 5

        // Пустой текст
        { "", "pattern" }, // Тест 6

        // Пустой шаблон (не должен находить совпадений)
        { "Текст.", "" }, // Тест 7

        // Текст с разными символами, шаблон в середине
        { "aaaaabbbbcccccdddddeeeee", "bb" }, // Тест 8

        // Шаблон расположен в середине большого количества одинаковых символов
        { string(10000, 'a') + "pattern" + string(10000, 'a'), "pattern" }, // Тест 9

        // Шаблон отсутствует в длинном тексте
        { "Тек", string(10000, 'a') }, // Тест 10
        
        // Небольшой текст с многими повторами, где особенность Рабина-Карпа будет полезна
        { "aaaaaaaabaaaabaaaaaaa", "ab" }, // Тест 11

        // Сложный случай, где лучше работает Бойер-Мурным
        { "the quick brown fox jumps over the lazy dog", "fox" }, // Тест 12

        // Длинный текст с многоразовыми символами для теста на эффективность
        { string(50000, 'a') + "pattern" + string(50000, 'a'), "pattern" }, // Тест 13

        // Шаблон с уникальными символами и текст
        { "abcdefgabcdefgabcdefg", "cde" }, // Тест 14
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