// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"

#include "sha3.h"
#pragma comment(lib, "rpcrt4.lib")
#include <windows.h>

#include "User.h"

using namespace std;

User::User(const string &login,
           const string &password,
           const string &role) :
           login_ (login),
           role_  (role)          
{
    passwordSalt_ = generateSalt_();
    setPassword(password);
}

string User::getLogin() const            { return login_;  }

string User::getRole()  const            { return role_; }
void   User::setRole(const string &role) { role_ = role; }

void User::setPassword(const string &password)
{
    SHA3 Sha3(SHA3::Bits512);
    passwordSalt_ = generateSalt_();
    password_ = Sha3(password + "+" + passwordSalt_);
}

bool User::isPasswordCorrect(const string &enteredPassword) const
{
    SHA3 Sha3(SHA3::Bits512);
    if (password_ == Sha3(enteredPassword + "+" + passwordSalt_))
        return true;
    else
        return false;
}

string User::generateSalt_()
{
    UUID uuid;
    RPC_CSTR uuidText;
    UuidCreate(&uuid);
    UuidToStringA(&uuid, &uuidText);
    string uuidString = reinterpret_cast<char *>(uuidText);
    RpcStringFreeA(&uuidText);
    return uuidString;
}