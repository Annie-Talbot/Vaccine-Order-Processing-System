#include <iostream>
#include <string>
#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H
#include <exceptions.hpp>
#endif

class Date
{
	int year;
	int month;
	int day;
	bool ended;
public:
	Date(int, int, int);
	Date(Date*);
	~Date();
	void end();
	bool isEnded();
	friend bool operator>(Date d1, Date d2);
	friend bool operator==(Date d1, Date d2);
	std::string toString();
};
