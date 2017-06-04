#pragma once

#include <string>
#include <vector>

using namespace std;

class Subscriber {
public:
	Subscriber(const string    &fullName,
			   const long long &number,
			   const long long &year,
			   const string    &plan);
    Subscriber(const vector<string> &fields);

	string    getFullName() const;

	long long getNumber() const;
	void	  setNumber(const long long &number);

	long long getYear() const;

	string    getPlan() const;
	void      setPlan(const string &plan);

    vector<string> getAsVector() const;

private:
	const string    fullName_;
	      long long number_;
	const long long year_;
	      string    plan_;
};