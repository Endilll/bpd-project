#pragma once

#include <vector>
#include <unordered_map>

#include "User.h"

using namespace std;

static class Users {
public:
    void add(const string &login,
             const string &password,
             const string &role = "user");
    void remove(const string &login);
    User& get(const string &login);
    vector<pair<string, string>> listUsers();

private:
    unordered_map<string, User> users_;
} users;