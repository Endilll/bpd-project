// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"

#pragma comment(lib, "rpcrt4.lib")
#include <windows.h>

#include "User.h"

using namespace std;

User::User(const string login,
           const string password,
           const string role) :
           login_ (login),
           role_  (role)          
{
    passwordSalt_ = generateSalt_();
    setPassword(password);
}

string User::getLogin() const             { return login_;  }
void   User::setLogin(const string login) { login_ = login; }

string User::getRole() const            { return role_; }
void   User::setRole(const string role) { role_ = role; }

void User::setPassword(const string password) {
    password_ = hashSha512(password + "+" + passwordSalt_);
}

bool User::isPasswordCorrect(const string enteredPassword) const {
    if (password_ == hashSha512(enteredPassword + "+" + passwordSalt_))
        return true;
    else
        return false;
}

string User::generateSalt_()
{
    UUID uuid;
    RPC_CSTR uuidText;
    string uuidString;
    UuidCreate(&uuid);
    UuidToStringA(&uuid, &uuidText);
    uuidString = reinterpret_cast<char *>(uuidText);
    RpcStringFreeA(&uuidText);
    return uuidString;
}

string User::hashSha512(const string string)
{
    BCRYPT_ALG_HANDLE bcryptProvider;           // hAlg
    BCRYPT_HASH_HANDLE hashHandle;              // hHash
    unsigned char *hash;                        // pbHash
    unsigned long hashLength = 0;               // cbHash
    unsigned char *hashObject;                  // pbHashObject
    unsigned long hashObjectLength = 0;         // cbHashObject
    unsigned long lengthOfHashObjectLength = 0; // cbData  

    BCryptOpenAlgorithmProvider(&bcryptProvider,
                                BCRYPT_SHA512_ALGORITHM,
                                nullptr,
                                NULL);
    BCryptGetProperty(bcryptProvider,
                      BCRYPT_OBJECT_LENGTH,
                      (PBYTE)&hashObjectLength,
                      sizeof(unsigned long),
                      &lengthOfHashObjectLength,
                      NULL);
    hashObject = (PBYTE)HeapAlloc(GetProcessHeap(), NULL, hashObjectLength);
    BCryptGetProperty(bcryptProvider,
                      BCRYPT_HASH_LENGTH,
                      (PBYTE)&hashLength,
                      sizeof(unsigned long),
                      &lengthOfHashObjectLength,
                      NULL);
    hash = (PBYTE)HeapAlloc(GetProcessHeap(), NULL, hashLength);
    BCryptCreateHash(bcryptProvider,
                     &hashHandle,
                     hashObject,
                     hashObjectLength,
                     nullptr,
                     NULL,
                     NULL);
    BCryptHashData(hashHandle,
                   (PBYTE)string.c_str(),
                   string.length(),
                   NULL);
    BCryptFinishHash(hashHandle,
                     hash,
                     hashLength,
                     NULL);

    std::string hashedString(reinterpret_cast<char *>(hash), hashLength);

    BCryptCloseAlgorithmProvider(bcryptProvider, NULL);
    BCryptDestroyHash(hashHandle);
    HeapFree(GetProcessHeap(), 0, hashObject);
    HeapFree(GetProcessHeap(), NULL, hash);

    return hashedString;
}


