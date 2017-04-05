// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "stdafx.h"

#include <string>

#include "Subscriber.h"

using namespace std;

Subscriber::Subscriber(const string    fullName,
			           const long long number,
			           const long long year,
			           const string    plan) :
			           fullName_(fullName),
			           number_  (number),
			           year_    (year),
			           plan_    (plan) {}

string   Subscriber::getFullName() const			{ return fullName_;     }
//void     Subscriber::setFullName(string fullName) { fullName_ = fullName; }

long long Subscriber::getNumber() const			  { return number_;   }
void	  Subscriber::setNumber(long long number) { number_ = number; }

long long Subscriber::getYear() const { return year_; }

string    Subscriber::getPlan() const		{ return plan_; }
void      Subscriber::setPlan(string plan) { plan_ = plan; }