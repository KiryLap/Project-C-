#include <iostream>
#include "Dmitry/functions1.h"
#include "Edward/functions2.h"
#include "Maxim/functions3.h"
#include "Zakhar/functions4.h"

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
                functions1();
                break;
            case 2:
                functions2();
                break;
            case 3:
                functions3();
                break;
            case 4:
                functions4();
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