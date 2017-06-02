#pragma once

#include <string>

using namespace std;

class Subscriber {
public:
	Subscriber(const string    &fullName,
			   const long long &number,
			   const long long &year,
			   const string    &plan);

	string    getFullName() const;

	long long getNumber() const;
	void	  setNumber(long long &number);

	long long getYear() const;

	string    getPlan() const;
	void      setPlan(string &plan);

private:
	const string    fullName_;
	      long long number_;
	const long long year_;
	      string    plan_;
};