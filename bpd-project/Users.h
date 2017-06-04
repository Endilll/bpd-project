#pragma once

#include <map>
#include <string>
#include <vector>

#include "User.h"

using namespace std;

static class Users {
public:
    void saveToFile  (const string &path);
    void loadFromFile(const string &path);

    void add(const string &login,
             const string &password,
             const string &role = "user");
    void remove(const string &login);
    User & get(const string &login);
    vector<pair<string, string>> listUsers();

private:
    map<string, User> users_;
} users;