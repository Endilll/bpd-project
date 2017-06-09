// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Commands.h"

#include <algorithm>
#include <conio.h>
#include <iomanip>
#include <iostream>

#include "Subscribers.h"
#include "Users.h"
#include "Utilities.h"

using namespace std;

map<string, vector<void(*)()>> Commands::commands_{
    make_pair("admin", vector<void(*)()> { &Commands::printUsers,
                                           &Commands::addUser,
                                           &Commands::editUser,
                                           &Commands::removeUser,
                                           &Commands::loadSubscribers,
                                           &Commands::saveSubscribers,
                                           &Commands::printSubscribers,
                                           &Commands::addSubscriber,
                                           &Commands::editSubscriber,
                                           &Commands::removeSubscriber,
                                           &Commands::findSubscriber,
                                           &Commands::doIndividual }),

    make_pair("user", vector<void(*)()>  { &Commands::loadSubscribers,
                                           &Commands::printSubscribers,
                                           &Commands::findSubscriber,
                                           &Commands::doIndividual })
};

void Commands::invoke(const string &role, const long long &command) {
    commands_[role][command - 1]();
}

void Commands::printUsers() {
    system("cls");
    cout << "Список всех пользователей:" << endl;

    printVectorOfVectors(users.listUsers());

    cout << endl;
	returnToMenu();
}

void Commands::addUser() {
    long long command;
    auto askForCommand = [&command]() {
        cout << "1. Добавить пользователя" << endl;
        cout << "2. Вернуться в меню" << endl;
        do {
            cin >> command;
        } while (!(command >= 1 && command <= 2));
    };

    do {
        system("cls");
        cout << "Добавление нового пользователя" << endl;

        string login;
        string password;
        string passwordCheck;
        string role;

        cout << "Имя пользователя: " << endl;
        ws(cin);
        getline(cin, login);
        SetStdinEcho(false);
        cout << "Пароль: " << endl;
        ws(cin);
        getline(cin, password);
        cout << "Проверка пароля: " << endl;
        ws(cin);
        getline(cin, passwordCheck);
        SetStdinEcho();
        cout << "Роль: " << endl;
        ws(cin);
        getline(cin, role);
        cout << endl;

        if (password != passwordCheck) {
            cout << "Пользователь не создан: пароль и проверка пароля не совпадают";
            askForCommand();
            continue;
        }
        try {
             users.add(login, password, role);
        } catch (string &errorMessage) {
            cout << "Пользователь не создан: " << errorMessage << endl;
        }

        askForCommand();
    } while (command != 2);
}

void Commands::editUser() {
    long long command;
    auto askForCommand = [&command]() {
        cout << "1. Редактировать пользователя" << endl;
        cout << "2. Вернуться в меню" << endl;
        do {
            cin >> command;
        } while (!(command >= 1 && command <= 2));
    };

    do {
        system("cls");
        cout << "Редактирование пользователя" << endl;

        string login;
        cout << "Имя пользователя: ";
        ws(cin);
        getline(cin, login);
        try {
            users.get(login);
        } catch (string &errorMessage) {
            cout << errorMessage << endl;
            askForCommand();
            continue;
        }
        User &editedUser = users.get(login);

        long long action;
        cout << "1. Задать новый пароль" << endl;
        cout << "2. Изменить роль" << endl;
        cout << "3. Закончить работу с этим пользователем" << endl;
        do {
            cin >> action;
        } while (!(action >= 1 && action <= 3));

        cout << endl;

        switch (action) {
        case 1: {
            cout << "Изменение пароля" << endl;;

            string newPassword;
            string newPasswordCheck;

            SetStdinEcho(false);
            cout << "Пароль: " << endl;
            ws(cin);
            getline(cin, newPassword);
            cout << "Проверка пароля: " << endl;
            ws(cin);
            getline(cin, newPasswordCheck);
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
            cout << "Изменение роли" << endl;

            string newRole;
            cout << "Текущая роль: " << endl;
            cout << editedUser.getRole() << endl;
            cout << "Новая роль: " << endl;
            ws(cin);
            getline(cin, newRole);

            editedUser.setRole(newRole);
            cout << "Роль успешно изменена" << endl;
            break;
        }
        }

		askForCommand();
    } while (command != 2);
}

void Commands::removeUser() {
    long long command;
    auto askForCommand = [&command]() {
        cout << "1. Удалить пользователя" << endl;
        cout << "2. Вернуться в меню" << endl;
        do {
            cin >> command;
        } while (!(command >= 1 && command <= 2));
    };

    do {
        system("cls");
        cout << "Удаление пользователя" << endl;

        string login;
        cout << "Имя пользователя: ";
        ws(cin);
        getline(cin, login);
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


void Commands::loadSubscribers() {
	long long command;
	auto askForCommand = [&command]() {
		cout << "1. Загрузить файл" << endl;
		cout << "2. Вернуться в меню" << endl;
		do {
			cin >> command;
		} while (!(command >= 1 && command <= 2));
	};

	do {
		system("cls");
		cout << "Загрузка файла с абонентами" << endl;

		string path;
		cout << "Имя файла: ";
        ws(cin);
        getline(cin, path);

		try {
			subscribers.loadFromFile(path);
		} catch (string &errorMessage) {
			cout << errorMessage << endl;
			askForCommand();
			continue;
		}

		cout << "Файл успешно загружен" << endl;

		askForCommand();
	} while (command != 2);
}

void Commands::saveSubscribers() {
	system("cls");
	cout << "Сохранение файла с абонентами" << endl;

	string path;
	cout << "Имя файла: ";
    ws(cin);
    getline(cin, path);
		
	subscribers.saveToFile(path);
	cout << "Файл успешно сохранен" << endl;

	returnToMenu();
}


void Commands::printSubscribers() {
	long long command;
	auto askForCommand = [&command] {
		cout << "1. Отсортировать по ФИО" << endl;
		cout << "2. Отсортировать по номеру телефона" << endl;
		cout << "3. Отсортировать по году подключения" << endl;
		cout << "4. Отсортировать по тарифному плану" << endl;
		cout << "5. Вернуться в меню" << endl;
		do {
			cin >> command;
		} while (!(command >= 1 && command <= 5));
	};

	auto compareByNumber = [](const vector<string> &a, const vector<string> &b) { return a[1] < b[1]; };
	auto compareByYear   = [](const vector<string> &a, const vector<string> &b) { return a[2] < b[2]; };
	auto compareByPlan   = [](const vector<string> &a, const vector<string> &b) { return a[3] < b[3]; };

	system("cls");
    cout << "Список всех абонентов:" << endl;

	auto subscribersList = subscribers.listSubscribers();
	if (subscribersList.size() == 0) {
		returnToMenu("Абоненты отсутствуют");
		return;
	}

	auto columnWidths = calculateColumnWidths(subscribersList);

	do {
		askForCommand();
        system("cls");

        auto sortedSubscribersList = subscribersList;
		switch (command) {
		case 1:	break;
		case 2: stable_sort(sortedSubscribersList.begin(), sortedSubscribersList.end(), compareByNumber); break;
		case 3: stable_sort(sortedSubscribersList.begin(), sortedSubscribersList.end(), compareByYear);   break;
		case 4: stable_sort(sortedSubscribersList.begin(), sortedSubscribersList.end(), compareByPlan);   break;
		case 5: continue; break;
		}

        printVectorOfVectors(sortedSubscribersList, columnWidths);
        cout << endl;
	} while (command != 5);
}

void Commands::addSubscriber() {
	long long command;
	auto askForCommand = [&command] {
		cout << "1. Добавить абонента" << endl;
		cout << "2. Вернуться в меню" << endl;
		do {
			cin >> command;
		} while (!(command >= 1 && command <= 2));
	};

	do {
		system("cls");
		cout << "Добавление нового абонента" << endl;

		string fio;
		long long number;
		long long year;
		string plan;

		cout << "ФИО: " << endl;
        ws(cin);
        getline(cin, fio);
		cout << "Номер телефона: " << endl;
		cin >> number;
		cout << "Год: " << endl;
		cin >> year;
        cout << "Тарифный план: " << endl;
        ws(cin);
        getline(cin, plan);
		cout << endl;

		try {
			subscribers.add(fio, number, year, plan);
		} catch (string &errorMessage) {
			cout << "Абонент не добавлен: " << errorMessage << endl;
		}

		askForCommand();
	} while (command != 2);
}

void Commands::editSubscriber() {
	long long command;
	auto askForCommand = [&command]() {
		cout << "1. Редактировать абонента" << endl;
		cout << "2. Вернуться в меню" << endl;
		do {
			cin >> command;
		} while (!(command >= 1 && command <= 2));
	};

	do {
		system("cls");
		cout << "Редактирование абонента" << endl;

		string fio;
		cout << "ФИО: ";
        ws(cin);
        getline(cin, fio);
		try {
			subscribers.get(fio);
		} catch (string &errorMessage) {
			cout << errorMessage << endl;
			askForCommand();
			continue;
		}
		Subscriber &editedSubscriber = subscribers.get(fio);

		long long action;
		cout << "1. Изменить номер" << endl;
		cout << "2. Изменить тарифный план" << endl;
		cout << "3. Закончить работу с этим пользователем" << endl;
		do {
			cin >> action;
		} while (!(action >= 1 && action <= 3));

		cout << endl;

		switch (action) {
		case 1: {
            cout << "Изменение номера" << endl;;

			long long newNumber;

            cout << "Текущий номер: " << endl;
            cout << editedSubscriber.getNumber() << endl;
			cout << "Новый номер: " << endl;
			cin >> newNumber;

			editedSubscriber.setNumber(newNumber);
			cout << "Номер успешно изменен" << endl;
            cout << endl;
			break;
		}
		case 2: {
			cout << "Изменение тарифного плана" << endl;;

			string newPlan;
            cout << "Текущий тарифный план: " << endl;
            cout << editedSubscriber.getPlan() << endl;
			cout << "Новый тарифный план: " << endl;
            ws(cin);
            getline(cin, newPlan);

			editedSubscriber.setPlan(newPlan);
			cout << "Тарифный план успешно изменен" << endl;
            cout << endl;
			break;
		}
		}

		askForCommand();
	} while (command != 2);
}

void Commands::removeSubscriber() {
	long long command;
	auto askForCommand = [&command]() {
		cout << "1. Удалить абонента" << endl;
		cout << "2. Вернуться в меню" << endl;
		do {
			cin >> command;
		} while (!(command >= 1 && command <= 2));
	};

	do {
		system("cls");
		cout << "Удаление абонента" << endl;

		string fio;
		cout << "ФИО абонента: ";
        ws(cin);
        getline(cin, fio);
		try {
			subscribers.get(fio);
			subscribers.remove(fio);
		} catch (string &errorMessage) {
			cout << errorMessage << endl;
			askForCommand();
			continue;
		}

		cout << "Абонент успешно удален" << endl;

		askForCommand();
	} while (command != 2);
}

void Commands::findSubscriber() {
	long long command;
	auto askForCommand = [&command]() {
		cout << "1. Найти абонента" << endl;
		cout << "2. Вернуться в меню" << endl;
		do {
			cin >> command;
		} while (!(command >= 1 && command <= 2));
	};

	do {
		system("cls");
		cout << "Поиск абонента" << endl;

		string searchString;
		cout << "Найти: ";
        ws(cin);
        getline(cin, searchString);

		vector<vector<string>> searchResults = subscribers.find(searchString);
		if (searchResults.size() == 0) {
			cout << "Ничего не найдено" << endl;
			askForCommand();
			continue;
		}

		cout << searchResults.size() << " результатов" << endl;
		printVectorOfVectors(searchResults);

		askForCommand();
	} while (command != 2);
}

void Commands::doIndividual() {
	long long command;
	auto askForCommand = [&command]() {
		cout << "1. Индивидуальное задание" << endl;
		cout << "2. Вернуться в меню" << endl;
		do {
			cin >> command;
		} while (!(command >= 1 && command <= 2));
	};

	do {
		system("cls");
		cout << "Индивидуальное задание: подсчитать и вывести на экран абонентов,\n подключенных с определенного года" << endl;

		long long year;
		cout << "Введите год: ";
		cin >> year;

		auto subscribersList = subscribers.listSubscribers();
		if (subscribersList.size() == 0) {
			returnToMenu("Абоненты отсутствуют");
			return;
		}

		auto compareByYear = [](const vector<string> &a, const vector<string> &b) { return a[2] < b[2]; };
		stable_sort(subscribersList.begin(), subscribersList.end(), compareByYear);

		auto firstMatch = lower_bound(subscribersList.begin(),
									  subscribersList.end(),
									  vector<string>(subscribersList[0].size(), to_string(year)),
									  compareByYear);
		if (firstMatch == subscribersList.end()) {
            cout << "Такие абоненты отсутствуют" << endl;
            askForCommand();
            continue;
		}

		printVectorOfVectors(vector<vector<string>>(firstMatch, subscribersList.end()));

		askForCommand();
	} while (command != 2);
}


void Commands::returnToMenu(const string &message) {
	if (!message.empty())
		cout << message << endl;
	cout << "Нажмите любую клавишу для возврата в меню" << endl;
	_getch();
}

vector<size_t> Commands::calculateColumnWidths(const vector<vector<string>> &data) {
	vector<size_t> columnWidths(data[0].size());
	for (size_t columnIndex = 0; columnIndex < columnWidths.size(); ++columnIndex)
		for (auto line : data)
			if (line[columnIndex].length() > columnWidths[columnIndex])
				columnWidths[columnIndex] = line[columnIndex].length();
	return columnWidths;
}

void Commands::printVectorOfVectors(const vector<vector<string>> &data) {
	printVectorOfVectors(data, calculateColumnWidths(data));
}

void Commands::printVectorOfVectors(const vector<vector<string>> &data, const vector<size_t> &columnWidths) {
    for (auto entry : data) {
        for (size_t column = 0; column < entry.size(); ++column)
            cout << left << setw(columnWidths[column]) << entry[column] << " ";
        cout << endl;
    }
}