// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"

#include "Subscriber.h"

using namespace std;

Subscriber::Subscriber(const string    &fullName,
			           const long long &number,
			           const long long &year,
			           const string    &plan) :
			           fullName_(fullName),
			           number_  (number),
			           year_    (year),
			           plan_    (plan) {}

Subscriber::Subscriber(const vector<string> &fields) :
                       fullName_      (fields[0]),
                       number_  (stoll(fields[1])),
                       year_    (stoll(fields[2])),
                       plan_          (fields[3]) {}

vector<string> Subscriber::getAsVector() const {
    return {           fullName_,
             to_string(number_),
             to_string(year_),
                       plan_ };
}

string    Subscriber::getFullName() const		         { return fullName_; }

long long Subscriber::getNumber()   const		         { return number_;   }
void	  Subscriber::setNumber(const long long &number) { number_ = number; }

long long Subscriber::getYear() const             { return year_; }

string    Subscriber::getPlan() const	          { return plan_; }
void      Subscriber::setPlan(const string &plan) { plan_ = plan; }