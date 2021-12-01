// import-export.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../libs/PhoneNumerCPP.h"
#include <fstream>
#include <process.h>

int main()
{
    setlocale(LC_ALL, "rus");
    Phonebook pb;
    std::ifstream fin(R"(C:\Users\D.mon\Documents\учеба\инфа\Chaminov_Dmeatry\Labs\Release\files\contacts.csv)");
    pb.importPhonebook(fin);
    pb.print(0,std::cout,'.');
    if (system(NULL)) {				// if 'system' function is available
        system("pause");			// do not close console
    }
    fin.close();
    return 0;
}
