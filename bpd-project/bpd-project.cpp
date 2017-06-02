// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

// bpd-project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <windows.h>
#include "Subscriber.h"
#include "Users.h"

using namespace std;

void SetStdinEcho(bool enable = true) {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    if (enable)
        mode |= ENABLE_ECHO_INPUT;
    else
        mode &= ENABLE_ECHO_INPUT;
    SetConsoleMode(hStdin, mode);
}

int main()
{
    SetConsoleCP(65001);
    try {
        users.add("admin", "admin");
        users.getUser("admin").setRole("admin");
        users.getUser("user");
    } catch (string errorMessage) {
        cout << errorMessage << endl;
    }

    string login;
    string password;
    do {
        login.clear();
        password.clear();
        system("cls");

        cout << "Имя пользователя: ";
        cin >> login;
        cout << endl;
        try {
            users.getUser(login);
        } catch (string errorMessage) {
            cout << errorMessage << endl;
            continue;
        }

        cout << "Пароль: ";
        SetStdinEcho(false);
        cin >> password;
        SetStdinEcho();
        cout << endl;
        if (users.getUser(login).isPasswordCorrect(password) == false) {
            cout << "Неверный пароль" << endl;
            Sleep(1);
            continue;
        }
        system("cls");
        break;
    } while (true);
    User &currentUser = users.getUser(login);

	return 0;
}

