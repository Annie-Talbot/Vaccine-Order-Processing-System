#include <iostream>
#include <exception>
using namespace std;

struct CannotOpenFileException : public exception {
	const char* what() const throw() {
		return "The file specified could not be opened. Please fix and try again";
	}
};

struct InvalidInputException : public exception {
	const char* what() const throw() {
		return "A line on the imput file contains an invalid instruction.Please fix and try again";
	}
};

struct IncorrectCustomerNumberException : public exception {
	const char* what() const throw() {
		return "The input file has allocated a customer with an incorrect customer number. Please alter this number and try again.";
	}
};

struct CustomerDoesNotExistException : public exception {
	const char* what() const throw() {
		return "An order has been made to a customer that as not been added to the system. Please alter this order and try again.";
	}
};

struct DateDoesNotMatchException : public exception {
	const char* what() const throw() {
		return "A command has been inputted with a date that is not the one currenlty being processed. Please alter this date and try again.";
	}
};

struct DateOrderIncorrectException : public exception {
	const char* what() const throw() {
		return "A command has been inputted with a date that is before the current date. Please alter these dates to be in consequetive order and try again.";
	}
};

struct InvalidDateException : public exception {
	const char* what() const throw() {
		return "A command in the input file contains an invalid date. Please fix and try again.";
	}
};
