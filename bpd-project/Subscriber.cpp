// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <string>

using namespace std;

class Subscriber {
public:
	Subscriber(string          fullName,
			   long long       number,
			   const long long year,
			   string          plan     )
				   : fullName_(fullName),
					 number_  (number),
					 year_    (year),
					 plan_    (plan)     {}

	string getFullName()				{ return fullName_;     }
	void   setFullName(string fullName) { fullName_ = fullName; }

	long long getNumber()				  { return number_;   }
	void	  setNumber(long long number) { number_ = number; }

	const long long getYear() { return year_; }

	string getPlan()			{ return plan_; }
	void   setPlan(string plan) { plan_ = plan; }

private:
	string          fullName_;
	long long       number_;
	const long long year_;
	string          plan_;
};