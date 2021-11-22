// Lab7.cpp

#include <iostream>
#include "../libs/PhoneNumerCPP.h"
#include <fstream>

int main()
{
	Phonebook pb;
	std::string answer;
	if (did_user_accept("Do you want to use file as an input?")) {
		std::ifstream fin;
		//file opening
		{
			while (!fin.is_open()) {
				std::cout << "Input file path:\n";
				getline(std::cin, answer, '\n');
				fin.open(answer);
				if (!fin.is_open()) {
					std::cerr << "Can't open the file" << std::endl;
				}
			}
		}
		pb.inputFromFile(fin);
		fin.close();
	} else {
		pb.input("0");
	}
	if (did_user_accept("Do you want to use file as an output?")) {
		std::ofstream fout;
		//file opening
		{
			while (!fout.is_open()) {
				std::cout << "Input file path:\n";
				getline(std::cin, answer, '\n');
				fout.open(answer);
				if (!fout.is_open()) {
					std::cerr << "Can't open the file" << std::endl;
				}
			}
		}
		pb.print(40, fout, '.');
		fout.close();
	} else {
		pb.print(40, std::cout, '.');
	}
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}
	return 0;
}

