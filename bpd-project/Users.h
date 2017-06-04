#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <windows.h>

#include "User.h"

using namespace std;

class Users {
public:
    static void saveToFile  (const string &path);
    static void loadFromFile(const string &path);

    static void add(const string &login,
                    const string &password,
                    const string &role = "user");
    static void remove(const string &login);
    static User & get(const string &login);
    static vector<vector<string>> listUsers();

private:
    static map<string, User> users_;
};

extern Users users;