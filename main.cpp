#include <iostream>
#include <chrono>
#include "Verification/utils.h"
#include "Cheremshanov/functions1_by_Cheremshanov.h"
#include "Muratov/functions2_by_Muratov.h"
#include "Fomenko/functions3_by_Fomenko.h"
#include "Sannikov/functions4_by_Sannikov.h"

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
        { "шаблон" + string(1000000, 'a'), "шаблон" }, // Тест 1
        { string(1000000, 'a') + "шаблон", "шаблон" }, // Тест 2
        { "шаблон" + string(5000, 'a') + "шаблон" + string(5000, 'b') + "шаблон", "шаблон" }, // Тест 3
        { string(20000, 'x'), "шаблон" }, // Тест 4
        { "шаблон", "шаблон" }, // Тест 5
        { "", "шаблон" }, // Тест 6
        { "Текст.", "" }, // Тест 7
        { "aaaaabbbbcccccdddddeeeee", "bb" }, // Тест 8
        { string(10000, 'a') + "шаблон" + string(10000, 'a'), "шаблон" }, // Тест 9
        { "Тек", string(10000, 'a') } // Тест 10
    };

    // Проход по всем тестам и выполнение их
    for (size_t i = 0; i < tests.size(); ++i) {
        const string& text = tests[i].first;
        const string& pattern = tests[i].second;
        cout << "Тест " << (i + 1) << ": ";
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
                run(functions1_by_Cheremshanov); 
                break;
            case 2:
                run(functions2_by_Muratov);      
                break;
            case 3:
                run(functions_by_Fomenko); 
                break;
            case 4:
                run(functions4_by_Sannikov);
                break;
            case 5:
                cout << "1. Алгоритм Ахо-Корасик" << endl;
                run(functions1_by_Cheremshanov); 
                cout << "2. Алгоритм  Рабина-Карпа" << endl;
                run(functions2_by_Muratov);
                cout << "3. Поиск с конечным автоматом" << endl;  
                run(functions_by_Fomenko);
                cout << "4. Алгоритм Бойера-Мура" << endl;
                run(functions4_by_Sannikov);
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