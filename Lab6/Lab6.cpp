// Lab6.cpp 

#include "../libs/PhoneNumerCPP.h"
#include <iostream>
#include <process.h>

int main()
{
	Phonebook pb;					// phonebook declaration (default constructor called)
	pb.input();						// input the phonebook
	pb.print(50, std::cout, '.');	// print phonebook
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}
	return 0;
}
