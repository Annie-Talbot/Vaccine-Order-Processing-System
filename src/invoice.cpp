#ifndef __INVOICE_H
#define __INVOICE_H
#include <invoice.hpp>

Invoice::Invoice(int id, int customerNum, string name, string orderType, int quantity, 
			Date* date)
{
	/* Constructor for an invoice object.
 * 	Assigning the instances main attributes. */
	this->id = id;
	this->customerNum = customerNum;
	this->customerName = name;
	this->orderType = orderType;
	this->quantity = quantity;
	this->date = date;
}

Invoice::~Invoice(){}

ostream &operator<<(ostream &os, Invoice &i)
{
	/* Custom write to stream operator.
 * 	When this object is outputted to a stream, all its important
 * 	attributes are included. */

	os << "InvoiceID: " << i.id << " CustomerID: " << setw(4) << setfill('0') 
		<< i.customerNum << " CustomerName: " << i.customerName << 
		" OrderType: " << i.orderType << " Quantity: " << i.quantity 
		<< " Date: " << i.date->toString(); 
	return os;
}

#endif
