// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"

#include <vector>
#include <unordered_map>

#include "Users.h"

using namespace std;

void Users::add(const string login,
                const string password,
                const string role)
{
    if (users_.emplace(login, User(login, password, role)).second == false)
        throw string("User already exists");
}

void Users::remove(const string login)
{
    try {
        users_.erase(login);
    } catch (exception exception) {
        throw string("Failed to remove user");
    }
}

User& Users::getUser(const string login)
{
    try {
        return users_.at(login);
    } catch (exception exception) {
        throw string("User doesn't exists");
    }
}

vector<pair<string, string>> Users::listUsers()
{
    vector<pair<string, string>> users;
    users.reserve(users_.size());
    for (auto pair : users_)
        users.emplace_back(pair.second.getLogin(), pair.second.getRole());
    return users;
}