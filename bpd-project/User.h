#pragma once

#include <string>

using namespace std;

class User {
public:
    User(const string &login,
         const string &password,
         const string &role = "user");

    string getLogin() const;
    void   setLogin(const string &login);

    string getRole() const;
    void   setRole(const string &role);

    void   setPassword      (const string &password);
    bool   isPasswordCorrect(const string &password) const;
           
private:
    string login_;
    string password_;
    string passwordSalt_;
    string role_;

    static string generateSalt_();
};