//myPhoneNumberLib.h

#include "myPhoneNumberLib.h"


/// <summary>
/// Creates record, allocs memory for name
/// DO NOT FORGIVE DELETE PHONE RECORD
/// </summary>
/// <param name="nick">nickname</param>
/// <param name="number">phone number</param>
/// <returns>returns pointer to new record</returns>
MyPhoneRecord* create_record(const char* nick, const char* number)
{
	MyPhoneRecord* res = new MyPhoneRecord;     // allocate memory for record

	res->nickname = new char[strlen(nick) + 1]; // allocate memory for nickname and '\0'
	strcpy(res->nickname, nick);                // copy nick to record nickname

	char* filtered_num = new char[strlen(number) + 1];
	strcpy(filtered_num, number);
	// allocate memory for filtered number and '\0'

	filter_string(filtered_num); // filter string
	if (filtered_num[0] == '+') { res->number.plus = 1; } // set plus
	else { res->number.plus = 0; } // set no plus
	if (filtered_num[0] == '-') { filtered_num[0] = '+'; }// ignore '-'
	res->number.number = atoll(filtered_num); // extract int from c-string and put it to res
	delete[] filtered_num;
	return res;
}


/// <summary>
/// Deletes phone record by pointer
/// </summary>
/// <param name="r">pointer to record</param>
void delete_record(MyPhoneRecord* r)
{
	delete r->nickname;				// free c-string
	delete r;						// free record
}


/// <summary>
/// Print phone number record cutting name
/// </summary>
/// <param name="r">pointer to record</param>
/// <param name="nick_len">name length</param>
void print_record(const MyPhoneRecord* r, int nick_len, char filler)
{
	char* nick = new char[nick_len + 1];// allocate memory for nickname in the table
	strncpy(nick, r->nickname, nick_len);//copy nickname to nick
	nick[nick_len] = '\0';	//end of string
	inflate_string(nick, nick_len, StringAlign::left, filler); //formatting nickname

	char number_reverse[21]; // string for a number
	unsigned __int64 n = r->number.number;	// temp variable for 
											//transforming number to reversed string
	int tmp = 0;				// just a counter
	while (n) {
		number_reverse[tmp++] = n % 10 + '0';	// write right digit to the string and increase i
		n /= 10;							// move number to 1 digit right 
	}
	if (r->number.plus) {					// if number includes '+'
		number_reverse[tmp] = '+';			// add + to the string
		number_reverse[tmp + 1] = '\0';		// end of string
	} else {
		number_reverse[tmp] = '\0';			// end of string
	}
	reverse_string(number_reverse);			// reversing string
	inflate_string(number_reverse, 20, StringAlign::right, filler); //formatting number
	printf("%s%s\n", nick, number_reverse);	// print row
	delete[] nick;							// free temp c-string
}
