// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Commands.h"

#include <conio.h>
#include <iomanip>
#include <iostream>

#include "Users.h"
#include "Utilities.h"

using namespace std;

Commands::Commands() {}

Commands::~Commands() {}

void Commands::printUsers() {
    system("cls");
    cout << "Список всех пользователей:" << endl;

    auto usersList = users.listUsers();

    int loginMaxLength = 0;
    for (auto pair : usersList)
        if (pair.first.length() > loginMaxLength)
            loginMaxLength = pair.first.length();

    for (auto pair : usersList)
        cout << left << setw(loginMaxLength) << pair.first << " " << pair.second << endl;

    cout << endl;
    cout << "Нажмите любую клавишу для возврата в меню" << endl;
    _kbhit();
}

void Commands::addUser() {
    int command;
    auto askForCommand = [&command]() {
        cout << "1. Добавить пользователя" << endl;
        cout << "2. Вернуться в меню" << endl;
        do {
            cin >> command;
        } while (command != 1 &&
                 command != 2);
    };

    do {
        system("cls");
        cout << "Добавление нового пользователя" << endl;

        string login;
        string password;
        string passwordCheck;
        string role;

        cout << setw(27) << "Имя пользователя: ";
        cin >> login;
        SetStdinEcho(false);
        cout << setw(27) << "Пароль: ";
        cin >> password;
        cout << setw(27) << "Проверка пароля: ";
        cin >> passwordCheck;
        SetStdinEcho();
        cout << setw(27) << "Роль (по умолчанию user): ";
        cin >> role;
        cout << endl;

        if (password != passwordCheck) {
            cout << "Пользователь не создан: пароль и проверка пароля не совпадают";
            askForCommand();
            continue;
        }
        try {
            if (role.empty())
                users.add(login, password);
            else
                users.add(login, password, role);
        } catch (string &errorMessage) {
            cout << "Пользователь не создан: " << errorMessage << endl;
        }

        askForCommand();
    } while (command != 2);
}

void Commands::editUser() {
    int command;
    auto askForCommand = [&command]() {
        cout << "1. Редактировать пользователя" << endl;
        cout << "2. Вернуться в меню" << endl;
        do {
            cin >> command;
        } while (command != 1 &&
                 command != 2);
    };

    do {
        system("cls");
        cout << "Редактирование пользователя" << endl;

        string login;
        cout << "Имя пользователя: ";
        cin >> login;
        try {
            users.get(login);
        } catch (string &errorMessage) {
            cout << errorMessage << endl;
            askForCommand();
            continue;
        }
        User &editedUser = users.get(login);

        int action;
        cout << "1. Задать новый пароль" << endl;
        cout << "2. Изменить роль" << endl;
        cout << "3. Закончить работу с этим пользователем" << endl;
        do {
            cin >> action;
        } while (action != 1 &&
                 action != 2 &&
                 action != 3);

        cout << endl;

        switch (action) {
        case 1: {
            cout << "Изменение пароля";

            string newPassword;
            string newPasswordCheck;

            SetStdinEcho(false);
            cout << setw(17) << "Пароль: ";
            cin >> newPassword;
            cout << setw(17) << "Проверка пароля: ";
            cin >> newPasswordCheck;
            SetStdinEcho();

            if (newPassword != newPasswordCheck) {
                cout << "Пароль не изменен: новый пароль и его проверка не совпадают" << endl;
                askForCommand();
                continue;
            }

            editedUser.setPassword(newPassword);
            cout << "Пароль успешно изменен" << endl;
            break;
        }
        case 2: {
            cout << "Изменение роли";

            string newRole;
            cout << "Новая роль: ";
            cin >> newRole;

            editedUser.setRole(newRole);
            cout << "Роль успешно изменена";
            break;
        }
        case 3:
            askForCommand();
        }
    } while (command != 2);
}

void Commands::removeUser() {
    int command;
    auto askForCommand = [&command]() {
        cout << "1. Удалить пользователя" << endl;
        cout << "2. Вернуться в меню" << endl;
        do {
            cin >> command;
        } while (command != 1 &&
                 command != 2);
    };

    do {
        system("cls");
        cout << "Удаление пользователя" << endl;

        string login;
        cout << "Имя пользователя: ";
        cin >> login;
        try {
            users.get(login);
            users.remove(login);
        } catch (string &errorMessage) {
            cout << errorMessage << endl;
            askForCommand();
            continue;
        }

        cout << "Пользователь успешно удален" << endl;

        askForCommand();
    } while (command != 2);
}
