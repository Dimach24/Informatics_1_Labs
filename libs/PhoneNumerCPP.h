//PhoneNumberCPP.h

#ifndef PHONE_NUMBER_CPP_INCLUDED
#define PHONE_NUMBER_CPP_INCLUDED

#include <string>		// for std::string class and string functions
#include <iostream>		// input-output streams lib
#include <vector>		// for vector container
#include <fstream>		// for file stream 
#include <process.h>
#include "utf-8Converting.h"
/// <summary>
/// Types of string align
/// </summary>
enum StrAlign { left, middle, right };

/// <summary>
/// Inflates string. If string is longer than 'w' characters, cuts the string
/// </summary>
/// <param name="s">the string</param>
/// <param name="w">the width of the string</param>
/// <param name="a">- string align</param>
/// <param name="filler">- character for filling space</param>
/// <returns>inflated string</returns>
std::string inflate_string(std::string s, size_t w, StrAlign a=StrAlign::left, char filler=' ');

/// <summary>
/// Asks user.
/// Filters input
/// </summary>
/// <param name="question">- the question</param>
/// <returns>Returns true if user agree, else - false</returns>
bool did_user_accept(std::string question);

size_t choose_list(uint16_t n, const char * list, std::ostream& out=std::cout,std::istream& in = std::cin);


/// <summary>
/// Class explaning phonebook record
/// </summary>
class PhoneRecord {
protected:
	// There is "friending" of comparison operators below
	// NOTA BENE: case-sensitive
	friend bool operator<(const PhoneRecord& a, const PhoneRecord& b);
	friend bool operator>(const PhoneRecord& a, const PhoneRecord& b);
	friend bool operator==(const PhoneRecord& a, const PhoneRecord& b);
	friend bool operator<=(const PhoneRecord& a, const PhoneRecord& b);
	friend bool operator>=(const PhoneRecord& a, const PhoneRecord& b);

	/// <summary>
	/// case-insensitive record names compairing
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>
	/// -1	if first record name is more than second,
	/// 0	if records names are equal,
	/// 1	if second record name is more than first.
	/// </returns>
	friend int8_t compair(const PhoneRecord& a, const PhoneRecord& b);


	/// <summary>
	/// Filters string (excludes all symbols except digits and '+' if it's the first one)
	/// </summary>
	/// <param name="s">- filtering string</param>
	/// <returns>filtered string</returns>
	std::string filter(const std::string& s);

	/// <summary>
	/// String for nickname
	/// </summary>
	std::string nickname;

	/// <summary>
	/// struct that explains phone number
	/// </summary>
	struct {
		/// <summary>
		/// phone number
		/// </summary>
		uint64_t num : 50;
		/*
		According to E.164 (standard phone number recording format)
		phone numbers should be not longer than 15 digits.
		So greatest phone number is: 999 999 999 999 999.
		Then 50 bits are enough for recording this number,
		because 2^50 = 1 125 899 906 842 624.
		*/

		/// <summary>
		/// Does number includes plus flag
		/// </summary>
		uint64_t plus : 1;
	} number; // object of the nameless struct
public:
	struct Field {
		std::string name;
		std::string value;
	};

	/// <summary>
	/// Number getter
	/// </summary>
	/// <returns>phone number as an std::string</returns>
	std::string getNumber() const;

	/// <summary>
	/// Name getter
	/// </summary>
	/// <returns>nickname</returns>
	std::string getName() const;

	/// <summary>
	/// Constructor with no parameters
	/// </summary>
	PhoneRecord();

	/// <summary>
	/// Constructor with initialization
	/// </summary>
	/// <param name="name">- nickname</param>
	/// <param name="number">- phone number as a std::string</param>
	/// <param name="checknum">= true, flag if we need filter string</param>
	PhoneRecord(std::string name, std::string number, bool checknum=true);

	/// <summary>
	/// Inputs phone record from the stream
	/// </summary>
	/// <param name="input">- input stream</param>
	/// <param name="output">- output stream for prompt</param>
	/// <param name="prompt_name">- prompt for input</param>
	/// <param name="prompt_number">- prompt for input</param>
	void input(
		std::istream& input = std::cin,
		std::ostream& output = std::cout,
		std::string prompt_name = "Input nickname\n>>> ",
		std::string prompt_number = "Input number\n>>> ");

	/// <summary>
	/// Number setter with filtering
	/// </summary>
	/// <param name="number">- std::string, that includes phone number an any format with missprints</param>
	/// <param name="filterstr">= true, flag if we need filter string</param>
	void setNumber(std::string number, bool filterstr = true);

	/// <summary>
	/// Name setter
	/// </summary>
	/// <param name="name">- new nickname</param>
	void setName(std::string name);

	/// <summary>
	/// Prints formated record
	/// </summary>
	/// <param name="name_length">- length of the nickname</param>
	/// <param name="output">- output stream</param>
	/// <param name="filler">fills space with it</param>
	void print(size_t name_length, std::ostream& output, char filler = ' ') const;

	void print_utf(size_t name_length, std::ostream& output = std::cout, char filler=' ') const;
};

// Compairing operators deprications
[[deprecated("Use int8_t compair(const PhoneRecord&, const PhoneRecord&) instead of this")]]
bool operator<(const PhoneRecord& a, const PhoneRecord& b);
[[deprecated("Use int8_t compair(const PhoneRecord&, const PhoneRecord&) instead of this")]]
bool operator>(const PhoneRecord& a, const PhoneRecord& b);
[[deprecated("Use int8_t compair(const PhoneRecord&, const PhoneRecord&) instead of this")]]
bool operator==(const PhoneRecord& a, const PhoneRecord& b);
[[deprecated("Use int8_t compair(const PhoneRecord&, const PhoneRecord&) instead of this")]]
bool operator<=(const PhoneRecord& a, const PhoneRecord& b);
[[deprecated("Use int8_t compair(const PhoneRecord&, const PhoneRecord&) instead of this")]]
bool operator>=(const PhoneRecord& a, const PhoneRecord& b);

/// <summary>
/// Class explaining phonedook
/// </summary>
class Phonebook {
protected:

	/// <summary>
	/// The member of Standard Template Library, 
	/// that storages my phone records
	/// </summary>
	std::vector<PhoneRecord> phbook;


public:

	/// <summary>
	/// adds record by name and number
	/// </summary>
	/// <param name="name"></param>
	/// <param name="number"></param>
	/// <param name="checknum">- should we filter number</param>
	void addRecord(std::string name, std::string number, bool checknum = true);

	/// <summary>
	/// adds the record to the phonebook
	/// </summary>
	/// <param name="r"></param>
	void addRecord(PhoneRecord record);

	/// <summary>
	/// Uses streams to create and add a new record
	/// </summary>
	/// <param name="input">stream</param>
	/// <param name="output">stream</param>
	/// <param name="prompt_name">prompt for name input</param>
	/// <param name="prompt_number">prompt for number input</param>
	void inputRecord(
		std::istream& input = std::cin,
		std::ostream& output = std::cout,
		std::string prompt_name = "Input nickname\n>>> ",
		std::string prompt_number = "Input number\n>>> ");

	/// <summary>
	/// Adds elements from inputs stream, until
	/// reaches record with number "terminator"
	/// </summary>
	/// <param name="terminator"></param>
	/// <param name="input">stream</param>
	/// <param name="output">stream</param>
	/// <param name="prompt_name">prompt for name input</param>
	/// <param name="prompt_number">prompt for number input</param>
	void input(
		std::string terminator = "0",
		std::istream& input = std::cin,
		std::ostream& output = std::cout,
		std::string prompt_name = "Input nickname\n>>> ",
		std::string prompt_number = "Input number\n>>> ",
		std::string exit_q="Do you really want to exit?",
		const char * yes_0_no = "Yes\0No");

	/// <summary>
	/// Adds "amount" elements from inputs stream
	/// </summary>
	/// <param name="amount"></param>
	/// <param name="input">stream</param>
	/// <param name="output">stream</param>
	/// <param name="prompt_name">prompt for name input</param>
	/// <param name="prompt_number">prompt for number input</param>
	void input(
		size_t amount,
		std::istream& input = std::cin,
		std::ostream& output = std::cout,
		std::string prompt_name = "Input nickname\n>>> ",
		std::string prompt_number = "Input number\n>>> ");


	/// <summary>
	/// Input records from file till the end of it
	/// </summary>
	/// <param name="fin">- input file stream</param>
	void inputFromFile(std::ifstream & fin);

	/// <summary>
	/// prints phonebook in the table
	/// </summary>
	/// <param name="name_length">- length of the name column, if '0' got, programm use (max_length_in_phonebook + 3)</param>
	/// <param name="output">stream</param>
	/// <param name="filler">stream</param>
	void print(size_t name_length = 0, std::ostream& output = std::cout, char filler = ' ');

	void print_utf(size_t name_length = 0, std::ostream& output = std::cout, char filler = ' ');

	/// <summary>
	/// Binary search
	/// Find nearest record (lexicographically) in the book
	/// </summary>
	/// <param name="r">- record</param>
	/// <returns>iterator to the record</returns>
	std::vector<PhoneRecord>::iterator findRecord(const PhoneRecord& r);

	/// <summary>
	/// Finds max name length
	/// </summary>
	/// <returns>max name lenght</returns>
	size_t maxNameLength();


	void addCSVRecord(std::istream& stream, const std::vector<std::string>& fields);

	/// <summary>
	/// imports Phonebook from *idk* format using stream
	/// </summary>
	/// <param name="stream"></param>
	void importPhonebook(std::istream& stream);
	/// <summary>
	/// imports Phonebook to *idk* format using stream
	/// </summary>
	/// <param name="stream"></param>
	void exportPhonebook(std::ostream& stream);
	/// <summary>
	/// Deletes record
	/// </summary>
	/// <param name="p_record"> iterator to the record</param>
	void deleteRecord(std::vector<PhoneRecord>::iterator p_record);

	bool isTail(std::vector<PhoneRecord>::iterator p_record);
	bool isHead(std::vector<PhoneRecord>::iterator p_record);
};

#endif