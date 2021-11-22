// Lab6.cpp 

#include "../libs/PhoneNumerCPP.h"
#include <iostream>
#include <process.h>

int main()
{
	Phonebook pb;
	pb.input();
	pb.print(50, std::cout, '.');	// print phonebook
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}
	return 0;
}
