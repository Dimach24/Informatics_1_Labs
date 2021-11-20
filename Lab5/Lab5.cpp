#include <iostream>				// input-output streams library
#include "../libs/PhoneNumerCPP.h"	// phonebook lib
#include <process.h>			// for 'system' functions
int main()
{
	Phonebook pb;				// create phonebook
	pb.input("0");				// input phonebook until "0"
	pb.print(50,std::cout,'.'); // print phonebook
	if (system(NULL)){			// if 'system' function is available
		system("pause");		// do not close console
	}
	return 0;
}