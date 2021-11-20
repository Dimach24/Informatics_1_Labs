//myDecToBinLibFunctions.cpp

#include "myDecToBinLibFunctions.h"

char* filter_string(char* s)
{	/*
		removes all 'bad' characters (not digits or sign if it is first)
		in the c-string
		function is protected by limitation string size with MY_STR_SIZE
	*/
	int i,			// index of the char that we read from the string
		j;			// index of the char that we write to the string
	for (i = j = 0; i < MY_STR_SIZE && s[i] != '\0'; i++) {	// for each char in the string
		if (('0' <= s[i] && s[i] <= '9') || (j == 0 && (s[i] == '-'|| s[i]=='+'))) {	// if char is not bad
			s[j++] = s[i];												// we write it
		}
	}
	s[j] = '\0';	// end of c-string
	return s;
}


/// <summary>
/// Reverses string
/// </summary>
/// <param name="s">pointer to a c-string</param>
/// <returns></returns>
char* reverse_string(char* s)
{
	int n = strlen(s);	// string size
	for (int i = 0; i < n / 2; i++) { // for i from 0 to middle of the string
		char tmp = s[i];			// just a buffer for values exchange
		s[i] = s[n - i - 1];		// exchanging
		s[n - i - 1] = tmp;			// still exchanging
	}
	return s;
}

void represent_as_bin(int n, char* b)
{
	/*
		Represents -2^16 <= n < 2^16 in binary notation and writes
		result to the c-string b, that MUST BE AT LEAST 32 SYBLOS LENGTH
	*/
	int i;                                          // bit index
	for (i = 0; i < 32; i++) {                      // i reaches from 0 to 32 increasing by 1
		if ((n & (1 << (31 - i)))) {				// if this bit is 1
	//         ^ use mask
	//               ^ set mask to 0...1...0, where 1 is at (31-i) bit
			b[i] = '1';								// set current char in c-string to '1'
		} else {
			b[i] = '0';								// set current char in c-string to '0'
		}
	}
	b[i] = '\0';    // end of c-string
}

void do_pause(char print_dir)
{
	/*
		Do not close console,
		if print_dir is not 0 - uses dir command
		function is safe
	*/
	if (system(NULL)) {
		if (print_dir) {
			system("DIR");
		}
		system("pause");

	}
}
char* inflate_string(char* s, unsigned int width, StringAlign align, char filler)
{
	/*
		Increases string size with adding filler symbols according to align parameter
	*/
	unsigned int n = strlen(s);	// get length
	switch (align) {			// for the different aligns
	case StringAlign::left:
	{
		int i;
		for (i = n; i < width; i++) {
			s[i] = filler;		// just add fillers after end of 
								//string until they reach width
		}
		
		break;
	}
	case StringAlign::right:
	{
		int i;
		for (i = width - 1; i >= 0; i--) {
			s[i] = width - i <= n ? s[n - (width - i)] : filler;
			// copy symbols to the end string if we have symbols left
			// else just put fillers
		}
		break;
	}
	case StringAlign::center:
	{
		inflate_string(s, (width - n) / 2 + n, StringAlign::right, filler); // add fillers to the left
		inflate_string(s, width, StringAlign::left, filler);				// add fillers to the right
		break;
	}
	}
	s[width] = '\0';			// end of string
	return s;
}
bool did_user_accept()
{	/*
		Asks user if he really want to exit
		returns true if it's true else returns false
	*/
	char a[MY_STR_SIZE] = "a";								// c-string for answer
	do {
		printf("Are you sure (y/n): ");		//prompt for input
		scanf("%s", a);										// get answer
		// while answer is neither 'y' nor 'n'
	} while (!(!strncmp(a, "y", MY_STR_SIZE) || !strncmp(a, "n", MY_STR_SIZE)));
	return !strcmp(a, "y");				// return if user want to exit
}
