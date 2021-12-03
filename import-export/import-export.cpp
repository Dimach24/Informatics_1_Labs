// import-export.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "../libs/PhoneNumerCPP.h"
#include <fstream>
#include <process.h>
#include <fcntl.h>
#include <io.h>

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    //setlocale(LC_ALL, "utf-8");
    Phonebook pb;
    std::wifstream fin(R"(C:\Users\D.mon\Documents\учеба\инфа\Chaminov_Dmeatry\Labs\Release\files\contacts.csv)");
    /*pb.importPhonebook(fin);
    pb.print(0,std::cout,'.');
    if (system(NULL)) {				// if 'system' function is available
        system("pause");			// do not close console
    }*/
    wchar_t buffer[1024];
    std::wstring s;
    fin.getline(buffer,1024);
    fin.getline(buffer,1024);
    s = buffer;
    std::wcout << s <<'\n';
    fin.close();
    if (system(NULL)) {				// if 'system' function is available
        system("pause");			// do not close console
    }
    std::wofstream fout(R"(C:\Users\D.mon\Documents\учеба\инфа\Chaminov_Dmeatry\Labs\Release\files\contacts_o.csv)");
    fout.write(s.c_str(),s.size());
    fout.close();
    return 0;
}
