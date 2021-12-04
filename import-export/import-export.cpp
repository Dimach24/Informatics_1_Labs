
#include "../libs/utf-8Converting.h"
#include "../libs/PhoneNumerCPP.h"
#include <iostream>
#include <fstream>
#include <process.h>



int main()
{
	setlocale(LC_ALL, "rus");
	std::ifstream fin(R"(C:\Users\D.mon\Documents\учеба\инфа\Chaminov_Dmeatry\Labs\Release\files\contacts.csv)");
	std::string s;
	Phonebook pb;
	pb.importPhonebook(fin);
	fin.close();
	pb.print_utf();
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}
	return 0;
}
