#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <algorithm>
#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include <controller.hpp>
#endif
#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H
#include <exceptions.hpp>
#endif
#ifndef __DATE_H
#define __DATE_H
#include <date.hpp>
#endif

class Controller;

/* Base Class */
class Command
{
public:
	virtual ~Command() {};
	virtual void process(Controller*) = 0;
	friend bool isNumber(string&);
	friend Date* getDate(string);
};

/* Dereived Classes */

class AddCustomerCommand: public Command {
	int id;
	std::string* name;
public:
	AddCustomerCommand(std::string);
	~AddCustomerCommand();
	friend std::ostream &operator<<(std::ostream &os, AddCustomerCommand &cmd);
	void process(Controller*);
};


class OrderCommand:public Command 
{
	Date* date;
	int type;
	int quantity;
	int custID;
public:
	OrderCommand(std::string);
	~OrderCommand();
	int isExpress();
	std::string getStringType();
	friend std::ostream &operator<<(std::ostream &os, OrderCommand &cmd);
	void process(Controller*);
};


class EndOfDayCommand: public Command {
	Date* date;
public:
	EndOfDayCommand(std::string);
	~EndOfDayCommand();
	friend std::ostream &operator<<(std::ostream &os, EndOfDayCommand &cmd);
	void process(Controller*);
};
