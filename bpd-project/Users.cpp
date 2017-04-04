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

vector<string> Users::listUsers()
{
    vector<string> logins;
    logins.reserve(users_.size());
    for (auto pair : users_)
        logins.push_back(pair.first);
    return logins;
}

User& Users::getUser(const string login)
{
    auto iterator = users_.find(login);
    if (iterator != users_.end())
        return iterator->second;
    else
        throw string("User doesn't exists");
}

