//myDecToBinLibFunctions.h

#ifndef myDecToBinLibFunctionsINCLUDED
#define myDecToBinLibFunctionsINCLUDED

#define MY_STR_SIZE 100										// size of the string, that user will be input
#define _CRT_SECURE_NO_WARNINGS								// MS VS do forbids unsafe functions like 'scanf'

#include <stdbool.h>										// standard bool type library
#include <string.h>											// standard string functions library
#include <stdio.h>											// standard input/output library
#include <process.h>										// library for system functions


char* filter_string(char* s);
/*
	removes all 'bad' characters (not digits or sign if it is first)
	in the c-string
	function is protected by limitation string size with MY_STR_SIZE
*/



/// <summary>
/// reverses string
/// </summary>
/// <param name="s">pointer to c-string</param>
/// <returns></returns>
char* reverse_string(char* s);

void represent_as_bin(int n, char* b);
/*
	Represents -2^16 <= n < 2^16 in binary notation and writes
	result to the c-string b, that MUST BE AT LEAST 32 SYBLOS LENGTH
*/

bool did_user_accept();
/*
	Asks user if he really want to exit
	returns true if it's true else returns false
*/

void do_pause(char print_dir = 0);
/*
	Do not close console,
	if print_dir is not 0 - uses dir command
	function is safe
*/

enum StringAlign { left, center, right }; // types of the string align for inflate_string function
char* inflate_string(char* s, unsigned int width, StringAlign align = StringAlign::left, char filler = ' ');
/*
	Increases string size with adding filler symbols according to align parameter
*/
#endif