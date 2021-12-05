
#include "../libs/utf-8Converting.h"
#include "../libs/PhoneNumerCPP.h"
#include <iostream>
#include <fstream>
#include <process.h>
#include "../libs/PhoneNumerCPP.h"


int main()
{
	Phonebook pb;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	while (true) {
	start_case:
		std::cout << "Выберите действие:" << std::endl;
		std::ifstream fin;
		std::ofstream fout;
		std::string answer;

		switch (choose_list(8, "Ввести с клавиатуры\0Ввести из файла\0"
			"Импортировать (Google csv)\0Вывести на экран\0"
			"Вывести в файл\0Экспортировать (Google csv)\0Найти номер\0Выйти")) {
		case 1:
		{
			pb.input
			(
				"0",
				std::cin, std::cout,
				"Введите имя\n>>> ",
				"Введите номер\n>>> ",
				"Вы действительно хотите закончить ввод?",
				"Да\0Нет"
			);
			std::cout << "Ввод завершен" << std::endl;
			break;
		}
		case 2:
		{
			while (!fin.is_open()) {
				std::cout << "Введите путь к файлу:" << std::endl
					<< ">>> ";
				answer = "";
				while (answer == "") {
					getline(std::cin, answer);
				}
				fin.open(answer);
				if (!fin.is_open()) {
					std::cout << "Не удалось открыть файл :(" << std::endl
						<< "Выберите действие:" << std::endl;
					switch (choose_list(3, "Попробовать снова\0Вернуться к началу\0Завершить выполнение")) {
					case 1:
						break;
					case 2:
						goto start_case;
						break;
					case 3:
						return 0;
					}
				}
			}
			pb.inputFromFile(fin);
			fin.close();
			std::cout << "Ввод завершен" << std::endl;
			break;
		}
		case 3:
		{
			while (!fin.is_open()) {
				std::cout << "Введите путь к файлу:" << std::endl
					<< ">>> ";
				getline(std::cin, answer);
				fin.open(answer);
				if (!fin.is_open()) {
					std::cout << "Не удалось открыть файл :(" << std::endl
						<< "Выберите действие:" << std::endl;
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
			fin.close();
			std::cout << "Импорт завершен" << std::endl;
			break;
		}
		case 4:
		{
			std::cout << "Распечатка телефонной книги:" << std::endl;
			pb.print(0, std::cout, '.');
			break;
		}
		case 5:
		{
			while (!fout.is_open()) {
				std::cout << "Введите путь к файлу:" << std::endl
					<< ">>> ";
				getline(std::cin, answer);
				fout.open(answer);
				if (!fout.is_open()) {
					std::cout << "Не удалось открыть файл :(" << std::endl
						<< "Выберите действие:" << std::endl;
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
			pb.print(0, fout, '.');
			fout.close();
			std::cout << "Вывод завершен" << std::endl;
			break;
		}
		case 6:
		{
			while (!fout.is_open()) {
				std::cout << "Введите путь к файлу:" << std::endl
					<< ">>> ";
				getline(std::cin, answer);
				fout.open(answer);
				if (!fout.is_open()) {
					std::cout << "Не удалось открыть файл :(" << std::endl
						<< "Выберите действие:" << std::endl;
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
			pb.exportPhonebook(fout);
			fout.close();
			std::cout << "Экспорт завершен" << std::endl;
			break;
		}
		case 7:
		{
			std::cout << "Введите имя контакта" << std::endl << ">>> ";
			getline(std::cin, answer);
			PhoneRecord to_find;
			to_find.setName(answer);
			auto p_record = pb.findRecord(to_find);
			if (pb.isTail(p_record)) { p_record--; }
			std::cout
				<< "Имя контакта: \"" << p_record->getName() << "\"" << std::endl
				<< "Номер: " << p_record->getNumber() << std::endl
				<< "Выберите действие:" << std::endl;
			switch (choose_list(4, "Продолжить\0Переименовать\0Изменить номер\0Удалить")) {
			case 1:
				break;
			case 2:
			{
				std::cout << "Введите новое имя контакта" << std::endl << ">>> ";
				getline(std::cin, answer);
				std::cout
					<< "Вы действительно хотите сменить имя контакта с \""
					<< p_record->getName()
					<< "\" на \"" << answer << "\"?" << std::endl;
				if (choose_list(2, "Да\0Нет") == 1) {
					p_record->setName(answer);
					std::cout << "Имя контакта успешно изменено" << std::endl;
				} else {
					std::cout << "Изменения отменены" << std::endl;
				}
				break;
			}
			case 3:
			{
				std::cout << "Введите новый номер контакта" << std::endl << ">>> ";
				getline(std::cin, answer);
				to_find.setNumber(answer, true);
				std::cout
					<< "Вы действительно хотите сменить номер контакта с \""
					<< p_record->getNumber()
					<< "\" на \"" << to_find.getNumber() << "\"?" << std::endl;
				if (choose_list(2, "Да\0Нет") == 1) {
					p_record->setNumber(to_find.getNumber(), false);
					std::cout << "Номер контакта успешно изменен" << std::endl;
				} else {
					std::cout << "Изменения отменены" << std::endl;
				}
				break;
			}
			case 4:
				std::cout
					<< "Вы действительно хотите удалить контакт с именем \""
					<< p_record->getName() << "\"?" << std::endl;
				if (choose_list(2, "Да\0Нет") == 1) {
					pb.deleteRecord(p_record);
					std::cout << "Контакт удален" << std::endl;
				} else {
					std::cout << "Удаление отменено" << std::endl;
				}
				break;
			}
			break;
		}
		case 8:
		{
			return 0;
		}
		}
		system("pause");
		system("cls");
	}
}
