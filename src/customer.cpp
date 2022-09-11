#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#include <customer.hpp>

Customer::Customer(int id, std::string name)
{
	this->id = id;
	this->name = new std::string(name);
	this->vaccinesOrdered = 0;

}

Customer::~Customer() 
{
	delete this->name;
}

ostream &operator<<(ostream &os, Customer &c)
{
	os << "ID: " << c.id << " Name: " << *c.name << " VaccinesOrdered: " <<	
	c.vaccinesOrdered;
	return os;
}

int Customer::getId()
{
	return this->id;
}

string Customer::getName()
{
	return *this->name;
}

int Customer::getNumVaccinesOrdered()
{
	return this->vaccinesOrdered;
}

void Customer::order(int quantity)
{
	this->vaccinesOrdered += quantity;
	return;
}

void Customer::reset()
{
	this->vaccinesOrdered = 0;
	return;
}

void Customer::notify(Invoice* i)
{
	cout << "SC: " << *i << endl;
	delete i;
	return;
}

int Customer::hasOrdered()
{
	if (this->vaccinesOrdered == 0)
		return 0;
	return 1;
}

#endif
