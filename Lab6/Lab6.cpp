﻿// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "../libs/PhoneNumerCPP.h"

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
