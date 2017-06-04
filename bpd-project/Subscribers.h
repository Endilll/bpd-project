#pragma once

#include <map>
#include <string>
#include <vector>

#include "Subscriber.h"

using namespace std;

class Subscribers {
public:
    static void saveToFile  (const string &path);
    static void loadFromFile(const string &path);

    static void add(const string    &fullName,
             const long long &number,
             const long long &year,
             const string    &plan);
    static void remove(const string &fullName);
    static vector<vector<string>> find(const string &searchString);
    static Subscriber & get(const string &fullName);
    static vector<vector<string>> listSubscribers();

private:
    static map<string, Subscriber> subscribers_;
};

extern Subscribers subscribers;