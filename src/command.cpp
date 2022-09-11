#ifndef __COMMAND_H
#define __COMMAND_H
#include <command.hpp>
using namespace std;

bool isNumber(string& s)
{
	/* ensures that the string given is a number */
	return !s.empty() && find_if(s.begin(), s.end(), 
		[](unsigned char c) {return !isdigit(c);}) == s.end();
}

Date* getDate(string s)
{
	/* returns a date object from a string input */
	if (!isNumber(s))
		throw InvalidInputException();
	return new Date(stoi(s.substr(0, 4)), stoi(s.substr(4, 2)),
				stoi(s.substr(6, 2)));
}


/* Add Customer Command */
AddCustomerCommand::AddCustomerCommand(string str)
{
	int length = str.length();
	if (length < 6)
		throw InvalidInputException();
	string temp = str.substr(1, 4);
	if (isNumber(temp))
	{
		this->id = stoi(str.substr(1, 4));
		this->name = new string(str.substr(5, length));
		/* trim the string */
		this->name->erase(this->name->find_last_not_of(" \t\n\r\f\v") + 1);
	} else
		throw InvalidInputException();
}

AddCustomerCommand::~AddCustomerCommand()
{
	delete this->name;
}

ostream &operator<<(ostream &os, AddCustomerCommand &cmd)
{
	os << "Add Customer Command. ID: " << cmd.id << " Name: " << cmd.name;
	return os;
}

void AddCustomerCommand::process(Controller* ctrl)
{
	Customer* c = ctrl->addCustomer(this->name);
	if (c->getId() != this->id)
		throw IncorrectCustomerNumberException();
	cout << "OP: Customer " << setw(5) << setfill('0') << c->getId() 
		<<  " " << c->getName() << " added." << endl;
	return;
}


/* Order Command */
OrderCommand::OrderCommand(string str)
{
	int length = str.length();
	if (length != 17)
		throw InvalidInputException();

	this->date = getDate(str.substr(1, 8));	
	
	string temp = str.substr(9, 1);
	if (temp.compare("N") == 0)
		this->type = 0;
	else if (temp.compare("X") == 0)
		this->type = 1;
	else
		throw InvalidInputException();
	
	temp = str.substr(10, 4);
	if (isNumber(temp))
		this->custID = stoi(temp);
	else
		throw InvalidInputException();
	
	temp = str.substr(14, 3);
	if (isNumber(temp))
		this->quantity = stoi(temp);
	else
		throw InvalidInputException();
	
}

OrderCommand::~OrderCommand()
{
	delete this->date;
}

ostream &operator<<(ostream &os, OrderCommand &cmd)
{
	os << " Order Command. CustomerID: " << cmd.custID << " Type: " << 
	cmd.getStringType() << " Quantity: " << cmd.quantity;
	return os;
}

void OrderCommand::process(Controller* ctrl)
{
	if (!ctrl->today)
		ctrl->today = new Date(this->date);	
	
	if (*ctrl->today > *this->date)
		throw DateOrderIncorrectException();	
	if (ctrl->today->isEnded())
	{
		delete ctrl->today;
		ctrl->today = new Date(this->date);
	} else if (!(*this->date == *ctrl->today))
		throw DateDoesNotMatchException();
	
	Customer* c = ctrl->findCustomer(this->custID);
	cout << "OP: Customer " << setw(4) << setfill('0') << this->custID 
		<< ": " << this->getStringType() << " Order: Quantity: "
		 << this->quantity << endl;

	c->order(this->quantity);
	if (this->isExpress())
		ctrl->ship(c, this->getStringType());
	return;
}

int OrderCommand::isExpress()
{
	return this->type;
}

string OrderCommand::getStringType()
{
	if (this->isExpress())
		return "Express";
	return "Standard";
}
/* End of Day Command */
EndOfDayCommand::EndOfDayCommand(string str)
{
	/* make sure string is in correct format */
	this->date = getDate(str.substr(1, 8));
}	

EndOfDayCommand::~EndOfDayCommand()
{
	delete this->date;
}

ostream &operator<<(ostream &os, EndOfDayCommand &cmd)
{
	os << "End of Day Command: Date: " << cmd.date->toString();
	return os;
}

void EndOfDayCommand::process(Controller* ctrl)
{
	if (!ctrl->today)
		ctrl->today = new Date(this->date);
	
	if (*this->date == *ctrl->today)
	{
		cout << "OP: End of day: " << this->date->toString() << endl;
		ctrl->shipAll();	
		ctrl->today->end();
		return;
	}
	throw DateDoesNotMatchException();
}

#endif
