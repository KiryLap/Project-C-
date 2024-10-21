#include "utils.h"

using namespace std;

template <typename T>
T read_positive(const string &prompt, const string &errorMessage, const T maxValue) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() ||
            (std::is_floating_point<T>::value ? value <= 0 : value < 0) ||
            value >= maxValue) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMessage << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            log("Введено значение: " + to_string(value));
            return value;
        }
    }
}

template double readPositive<double>(const string &prompt, const string &errorMessage, const double);
template int readPositive<int>(const string &prompt, const string &errorMessage, const int);

/*
 * Функция readPositive запрашивает у пользователя ввод положительного числа с учетом заданного предела maxValue.
 * 
 * @param prompt: Строка, отображаемая пользователю в качестве запроса на ввод.
 * @param errorMessage: Сообщение об ошибке, которое выводится при некорректном вводе.
 * @param maxValue: Максимально допустимое значение для ввода.
 * 
 * Возвращает введенное пользователем значение типа T, если оно является положительным и меньше maxValue.
 * В случае некорректного ввода (например, отрицательное число, ноль или число больше maxValue) 
 * функция продолжает запрашивать ввод до получения корректного значения.
 * Пример использования: 
 * totalShops = readPositive<int>("Введите количество цехов: ", "Ошибка! Количество цехов должно быть неотрицательным числом. Попробуйте снова.");
 * efficiency = readPositive<double>("Введите эффективность в % (1-100): ","Ошибка! Эффективность должна быть неотрицательным числом и меньше 100. Попробуйте снова.",101 );
 */

long number_or_default(const std::string &input, long defaultValue, size_t minLength) {
    if (input.length() < minLength || 
        input.empty() || 
        std::find_if(input.begin(), input.end(), [](unsigned char c) { return !isdigit(c); }) != input.end()) {
        return defaultValue;
    }
    return strtol(input.c_str(), nullptr, 10);
}

/* 
 * Функция numberOrDefault принимает строку input, значение defaultValue и минимальную длину minLength.
 * Если строка input пустая, имеет длину менее minLength или содержит недопустимые символы (не цифры), 
 * функция возвращает defaultValue. Если input валидна, функция преобразует строку в целое число типа long 
 * и возвращает это значение.
 *
 * @param input: Строка, которую нужно проверить и преобразовать.
 * @param defaultValue: Значение, возвращаемое в случае ошибки проверки.
 * @param minLength: Минимально допустимая длина строки input.
 * @return: Преобразованное целое число типа long или defaultValue при ошибке.
 */

int input_int_in_range(const string &prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value) {
            if (ss.eof()) {
                if (value >= minValue && value <= maxValue) {
                    return value;
                } else {
                    cout << "----------------------------------------" << endl;
                    cout << "Ошибка: введите число от " << minValue << " до " << maxValue << "." << endl;
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
 * Функция inputIntInRange запрашивает у пользователя ввод целого числа в заданном диапазоне 
 * от minValue до maxValue. 
 * 
 * @param prompt: Строка, отображаемая пользователю в качестве запроса на ввод.
 * @param minValue: Минимально допустимое значение для ввода.
 * @param maxValue: Максимально допустимое значение для ввода. 
 * 
 * Если ввод некорректен (не является целым числом или выходит за пределы диапазона), 
 * функция повторно запрашивает ввод и выводит соответствующее сообщение об ошибке 
 * до получения корректного значения.
 * Пример использования: 
 * int choice;
 * choice = inputIntInRange("Выберете действие: ", 0, 4);
 */