#include <string>
#include <stdio.h>

//
// Конструктор и деструктор - функции, 
// которые выполняются при создании переменной и
// выходе переменной из области видимости.
//
//
// Конструктор по умолчанию - созданный 
// автоматически компилятором
//

#define MAX_STR_LEN 128

struct MyPhNo_s {
	unsigned long long int plus : 1;
	unsigned long long int number : 45;
};

struct MyPhoneRec_s {
	char nickname[MAX_STR_LEN];
	struct MyPhNo_s phone;
	MyPhoneRec_s(const char name[], unsigned __int64 number, char plus)
	{
		strcpy_s(nickname, name);
		phone.number = number;
		phone.plus = plus ? 1 : 0;
	}
	~MyPhoneRec_s() {}
};

// 3 принципа ООП (Объектно ориентированного программирования):
	// инкапсуляция - способ совмещения переменных и функций в классе
	// полиморфизм - использование множества функций с одними именами, 
	//							  но разными типами/списком параметров
	// наследование - принцип копирование полей родительского класса в дочерний

class MyPhoneRec {
	// Типы доступа:
		// public - открытый всем и вся
		// private - доступный только из методова класса
		// protected - доступный наследникам
public:
	std::string nickname;
	MyPhoneRec();
	MyPhoneRec(char* name, unsigned __int64 number, int plus);
	~MyPhoneRec();
};


int main()
{
	//struct MyPhoneRec_s A("Vasya", 789456, 1);

}

MyPhoneRec::MyPhoneRec()
{
	nickname = "";
}

MyPhoneRec::MyPhoneRec(char* name, unsigned __int64 number, int plus)
{

}

MyPhoneRec::~MyPhoneRec()
{

}
