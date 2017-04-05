#pragma once

#include <array>
#include <map>
#include <vector>

#include "Subscriber.h"

using namespace std;

static class Subscribers {
public:
    void add(const string    fullName,
             const long long number,
             const long long year,
             const string    plan);
    void remove(const string fullName);
    Subscriber& getSubscriber(const string fullName);
    vector<array<string, 4>> listSubscribers();

private:
    map<string, Subscriber> subscribers_;
} subscribers;

