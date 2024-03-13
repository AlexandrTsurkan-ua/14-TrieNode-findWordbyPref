#include <iostream>
#include "Myfunction.h"
#include <string>

using namespace std;


int chekChoose(int a, int b) // ������� �������� �������� ������ ������ ����
{
    int i; //������� �����
    string str;// �������� ������
    do
    {
        i = 1;
        cout << "�������� ���� �����:" << endl;
        if (cin.peek() == '\n')
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        getline(cin, str);

        if (str.find_first_not_of("0123456789") != std::string::npos)
        {
            cout << "�������� ����� - ������� �����������. ���������� ��� ���!" << endl;
            cout << "\n\n" << endl;
            i = 0;
            continue;
        }

        if (stoi(str) < a || stoi(str) > b) // �������� ��������(1, 2 ��� 3), ���� int
        {
            cout << "�������� ����� - ����������� ������ ������ �������� ���!" << endl;
            cout << "�������� �������� � ��������� ����� " << a << " � " << b << ". ���������� ��� ���!" << endl;
            cout << "\n\n" << endl;
            i = 0;
        }
    } while (i == 0);
    return stoi(str); // ���������� � int � ������� int

}