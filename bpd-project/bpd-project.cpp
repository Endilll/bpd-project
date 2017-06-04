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

bool DATABASE_LOADED = false;

User& login() {
    string login;
    do {
        system("cls");

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
        //SetStdinEcho(false);
        cin >> password;
        //SetStdinEcho();
        
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
    /*try {
        users.add("admin", "admin");
        users.get("admin").setRole("admin");
        users.add("user", "user", "user");
        users.add("root", "root", "admin");
    } catch (string &errorMessage) {
        cout << errorMessage << endl;
    }*/
    users.loadFromFile("users.yaml");

    User& currentUser = login();

    long long command;
    auto askForCommand = [&command, &currentUser] {
        if (currentUser.getRole() == "admin") {
            do {
                system("cls");
                cout << "Управление учетными записями пользователей:" << endl;
                cout << "1. Просмотр списка учетных записей" << endl;
                cout << "2. Добавление новой учетной записи" << endl;
                cout << "3. Редактирование учетной записи" << endl;
                cout << "4. Удаление учетной записи" << endl;
				cout << endl;
				cout << "Работа с файлом абонентов:" << endl;
				cout << "5. Загрузить" << endl;
				cout << "6. Сохранить" << endl;
				cout << endl;
				cout << "Работа с абонентами:" << endl;
				cout << "7. Просмотр списка абонентов" << endl;
				cout << "8. Добавление абонента" << endl;
				cout << "9. Редактирование абонента" << endl;
				cout << "10. Удаление абонента" << endl;
				cout << "11. Найти абонента" << endl;
				cout << "12. Индивидуальное задание" << endl;
				cout << endl;
				cout << "13. Выход" << endl;
				
                cin >> command;
			} while (!(command >= 1 && command <= 13));
        }
    };

	do {
		askForCommand();

		switch (command) {
		case 1:
			commands.printUsers();
			break;
		case 2:
			commands.addUser();
			break;
		case 3:
			commands.editUser();
			break;
		case 4:
			commands.removeUser();
			break;	
		case 5:
			commands.loadSubscribers();
			break;
		case 6:
			commands.saveSubscribers();
			break;
		case 7:
			commands.printSubscribers();
			break;
		case 8:
			commands.addSubscriber();
			break;
		case 9:
			commands.editSubscriber();
			break;
		case 10:
			commands.removeSubscriber();
			break;
		case 11:
			commands.findSubscriber();
			break;
		case 12:
			commands.doIndividual();
			break;
		}
	} while (command != 13);
	return 0;
}

