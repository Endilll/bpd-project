#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;

class Commands
{
public:
    static void invoke(const string &role, const long long &command);

private:
    static map<string, vector<void (*)()>> commands_;

    static void printUsers();
    static void addUser();
    static void editUser();
    static void removeUser();

    static void loadSubscribers();
    static void saveSubscribers();

    static void printSubscribers();
    static void addSubscriber();
    static void editSubscriber();
    static void removeSubscriber();
    static void findSubscriber();
    static void doIndividual();

	static void		      returnToMenu		   (const string &message = "");
	static vector<size_t> calculateColumnWidths(const vector<vector<string>> &data);
	static void		      printVectorOfVectors (const vector<vector<string>> &data);
	static void		      printVectorOfVectors (const vector<vector<string>> &data,
                                                const vector<size_t> &columnWidths);
};

extern Commands commands;