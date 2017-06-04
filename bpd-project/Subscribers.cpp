// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

#include "Subscribers.h"

using namespace std;
using namespace YAML;

map<string, Subscriber> Subscribers::subscribers_;

void Subscribers::add(const string    &fullName,
                      const long long &number,
                      const long long &year,
                      const string    &plan)
{
    if (subscribers_.emplace(fullName, Subscriber(fullName, number, year, plan)).second == false)
        throw string("Абонент с таким именем уже существует");
}

void Subscribers::remove(const string &fullName)
{
    try {
        subscribers_.erase(fullName);
    } catch (exception &exception) {
        throw string("Не удалось удалить абонента");
    }
}

Subscriber & Subscribers::get(const string &fullName)
{
    try {
        return subscribers_.at(fullName);
    } catch (exception &exception) {
        throw string("Абонент не существует");
    }
}

vector<vector<string>> Subscribers::find(const string &searchString) {
	vector<vector<string>> searchResults;

	if (searchString.find_first_not_of("0123456789") == string::npos) {
		long long searchNumber = stoll(searchString);
		for (auto pair : subscribers_) {
			Subscriber &subscriber = pair.second;
			if (searchNumber == subscriber.getNumber() ||
				searchNumber == subscriber.getYear())
				searchResults.push_back(subscriber.getAsVector());
		}
	} else
		for (auto pair : subscribers_) {
			Subscriber &subscriber = pair.second;
			if (searchString == subscriber.getFullName() ||
				searchString == subscriber.getPlan())
				searchResults.push_back(subscriber.getAsVector());
		}

	return searchResults;
}

vector<vector<string>> Subscribers::listSubscribers() {
    vector<vector<string>> subscribers;
    subscribers.reserve(subscribers_.size());
    for (auto pair : subscribers_)
        subscribers.push_back({           pair.second.getFullName(),
                                to_string(pair.second.getNumber()),
                                to_string(pair.second.getYear()),
                                          pair.second.getPlan()});
    return subscribers;
}

void Subscribers::saveToFile(const string &path) {
    Emitter emitter;
    emitter << BeginSeq;
    for (auto pair : subscribers_) {
        emitter << Flow << pair.second.getAsVector();
    }
    emitter << EndSeq;

    ofstream file(path, ios::trunc);
    file << emitter.c_str();
}

void Subscribers::loadFromFile(const string &path) {
	subscribers_.clear();

	Node subscribersNode;
	try {
		subscribersNode = LoadFile(path);
	} catch (exception &exception) {
		throw string("Файл не найден");
	}

	for (auto userNode : subscribersNode) {
		Subscriber subscriber(userNode.as<vector<string>>());
		subscribers_.emplace(subscriber.getFullName(), subscriber);
	}
}
