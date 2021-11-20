//Lab4.cpp
#define _CRT_SECURE_NO_WARNINGS								// MS VS do forbids unsafe functions like 'scanf'

#include<stdio.h> //for input-output
#include "../libs/myPhoneNumberLib.h" //for phone numbers 


int main()
{
	MyPhoneRecord* phonebook[100] = { NULL };		//declarations and filling with '0'
	int i = 0;										//just a counter
	do {
		while (1) {									// always
			char name_buffer[64], num_buffer[64];	// buffers declaration
			printf("Input a name\n>>> ");			// prompt for name input
			do {
				gets_s(name_buffer, 64);			// input string
			} while (name_buffer[0]=='\n' || name_buffer[0]=='\0');	// checking if this is a null string
			if (!strcmp(name_buffer, "0")) {		// if user inputed 0
				break;								// go to asking if user want to exit
			}
			printf("Input the number\n>>> ");		// prompt for number input
			do {
				_itoa(rand(),num_buffer,10);
				gets_s(num_buffer, 64);				// input strings
			} while (name_buffer[0] == '\n' || name_buffer[0] == '\0');	// checking if this is a null string
			if (!strcmp(num_buffer, "0")) {			// if user inputed 0
				break;								// go to asking if user want to exit
			} else {
				phonebook[i++] = create_record(name_buffer, num_buffer); //else create record
			}
		}
		printf("You inputed '0', you are going to exit.\n");	// ask about exiting
	} while (!did_user_accept());	// checking iif user really want to exit
	printf("#   Nickname                               Number\n");	// table header
	for (int j = 0; j < i; j++) {			// for all records
		printf("%-3d ", j+1);				// print number
		print_record(phonebook[j], 30,' ');	// print record
		delete_record(phonebook[j]);		// delete (free) records memory
		phonebook[j] = NULL;				// erase pointer from array
	}
	do_pause();								// do not close console
	return 0;
}
