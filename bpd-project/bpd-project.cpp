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
        cout << "Имя пользователя: ";
        cin >> login;
        try {
            users.get(login);
        } catch (string &errorMessage) {
            cout << errorMessage << endl;
            continue;
        }

        string password;
        cout << "Пароль: ";
        SetStdinEcho(false);
        cin >> password;
        SetStdinEcho();
        
        if (users.get(login).isPasswordCorrect(password) == false) {
            cout << "Неверный пароль" << endl;
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
                cout << "Управление учетными записями пользователей:" << endl;
                cout << "1. Просмотреть спискок учетных записей" << endl;
                cout << "2. Добавленить новую учетную запись" << endl;
                cout << "3. Редактировать учетную запись" << endl;
                cout << "4. Удалить учетную запись" << endl;
                cout << endl;
                cout << "Работа с файлом абонентов:" << endl;
                cout << "5. Загрузить файл абонентов" << endl;
                cout << "6. Сохранить файл абонентов" << endl;
                cout << endl;
                cout << "Работа с абонентами:" << endl;
                cout << "7. Просмотреть спискок абонентов" << endl;
                cout << "8. Добавленить абонента" << endl;
                cout << "9. Редактировать абонента" << endl;
                cout << "10. Удаленить абонента" << endl;
                cout << "11. Найти абонента" << endl;
                cout << "12. Выполнить индивидуальное задание" << endl;
                cout << endl;
                cout << "13. Выход" << endl;

                cin >> command;
            } while (!(command >= 1 && command <= 13));

            if (command == 13)
                break;

        } else if (currentUser.getRole() == "user") {
            do {
                cout << "Работа с файлом абонентов:" << endl;
                cout << "1. Загрузить файл абонентов" << endl;
                cout << endl;
                cout << "Работа с абонентами:" << endl;
                cout << "2. Просмотреть спискок абонентов" << endl;
                cout << "3. Найти абонента" << endl;
                cout << "4. Выполнить индивидуальное задание" << endl;
                cout << endl;
                cout << "5. Выход" << endl;

                cin >> command;
            } while (!(command >= 1 && command <= 5));

            if (command == 5)
                break;
        }
        commands.invoke(currentUser.getRole(), command);
    }
	return 0;
}