//myPhoneNumberLib.h

#ifndef MY_PHONE_NUMBER_LIB_INCLUDED
#define MY_PHONE_NUMBER_LIB_INCLUDED

#define _CRT_SECURE_NO_WARNINGS								// MS VS do forbids unsafe functions like 'scanf'

#include <stdio.h> // for input-output
#include <process.h> // for 'system' function
#include <string.h> // for string functions
#include <stdlib.h> // for 'atoi' functions
#include "myDecToBinLibFunctions.h" 
// for functions from previous labs


typedef struct {
	unsigned __int64 number : 50; // is digits in a number
	/*
	According to E.164 (standard phone number recording format)
	phone numbers should be not longer than 15 digits.
	So greatest phone number is: 999 999 999 999 999.
	Then 50 bits are enough for recording this number,
	because 2^50 = 1 125 899 906 842 624.
	*/
	unsigned __int64 plus : 1; // :=1 if number includes +, else :=0
}MyPhoneNumber;

typedef struct {
	MyPhoneNumber number; // phone number
	char* nickname;       // nickname
}MyPhoneRecord;


/// <summary>
/// Creates record, allocs memory for name
/// DO NOT FORGIVE DELETE PHONE RECORD
/// </summary>
/// <param name="nick">nickname</param>
/// <param name="number">phone number</param>
/// <returns>returns pointer to new record</returns>
MyPhoneRecord* create_record(const char* nick, const char* number);


/// <summary>
/// Deletes phone record by pointer
/// </summary>
/// <param name="r">pointer to record</param>
void delete_record(MyPhoneRecord* r);


/// <summary>
/// Print phone number record cutting name
/// </summary>
/// <param name="r">pointer to record</param>
/// <param name="nick_len">name length</param>
void print_record(const MyPhoneRecord* r, int nick_len, char filler=' ');


#endif // !MY_PHONE_NUMBER_LIB_INCLUDED