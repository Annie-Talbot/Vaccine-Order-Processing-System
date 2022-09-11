#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include <controller.hpp>

Controller::Controller()
{
	this->customerList = new forward_list<Customer*>();	
	this->nextCustId = 1;
	this->nextInvId = 1000;
}
Controller::~Controller()
{
	for (auto it = this->customerList->begin(); it != this->customerList->end(); ++it)
		delete *it;
	delete this->customerList;
	delete this->today;
}

Customer* Controller::findCustomer(int id)
{
	Customer* c;
	for (auto it = this->customerList->begin(); it != this->customerList->end(); ++it)
	{
		c = *it;
		if (c->getId() == id)
			return c;
	}
	throw CustomerDoesNotExistException();
}

void Controller::ship(Customer* c, string type)
{
	Invoice* i = new Invoice(this->nextInvId, c->getId(), c->getName(), 
				 type, c->getNumVaccinesOrdered(), this->today);
	c->notify(i);
	cout << "OP: Customer: " << c->getId() << " Quantity: " << 
		c->getNumVaccinesOrdered() << " shipped." << endl;
 	c->reset();
	this->nextInvId++;
	return;
}

void Controller::shipAll()
{
	for (auto it = this->customerList->begin(); it != this->customerList->end(); ++it)
		if ((*it)->hasOrdered())
			this->ship(*it, "Standard");
	
}

void Controller::run(string filename)
{
	string buffer;
	ifstream f;
	try {
		f.open(filename);
		if (f.is_open())
		{
			while (getline(f, buffer))
			{
				if (buffer == "")
					throw InvalidInputException();
				Command* c = this->getCommand(buffer);
				c->process(this);
				delete c;
			}	
		} else 
			throw CannotOpenFileException();
	} catch (InvalidDateException& e) {
		cerr << "Exception: " << e.what() << endl;
	} catch (DateOrderIncorrectException& e) {
		cerr << "Exception: " << e.what() << endl;	
	} catch (DateDoesNotMatchException& e) {
		cerr << "Exception: " << e.what() << endl;
	} catch (CustomerDoesNotExistException& e) {
		cerr << "Exception: " << e.what() << endl;
	} catch (IncorrectCustomerNumberException& e) {
		cerr << "Exception: " << e.what() << endl;
	} catch (InvalidInputException& e) {
		cerr << "Exception: " << e.what() << endl;
	} catch (CannotOpenFileException& e) {
		cerr << "Exception: " << e.what() << endl;
	} catch (ifstream::failure e) {
		cerr << "Exception: " << e.what() << endl; 
	}
	f.close();
	return;
}

Customer* Controller::addCustomer(string* name)
{
	Customer* c = new Customer(this->nextCustId, *name);
	this->customerList->push_front(c);
	this->nextCustId++;
	return c;
}

Command* Controller::getCommand(string str)
{
	Command* cmd;
	string type = str.substr(0, 1);
	if (type == "C")
		cmd = new AddCustomerCommand(str);
	else if (type == "S")
		cmd = new OrderCommand(str);
	else if (type == "E")
		cmd = new EndOfDayCommand(str);
	else
	{
		throw InvalidInputException();
	}
	return cmd;
}
#endif
