// Lab6.cpp 

#include "../libs/PhoneNumerCPP.h"	// my lib
#include <iostream>					// for std::cout
#include <process.h>				// for 'system' function

int main()
{
	Phonebook pb;					// phonebook declaration (default constructor called)
	pb.input();						// input the phonebook
	pb.print(50, std::cout, '.');	// print phonebook
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}
	return 0;						// Exit success
}
