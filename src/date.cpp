#ifndef __DATE_H
#define __DATE_H
#include <date.hpp>
using namespace std;


Date::Date(Date* d)
{
	this->year = d->year;
	this->month = d->month;
	this->day = d->day;
	this->ended = false;
}

Date::Date(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->ended = false;

	/* Make sure the date is valid */
	if (month == 1 || month == 3 || month == 5 || month == 7 
		|| month == 8 || month == 10 || month == 12)
	{
		if (day < 1 || day > 31)
			throw InvalidDateException();
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day < 1 || day > 30)
			throw InvalidDateException();
	}
	else if (month == 2)
	{
		if (day < 1 || day > 29)
			throw InvalidDateException();
	}
	else
		throw InvalidDateException();
}

Date::~Date(){}

void Date::end()
{
	this->ended = true;
	return;
}

bool Date::isEnded()
{
	return this->ended;
}

bool operator>(Date d1, Date d2)
{
	if (d1.year < d2.year)
		return false;
	else if (d1.year > d2.year)
		return true;
	else
	{
		if (d1.month < d2.month)
			return false;
		else if (d1.month > d2.month)
			return true;
		else
		{
			if (d1.day < d2.day)
				return false;
			else if (d1.day > d2.day)
				return true;
			else
				return false;
		}
	}
}

bool operator==(Date d1, Date d2)
{
	return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day;
}

string Date::toString()
{
	return to_string(this->year) + "-" + to_string(this->month) + "-" + to_string(this->day);
}
#endif
