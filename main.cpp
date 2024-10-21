#include <iostream>
#include "Cheremshanov/functions1_by_Cheremshanov.h"
#include "Muratov/functions2_by_Muratov.h"
#include "Fomenko/functions3_by_Fomenko.h"
#include "Sannikov/functions4_by_Sannikov.h"

// Шаблонная функция для измерения времени выполнения другой функции
template <typename Func>
void measure_time(Func function, const string& text, const string& pattern) {
    auto start = chrono::high_resolution_clock::now();
    function(text, pattern);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Время выполнения: " << duration.count() << " сек." << endl;
}

void run(void(*test_function)(const string&, const string&)) {
    string text;
    string pattern;

    // Тест 1: Текст и шаблон из примера
    text = "Это пример текста с шаблоном.";
    pattern = "шаблоном";
    cout << "Тест 1: ";
    measure_time(test_function, text, pattern);

    // Тест 2: Шаблон присутствует несколько раз
    text = "Шаблон шаблон шаблон.";
    pattern = "шаблон";
    cout << "Тест 2: ";
    measure_time(test_function, text, pattern);

    // Тест 3: Шаблон отсутствует
    text = "Это некоторый текст.";
    pattern = "несуществующий шаблон";
    cout << "Тест 3: ";
    measure_time(test_function, text, pattern);

    // Тест 4: Шаблон совпадает с текстом
    text = "Совпадаем.";
    pattern = "Совпадаем.";
    cout << "Тест 4: ";
    measure_time(test_function, text, pattern);

    // Тест 5: Пустой текст и непустой шаблон
    text = "";
    pattern = "шаблон";
    cout << "Тест 5: ";
    measure_time(test_function, text, pattern);

    // Тест 6: Непустой текст и пустой шаблон
    text = "Текст.";
    pattern = "";
    cout << "Тест 6: ";
    measure_time(test_function, text, pattern);

    // Тест 7: Пустой текст и пустой шаблон
    text = "";
    pattern = "";
    cout << "Тест 7: ";
    measure_time(test_function, text, pattern);

    // Тест 8: Текст и шаблон содержат повторяющиеся символы
    text = "аааабbbbбccccсаждм";
    pattern = "bbb";
    cout << "Тест 8: ";
    measure_time(test_function, text, pattern);

    // Тест 9: Большой текст и короткий шаблон
    text = string(10000, 'a') + "шаблон" + string(10000, 'a');
    pattern = "шаблон";
    cout << "Тест 9: ";
    measure_time(test_function, text, pattern);

    // Тест 10: Короткий текст и длинный шаблон
    text = "Тек";
    pattern = string(10000, 'a');
    cout << "Тест 10: ";
    measure_time(test_function, text, pattern);
}

int main() {
    int choice;
    while (true) {
        cout << "-----------------------------" << endl;
        cout << "|            Меню:          |" << endl;
        cout << "| 1. Функция Дмитрия        |" << endl;
        cout << "| 2. Функция Эдуарда        |" << endl;
        cout << "| 3. Функция Максима        |" << endl;
        cout << "| 4. Функция Захара         |" << endl;
        cout << "| 5. Запуск всех функций    |" << endl;
        cout << "| 0. Выход                  |" << endl;
        cout << "-----------------------------" << endl;
        choice = input_int_in_range("Выберете действие: ", 0, 4);
        cout << "-----------------------------" << endl;
        switch (choice) {
            case 1:
                run(fun1);
                break;
            case 2:
                run(fun2);
                break;
            case 3:
                run(fun3);
                break;
            case 4:
                run(fun4);
                break;
            case 5:
                run(fun1);
                run(fun2);
                run(fun3);
                run(fun4);
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