#include <iostream>
#include "Myfunction.h"
#include <string>

using namespace std;


int chekChoose(int a, int b) // функция проверки верности выбора пункта меню
{
    int i; //счетчик цикла
    string str;// вводимая строка
    do
    {
        i = 1;
        cout << "Сделайте свой выбор:" << endl;
        if (cin.peek() == '\n')
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        getline(cin, str);

        if (str.find_first_not_of("0123456789") != std::string::npos)
        {
            cout << "Неверный выбор - символы недопустимы. Попробуйте еще раз!" << endl;
            cout << "\n\n" << endl;
            i = 0;
            continue;
        }

        if (stoi(str) < a || stoi(str) > b) // проверка значений(1, 2 или 3), если int
        {
            cout << "Неверный выбор - возможности выбора такого значения нет!" << endl;
            cout << "Выберите значение в диапазоне между " << a << " и " << b << ". Попробуйте еще раз!" << endl;
            cout << "\n\n" << endl;
            i = 0;
        }
    } while (i == 0);
    return stoi(str); // приведение к int и возврат int

}