
#include "../libs/utf-8Converting.h"
#include "../libs/PhoneNumerCPP.h"
#include <iostream>
#include <fstream>
#include <process.h>
#include "../libs/PhoneNumerCPP.h"


int main()
{
	Phonebook pb;
	setlocale(LC_ALL, "rus");
start_case:
	std::cout << "Выбирете действие:" << std::endl;
	std::ifstream fin;
	std::string answer;
	switch (choose_list(3, "Ввести с клавиатуры\0Ввести из файла\0Импортировать\0")) {
	case 1:
		pb.input("0",std::cin,std::cout,"Введите имя\n>>> ","Введите номер\n>>> ");
		break;
	case 2:
		while (!fin.is_open()) {
			std::cout << "Введите путь к файлу:" << std::endl
				<< ">>> ";
			getline(std::cin, answer);
			fin.open(answer);
			if (!fin.is_open()) {
				std::cout << "Не удалось открыть файл :(" << std::endl
					<< "Выбирите действие:" << std::endl;
				switch (choose_list(3, "Попробовать снова\0Вернуться к началу\0Завершить выполнение")) {
				case 1:
					break;
				case 2:
					goto start_case;
					break;
				case 3:
					return 0;
					break;
				}
			}
		}
		pb.inputFromFile(fin);
		break;
	case 3:
		while (!fin.is_open()) {
			std::cout << "Введите путь к файлу:" << std::endl
				<< ">>> ";
			getline(std::cin, answer);
			fin.open(answer);
			if (!fin.is_open()) {
				std::cout << "Не удалось открыть файл :(" << std::endl
					<< "Выбирите действие:" << std::endl;
				switch (choose_list(3, "Попробовать снова\0Вернуться к началу\0Завершить выполнение")) {
				case 1:
					break;
				case 2:
					goto start_case;
					break;
				case 3:
					return 0;
					break;
				}
			}
		}
		pb.importPhonebook(fin);
		break;
	}
	return 0;
}
//TODO
// добавить флаг записи (про utf-8) и 
// его обработчик внутри функции вывода
// для совмещения источников записей

