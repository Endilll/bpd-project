// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

// bpd-project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "Subscriber.h"
#include "Users.h"

using namespace std;

int main()
{
    try {
        users.add("admin", "admin");
        users.getUser("admin").setRole("admin");
        users.getUser("user");
    } catch (string errorMessage) {
        cout << errorMessage << endl;
    }
	return 0;
}

