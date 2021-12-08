//import-export.cpp
#include "../libs/PhoneNumerCPP.h"		// for working with phonebook
#include <iostream>						// for working with input/output streams
										// and console i/o streams
#include <fstream>						// for working with file streams
#include <process.h>					// for 'system' functions
#include <consoleapi2.h>				// for console codepages settings

int main()
{
	Phonebook pb;						// Phonebook object
	SetConsoleCP(1251);					// set console input codepage
	SetConsoleOutputCP(1251);			// set concole output codepage
	while (true) {						// mainloop (always)
	start_case:							// for "go to the start"
		std::cout << "Выберите действие:" << std::endl;	// prompt for choosing
		std::ifstream fin;				// file input stream object
		std::ofstream fout;				// file output stream object
		std::string answer;				// string for input

		switch (choose_list(8, "Ввести с клавиатуры\0Ввести из файла\0"
			"Импортировать (Google csv)\0Вывести на экран\0"
			"Вывести в файл\0Экспортировать (Google csv)\0Найти номер\0Выйти")) {	// choose action
		case 1:							// console input
		{
			pb.input					// input phonebook
			(
				"0",
				std::cin, std::cout,
				"Введите имя\n>>> ",
				"Введите номер\n>>> ",
				"Вы действительно хотите закончить ввод?",
				"Да\0Нет"
			);
			std::cout << "Ввод завершен" << std::endl;		// action end message
			break;						// end of action
		}
		case 2:							// file input
		{
			while (!fin.is_open()) {	// while file is not opened
				std::cout << "Введите путь к файлу:" << std::endl
					<< ">>> ";			// prompt for input
				getline(std::cin, answer);	// get file name
				fin.open(answer);		// open file
				if (!fin.is_open()) {	// if cannot open
					std::cout << "Не удалось открыть файл :(" << std::endl
						<< "Выберите действие:" << std::endl;	//message and prompt for choosing
					switch (choose_list(3, "Попробовать снова\0Вернуться к началу\0Завершить выполнение")) {
					case 1:					// try again
						break;				// just continue
					case 2:					// go to the start
						goto start_case;	// go to the start
						break;
					case 3:					// exit
						return 0;			// exit success
					}
				}
			}
			pb.inputFromFile(fin);		// input phonebook from file
			fin.close();				// close file
			std::cout << "Ввод завершен" << std::endl; // action end message
			break;
		}
		case 3:							// import
		{
			while (!fin.is_open()) {	// while file is not opened
				std::cout << "Введите путь к файлу:" << std::endl
					<< ">>> ";			// prompt for input
				getline(std::cin, answer);	// get file name
				fin.open(answer);		// open file
				if (!fin.is_open()) {	// if cannot open
					std::cout << "Не удалось открыть файл :(" << std::endl
						<< "Выберите действие:" << std::endl;	// message and prompt for choosing action
					switch (choose_list(3, "Попробовать снова\0Вернуться к началу\0Завершить выполнение")) {
					case 1:				// try again
						break;			// just continue (loop)
					case 2:				// go to the start
						goto start_case;// go to the start
						break;
					case 3:				// exit
						return 0;		// exit success code
						break;
					}
				}
			}
			pb.importPhonebook(fin);	// import phonebook
			fin.close();				// close the file
			std::cout << "Импорт завершен" << std::endl;	// action end message
			break;						// end of the action
		}
		case 4:							// console output
		{
			std::cout << "Распечатка телефонной книги:" << std::endl;	//message
			pb.print(0, std::cout, '.');// phonebook console output
			break;						// end of the action
		}
		case 5:							// file output
		{
			while (!fout.is_open()) {	// while file is not opened
				std::cout << "Введите путь к файлу:" << std::endl
					<< ">>> ";			// prompt for input
				getline(std::cin, answer);	// input file name
				fout.open(answer);		// open the file
				if (!fout.is_open()) {	// if cannot open the file
					std::cout << "Не удалось открыть файл :(" << std::endl
						<< "Выберите действие:" << std::endl;	// message and prompt for choosing
					switch (choose_list(3, "Попробовать снова\0Вернуться к началу\0Завершить выполнение")) {
					case 1:				// try again
						break;			// just continue (loop)
					case 2:				// go to the start
						goto start_case;// go to the start
						break;
					case 3:				// exit
						return 0;		// exit success code
						break;
					}
				}
			}
			pb.print(0, fout, '.');		// file output
			fout.close();				// close the file
			std::cout << "Вывод завершен" << std::endl;	// action end message
			break;						// end of the action
		}
		case 6:							// export
		{
			while (!fout.is_open()) {	// while file is not opened
				std::cout << "Введите путь к файлу:" << std::endl
					<< ">>> ";			// prompt for input
				getline(std::cin, answer);	// input file name
				fout.open(answer);		// open the file
				if (!fout.is_open()) {	// if cannot open the file
					std::cout << "Не удалось открыть файл :(" << std::endl
						<< "Выберите действие:" << std::endl;	// message and prompt for choosing
					switch (choose_list(3, "Попробовать снова\0Вернуться к началу\0Завершить выполнение")) {
					case 1:				// try again
						break;			// continue (loop)
					case 2:				// go to the start
						goto start_case;// go to the start
						break;
					case 3:				// exit
						return 0;		// exit success code
						break;
					}
				}
			}
			pb.exportPhonebook(fout);	// export phonebook
			fout.close();				// close the file
			std::cout << "Экспорт завершен" << std::endl;	// end of action message
			break;						// end of the acion
		}
		case 7:
		{
			if (pb.isEmpty()) {				// if phonebook is empty
				std::cout << "Телефонная книга пуста" << std::endl;	//message
				break;								// end of the action
			}
			std::cout << "Введите имя контакта" << std::endl << ">>> ";	//prompt for input
			getline(std::cin, answer);				// get contact name
			PhoneRecord to_find;					// Phone record with the same name as got
			to_find.setName(answer);				// set this name
			auto p_record = pb.findRecord(to_find);	// place for iterator to the record
	
			if (pb.isTail(p_record)) {				// if it's the .end() of phoneebok
				p_record--;
				// set it to the last element
			}
			std::cout			// output and prompt for action choosing
				<< "Имя контакта: \"" << p_record->getName() << "\"" << std::endl
				<< "Номер: " << p_record->getNumber() << std::endl
				<< "Выберите действие:" << std::endl;
			switch (choose_list(4, "Продолжить\0Переименовать\0Изменить номер\0Удалить")) {
			case 1:									// continue
				break;								// continue
			case 2:									// rename
			{
				std::cout << "Введите новое имя контакта" << std::endl << ">>> "; //prompt for input
				getline(std::cin, answer);			// get new name
				std::cout							// prompt for confirmation
					<< "Вы действительно хотите сменить имя контакта с \""
					<< p_record->getName()
					<< "\" на \"" << answer << "\"?" << std::endl;
				if (choose_list(2, "Да\0Нет") == 1) {//if confirmed
					p_record->setName(answer);		// rename 
					std::cout << "Имя контакта успешно изменено" << std::endl;	// message
				} else {
					std::cout << "Изменения отменены" << std::endl;				// message
				}
				break;
			}
			case 3:									// change the number
			{
				std::cout << "Введите новый номер контакта" << std::endl << ">>> ";
				// prompt for input
				getline(std::cin, answer);			// input the number
				to_find.setNumber(answer, true);	// filter and remember new number
				std::cout							// confirmation
					<< "Вы действительно хотите сменить номер контакта с \""
					<< p_record->getNumber()
					<< "\" на \"" << to_find.getNumber() << "\"?" << std::endl;
				if (choose_list(2, "Да\0Нет") == 1) {//if confirmed
					p_record->setNumber(to_find.getNumber(), false);	// set new number
					std::cout << "Номер контакта успешно изменен" << std::endl;	// message
				} else {
					std::cout << "Изменения отменены" << std::endl;				// message
				}
				break;
			}
			case 4:									// delete
				std::cout							// confirmation
					<< "Вы действительно хотите удалить контакт с именем \""
					<< p_record->getName() << "\"?" << std::endl;
				if (choose_list(2, "Да\0Нет") == 1) {//if confirmed
					pb.deleteRecord(p_record);		// delete record
					std::cout << "Контакт удален" << std::endl;		// message
				} else {
					std::cout << "Удаление отменено" << std::endl;	// message
				}
				break;
			}
			break;
		}
		case 8:										// exit
		{
			return 0;								// exit success code
		}
		}
		system("pause");							// wait any key pressed
		system("cls");								// clear console
	}
}
