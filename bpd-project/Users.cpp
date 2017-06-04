// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

#include "Users.h"

using namespace std;
using namespace YAML;

map<string, User> Users::users_;

void Users::add(const string &login,
                const string &password,
                const string &role)
{
    if (users_.emplace(login, User(login, password, role)).second == false)
        throw string("������������ � ����� ������ ��� ����������");
}

void Users::remove(const string &login)
{
    try {
        users_.erase(login);
    } catch (exception &exception) {
        throw string("�� ������� ������� ������������");
    }
}

User & Users::get(const string &login)
{
    try {
        return users_.at(login);
    } catch (exception &exception) {
        throw string("������������ �� ����������");
    }
}

vector<vector<string>> Users::listUsers()
{
    vector<vector<string>> users;
    users.reserve(users_.size());
    for (auto pair : users_)
        users.push_back({ pair.second.getLogin(),
                          pair.second.getRole() });
    return users;
}

void Users::saveToFile(const string &path) {
    Emitter emitter;
    emitter << BeginSeq;
    for (auto pair : users_) {
        emitter << Flow << pair.second.getAsVector();
    }
    emitter << EndSeq;

    ofstream file(path, ios::trunc);
    file << emitter.c_str();
}

void Users::loadFromFile(const string &path) {
	users_.clear();

	Node usersNode;
	try {
		usersNode = LoadFile(path);
	} catch (exception &exception) {
		throw string("���� �� ������");
	}

    for (auto userNode : usersNode) {
        User user(userNode.as<vector<string>>());
        users_.emplace(user.getLogin(), user);
    }
}