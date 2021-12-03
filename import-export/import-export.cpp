// import-export.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../libs/PhoneNumerCPP.h"
#include <fstream>
#include <process.h>
#include <atlconv.h>
#include <fcntl.h>
#include <io.h>

int main()
{
	setlocale(LC_ALL, "rus");
	//Phonebook pb;
	std::wifstream fin(R"(C:\Users\D.mon\Documents\учеба\инфа\Chaminov_Dmeatry\Labs\Release\files\contacts.csv)");
	/*pb.importPhonebook(fin);
	pb.print(0,std::cout,'.');
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}*/
	std::wstring s;
	getline(fin, s);
	getline(fin, s);
	char buffer[1024];
	const char d = '@';
	LPBOOL t = new BOOL(1);
	WideCharToMultiByte(1256, WC_COMPOSITECHECK, s.c_str(), -1, buffer, 1024, &d, t);
	delete t;
	std::cout << buffer << '\n';
	fin.close();
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}
	std::wofstream fout(R"(C:\Users\D.mon\Documents\учеба\инфа\Chaminov_Dmeatry\Labs\Release\files\contacts_o.csv)");


	fout.write(s.c_str(), s.size());
	fout.close();
	return 0;
}
