// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"

#include <array>
#include <map>
#include <vector>

#include "Subscribers.h"

using namespace std;

void Subscribers::add(const string    &fullName,
                      const long long &number,
                      const long long &year,
                      const string    &plan)
{
    if (subscribers_.emplace(fullName, Subscriber(fullName, number, year, plan)).second == false)
        throw string("Subscriber already exists");
}

void Subscribers::remove(const string &fullName)
{
    try {
        subscribers_.erase(fullName);
    } catch (exception &exception) {
        throw string("Failed to remove subscriber");
    }
}

Subscriber& Subscribers::getSubscriber(const string &fullName)
{
    try {
        return subscribers_.at(fullName);
    } catch (exception &exception) {
        throw string("Subscriber doesn't exists");
    }
}

vector<array<string, 4>> Subscribers::listSubscribers()
{
    vector<array<string, 4>> subscribers;
    subscribers.reserve(subscribers_.size());
    for (auto pair : subscribers_)
        subscribers.emplace_back(          pair.second.getFullName(),
                                 to_string(pair.second.getNumber()),
                                 to_string(pair.second.getYear()),
                                           pair.second.getPlan());
    return subscribers;
}

