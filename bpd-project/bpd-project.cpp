// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

// bpd-project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <windows.h>

#include "Commands.h"
#include "Subscriber.h"
#include "Users.h"
#include "Utilities.h"

using namespace std;


User& login() {
    string login;
    do {
        system("cls");

        login.clear();
        cout << "Имя пользователя: ";
        cin >> login;
        cout << endl;
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
        cout << endl;
        if (users.get(login).isPasswordCorrect(password) == false) {
            cout << "Неверный пароль" << endl;
            Sleep(1);
            continue;
        }
        system("cls");
        break;
    } while (true);
    return users.get(login);
}

int main()
{
    SetConsoleOutputCP(65001);
    try {
        users.add("admin", "admin");
        users.get("admin").setRole("admin");
        users.get("user");
    } catch (string &errorMessage) {
        cout << errorMessage << endl;
    }

    User& currentUser = login();
	return 0;
}

