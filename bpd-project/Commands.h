#pragma once

#include <string>
#include <vector>

using namespace std;

static class Commands
{
public:
    void printUsers() const;
    void addUser() const;
    void editUser() const;
    void removeUser() const;

	void loadSubscribers() const;
	void saveSubscribers() const;

	void printSubscribers() const;
	void addSubscriber() const;
	void editSubscriber() const;
	void removeSubscriber() const;
	void findSubscriber() const;
	void doIndividual() const;

private:
	void		   returnToMenu		    (const string &message = "") const;
	vector<size_t> calculateColumnWidths(const vector<vector<string>> &data) const;
	void		   printVectorOfVectors (const vector<vector<string>> &data) const;
	void		   printVectorOfVectors (const vector<vector<string>> &data, const vector<size_t> &columnWidths) const;
} commands;

