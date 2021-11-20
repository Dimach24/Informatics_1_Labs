#define _CRT_SECURE_NO_WARNINGS							// MS VS forbids unsafe functions like 'scanf'

#include <stdio.h>										// standard input/output library
#include "../libs/myDecToBinLibFunctions.h"				// my library with my functions
#include <stdlib.h>										// for atoi function

int main()
{
	char A[MY_STR_SIZE] = { 0 };// string for input 
	int requests[100] = { 0 };	// array for initial numbers
	int i = 0;					// just a counter

	do {
		printf("Input your numbers\n>>>");	//prompt for input
		scanf("%s", A);						// get string
		int tmp = atoi(filter_string(A));	//filter string and get number from it
		while (tmp) {						//while inputed not zero
			requests[i++] = tmp;			// put this request into array
			printf(">>>");					// prompt for input
			scanf("%s", A);					// get string
			tmp = atoi(filter_string(A));	//filter string and get number from it
		}
	} while (!did_user_accept());			//while user not accepted exiting

	printf("Output:\n #  |       decimal  |              binary\n");	// table header
	i = 0;
	while (requests[i]) {					// for each inputted number
		char res[33];						// c-string for binary representation
		represent_as_bin(requests[i], res);	// represent as bin and write representation in res
		//printf("%-5d%-+16d%s\n", i + 1, requests[i], res);	// print row of the table
		char number_s[4] = { 0 }, 
			decimal_s[15] = { 0 };
		_itoa(i+1, number_s, 10);				// make string with index + 1
		_itoa(requests[i], decimal_s, 10);		// make string with requested number
		inflate_string(number_s, 3, StringAlign::center);	// format string
		inflate_string(decimal_s, 14, StringAlign::right);	//format string
		char row[80] = { 0 };					// string for the row of the table
		strcat(row, number_s);					// add index + 1 string to the row
		strcat(row, " | ");						// add separator to the row
		strcat(row, decimal_s);					// add requested number string to the row
		strcat(row, " | ");						// add separator to the row
		strcat(row, res);						// add binary representation to the row
		printf("%s\n", row);					// print row
		i++;									// increase index
	}
	do_pause();								// do not close console, user should be able to see result
	return 0;								// EXIT_SUCCESS
}