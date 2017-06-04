// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

// bpd-project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <windows.h>

#include "Commands.h"
#include "Subscribers.h"
#include "Users.h"
#include "Utilities.h"

using namespace std;

User& login() {
    string login;
    do {
        login.clear();
        cout << "��� ������������: ";
        cin >> login;
        try {
            users.get(login);
        } catch (string &errorMessage) {
            cout << errorMessage << endl;
            continue;
        }

        string password;
        cout << "������: ";
        SetStdinEcho(false);
        cin >> password;
        SetStdinEcho();
        
        if (users.get(login).isPasswordCorrect(password) == false) {
            cout << "�������� ������" << endl;
            Sleep(1);
            continue;
        }
        break;
    } while (true);
    return users.get(login);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    users.loadFromFile("users.yaml");

    User& currentUser = login();
    //User& currentUser = users.get("admin");
    //subscribers.loadFromFile("subscribers.yaml");

    while (true) {
        system("cls");
        long long command = 0;
        if (currentUser.getRole() == "admin") {
            do {
                cout << "���������� �������� �������� �������������:" << endl;
                cout << "1. ����������� ������� ������� �������" << endl;
                cout << "2. ����������� ����� ������� ������" << endl;
                cout << "3. ������������� ������� ������" << endl;
                cout << "4. ������� ������� ������" << endl;
                cout << endl;
                cout << "������ � ������ ���������:" << endl;
                cout << "5. ��������� ���� ���������" << endl;
                cout << "6. ��������� ���� ���������" << endl;
                cout << endl;
                cout << "������ � ����������:" << endl;
                cout << "7. ����������� ������� ���������" << endl;
                cout << "8. ����������� ��������" << endl;
                cout << "9. ������������� ��������" << endl;
                cout << "10. ��������� ��������" << endl;
                cout << "11. ����� ��������" << endl;
                cout << "12. ��������� �������������� �������" << endl;
                cout << endl;
                cout << "13. �����" << endl;

                cin >> command;
            } while (!(command >= 1 && command <= 13));

            if (command == 13)
                break;

        } else if (currentUser.getRole() == "user") {
            do {
                cout << "������ � ������ ���������:" << endl;
                cout << "1. ��������� ���� ���������" << endl;
                cout << endl;
                cout << "������ � ����������:" << endl;
                cout << "2. ����������� ������� ���������" << endl;
                cout << "3. ����� ��������" << endl;
                cout << "4. ��������� �������������� �������" << endl;
                cout << endl;
                cout << "5. �����" << endl;

                cin >> command;
            } while (!(command >= 1 && command <= 5));

            if (command == 5)
                break;
        }
        commands.invoke(currentUser.getRole(), command);
    }
	return 0;
}