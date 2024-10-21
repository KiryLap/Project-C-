#include "utils.h"

using namespace std;

template <typename T>
T read_positive(const string &prompt, const string &error_message, const T max_value) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() ||
            (std::is_floating_point<T>::value ? value <= 0 : value < 0) ||
            value >= max_value) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << error_message << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            log("Введено значение: " + to_string(value));
            return value;
        }
    }
}

template double read_positive<double>(const string &prompt, const string &error_message, const double);
template int read_positive<int>(const string &prompt, const string &error_message, const int);

/*
 * Функция read_positive запрашивает у пользователя ввод положительного числа с учетом заданного предела max_value.
 * 
 * @param prompt: Строка, отображаемая пользователю в качестве запроса на ввод.
 * @param error_message: Сообщение об ошибке, которое выводится при некорректном вводе.
 * @param max_value: Максимально допустимое значение для ввода.
 * 
 * Возвращает введенное пользователем значение типа T, если оно является положительным и меньше max_value.
 * В случае некорректного ввода (например, отрицательное число, ноль или число больше max_value) 
 * функция продолжает запрашивать ввод до получения корректного значения.
 * Пример использования: 
 * totalShops = read_positive<int>("Введите количество цехов: ", "Ошибка! Количество цехов должно быть неотрицательным числом. Попробуйте снова.");
 * efficiency = read_positive<double>("Введите эффективность в % (1-100): ","Ошибка! Эффективность должна быть неотрицательным числом и меньше 100. Попробуйте снова.",101 );
 */

long number_or_default(const std::string &input, long default_value, size_t min_length) {
    if (input.length() < min_length || 
        input.empty() || 
        std::find_if(input.begin(), input.end(), [](unsigned char c) { return !isdigit(c); }) != input.end()) {
        return default_value;
    }
    return strtol(input.c_str(), nullptr, 10);
}

/* 
 * Функция number_or_default принимает строку input, значение default_value и минимальную длину min_length.
 * Если строка input пустая, имеет длину менее min_length или содержит недопустимые символы (не цифры), 
 * функция возвращает default_value. Если input валидна, функция преобразует строку в целое число типа long 
 * и возвращает это значение.
 *
 * @param input: Строка, которую нужно проверить и преобразовать.
 * @param default_value: Значение, возвращаемое в случае ошибки проверки.
 * @param min_length: Минимально допустимая длина строки input.
 * @return: Преобразованное целое число типа long или default_value при ошибке.
 */

int input_int_in_range(const string &prompt, int min_value, int max_value) {
    int value;

    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value) {
            if (ss.eof()) {
                if (value >= min_value && value <= max_value) {
                    return value;
                } else {
                    cout << "----------------------------------------" << endl;
                    cout << "Ошибка: введите число от " << min_value << " до " << max_value << "." << endl;
                    cout << "----------------------------------------" << endl;
                }
            } else {
                cout << "---------------------------------------" << endl;
                cout << "Ошибка: введите корректное целое число." << endl;
                cout << "----------------------------------------" << endl;
            }
        } else {
            cout << "----------------------------------------" << endl;
            cout << "Ошибка: введите корректное целое число." << endl;
            cout << "----------------------------------------" << endl;
        }
    }
}

/* 
 * Функция input_int_in_range запрашивает у пользователя ввод целого числа в заданном диапазоне 
 * от min_value до max_value. 
 * 
 * @param prompt: Строка, отображаемая пользователю в качестве запроса на ввод.
 * @param min_value: Минимально допустимое значение для ввода.
 * @param max_value: Максимально допустимое значение для ввода. 
 * 
 * Если ввод некорректен (не является целым числом или выходит за пределы диапазона), 
 * функция повторно запрашивает ввод и выводит соответствующее сообщение об ошибке 
 * до получения корректного значения.
 * Пример использования: 
 * int choice;
 * choice = input_int_in_range("Выберете действие: ", 0, 4);
 */