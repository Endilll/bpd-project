#pragma once

#include <string>

using namespace std;

class Subscriber {
public:
	Subscriber(string          fullName,
			   long long       number,
			   const long long year,
			   string          plan     );

	string getFullName();
	void   setFullName(string fullName);

	long long getNumber();
	void	  setNumber(long long number);

	const long long getYear();

	string getPlan();
	void   setPlan(string plan);

private:
	string          fullName_;
	long long       number_;
	const long long year_;
	string          plan_;
};