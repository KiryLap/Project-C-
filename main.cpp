#include <iostream>
#include "Cheremshanov/functions1_by_Cheremshanov.h"
#include "Muratov/functions2_by_Muratov.h"
#include "Fomenko/functions3_by_Fomenko.h"
#include "Sannikov/functions4_by_Sannikov.h"

int main() {
    int choice;
    while (true) {
        cout << "-----------------------------" << endl;
        cout << "|            Меню:          |" << endl;
        cout << "| 1. Функция Дмитрия        |" << endl;
        cout << "| 2. Функция Эдуарда        |" << endl;
        cout << "| 3. Функция Максима        |" << endl;
        cout << "| 4. Функция Захара         |" << endl;
        cout << "| 0. Выход                  |" << endl;
        cout << "-----------------------------" << endl;
        choice = inputIntInRange("Выберете действие: ", 0, 4);
        cout << "-----------------------------" << endl;
        switch (choice) {
            case 1:
                fun1();
                break;
            case 2:
                fun2();
                break;
            case 3:
                fun3();
                break;
            case 4:
                fun4();
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