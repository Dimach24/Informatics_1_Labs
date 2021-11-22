// Lab7.cpp

#include <iostream>
#include "../libs/PhoneNumerCPP.h"
#include <fstream>

int main()
{
	Phonebook pb;
	std::string answer;
	if (did_user_accept("Do you want to use file as an input?")) {
		std::cout << "Input file path:";
		std::ifstream fin;
	}
	
	std::ofstream fout;
	pb.print(50, std::cout, '.');	// print phonebook
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}
	return 0;
}

