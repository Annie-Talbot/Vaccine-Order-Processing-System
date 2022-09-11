#include <forward_list>
#include <fstream>
#ifndef __CUSTOMER_H
#define __CUSTOMER_H
#include <customer.hpp>
#endif
#ifndef __COMMAND_H
#define __COMMAND_H
#include <command.hpp>
#endif
#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H
#include <exceptions.hpp>
#endif
#ifndef __DATE_H
#define __DATE_H
#include <date.hpp>
#endif

class Command;

class Controller
{
	forward_list<Customer*>* customerList;
	int nextCustId;
	int nextInvId;
public:
	Date* today;
	Controller();
	~Controller();
	Customer* findCustomer(int);
	void ship(Customer*, std::string);
	void shipAll();
	void run(std::string);
	Customer* addCustomer(std::string*);
	Command* getCommand(std::string);
};
