#include <iostream>
#include <string>
#ifndef __INVOICE_H
#define __INVOICE_H
#include <invoice.hpp>
#endif

class Customer 
{
	int id;
	std::string*  name;
	int vaccinesOrdered;
public:
	Customer(int, std::string);
	~Customer();
	friend ostream &operator<<(ostream &os, Customer &c);
	int getId();
	string getName();
	int getNumVaccinesOrdered();
	void order(int);
	void reset();
	void notify(Invoice* i);
	int hasOrdered();
};
