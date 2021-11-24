// Lab7.cpp

#include <iostream>
#include "../libs/PhoneNumerCPP.h"
#include <fstream>

int main()
{
	Phonebook pb;			// phonebook declaration
	std::string answer;		// string for input
	if (did_user_accept("Do you want to use file as an input?")) {	// asking if user wants to use file
		std::ifstream fin;											// file input stream declaration
		//file opening
		{
			while (!fin.is_open()) {								// while file is not opened
				std::cout << "Input file path:\n";					// ask file name
				getline(std::cin, answer, '\n');					// get file name
				fin.open(answer);									// link stream and file
				if (!fin.is_open()) {								// if can't open the file
					std::cerr << "Can't open the file" << std::endl;// error msg to error output stream
				}
			}
		}
		pb.inputFromFile(fin);										// input the phonebook
		fin.close();												// close input file stream
	} else {
		pb.input("0");												// standard phonebook input
	}
	if (did_user_accept("Do you want to use file as an output?")) {	// ask if user wants to use file
		std::ofstream fout;											// file output stream declaration
		//file opening
		{
			while (!fout.is_open()) {								// while file is not open
				std::cout << "Input file path:\n";					// ask file name
				getline(std::cin, answer, '\n');					// get file name
				fout.open(answer);									// link stream and file
				if (!fout.is_open()) {								// if cannot open
					std::cerr << "Can't open the file" << std::endl;// put message to error string
				}
			}
		}
		pb.print(40, fout, '.');									// phonebook output to the file stream
		fout.close();												// closing file stream
	} else {
		pb.print(40, std::cout, '.');								// standard output
	}
	if (system(NULL)) {				// if 'system' function is available
		system("pause");			// do not close console
	}
	return 0;
}
