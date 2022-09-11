#include <iostream>
#include <iomanip>
#include <string>
#ifndef __DATE_H
#define __DATE_H
#include <date.hpp>
#endif
using namespace std;

class Invoice
{
	int id;
	int customerNum;
	string customerName;
	string orderType;
	int quantity;
	Date* date;
public:
	Invoice(int, int, string, string, int, Date* date);
	~Invoice();
	friend ostream &operator<<(ostream &os, Invoice &i);
};
