#include <iostream>
#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include <controller.hpp>
#endif

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		Controller* ctrl = new Controller();
		ctrl->run(argv[1]);
		delete ctrl;
	} else 
		cout << "Please enter a file name." <<  endl;
	return 0;
}
