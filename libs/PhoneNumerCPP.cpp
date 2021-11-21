//PhoneNumberCPP.cpp

#include "PhoneNumerCPP.h"	// lib header


//								Functions:
std::string inflate_string(std::string s, size_t w, StrAlign a, char filler)
{
	size_t n = s.size();		// 's' length
	switch (a) {				// choose align
	case StrAlign::left:
		if (n > w) {			// if 's' is longer 'w' chars
			s.erase(w, n - w);	// cut it
		}
		for (; n < w; n++) {	// while 's' is shorter 'w' chars
			s = s + filler;		// add filler
		}
		break;
	case StrAlign::right:
		if (n > w) {			// if 's' is longer 
			s.erase(0, n - w);	// cut it
		}
		for (; n < w; n++) {	// while 's' is shorter
			s = filler + s;		// add filler
		}
		break;

	case StrAlign::middle:
		if (n > w) {								// if 's' longer
			s.erase(0, (n - w) / 2);				// cut the head
			s.erase(w, (n - w) / 2 + (n - w) % 2);	// cut the tail
		} else {
			s = inflate_string(s, (w - n) / 2 + n, StrAlign::left, filler);	// add fillers to the right
			s = inflate_string(s, (w - n) / 2 + (w - n) % 2 + s.size(), StrAlign::right, filler);	// add to the left
		}
	}
	return s;					// return result
}

bool did_user_accept(std::string question = "Are you sure?")
{
	std::string answer;							// place for answer
	while (1) {									// always
		std::cout << question << "(y/n)\n>>> ";	// prompt for input
		getline(std::cin, answer, '\n');		// input
		if (answer == "y") {					// if user agree
			return true;						// return true
		} else if (answer == "n") {				// if user disagree
			return false;						// return false
		}										// else repeat
	}
}








//								PhoneRecord methods:


PhoneRecord::PhoneRecord() = default; // default constructor

PhoneRecord::PhoneRecord(std::string name, std::string number, bool checknum)
{
	setName(name);					// set name
	setNumber(number, checknum);	// set number
}

std::string PhoneRecord::filter(const std::string & s)
{
	bool is_it_first = true;
	std::string result;											// place for result
	size_t n = s.size();										// source string size
	for (size_t i = 0; i < n; i++) {							// for each character in source
		char c = s[i];											// place for character
		if (('0' <= c and c <= '9') or (is_it_first and c == '+')) {// if 'c' is good (digit or '+' as the first)
			result += c;										// add 'c' to result string
			is_it_first = false;								// it's not first
		}
	}
	return result;												// return result
}

void PhoneRecord::setNumber(std::string s, bool filterstr)
{
	if (filterstr) {						//if we need filter string
		s = filter(s);						// filter string
	}
	if (s.size()) {
		number.plus = (s[0] == '+');			// set plus if it's necessary
												// else set no plus
		number.num = std::stoll(s);				// set number
	} else {	
		number = { 0,0 };	// fill number with 0
	}
}

void PhoneRecord::setName(std::string s) { nickname = s; }	//  set nickname

std::string PhoneRecord::getNumber()const
{
	std::string res;									// string for result
	if (number.plus) { res = "+"; } else { res = ""; }	// if plus add '+' to res
	res = res + std::to_string(number.num);				// convert number to string and add it to res
	return res;											// return res
}

std::string PhoneRecord::getName()const { return nickname; }	//return nickname

void PhoneRecord::input(std::istream & input, std::ostream & output, std::string prompt_name, std::string prompt_number)
{
	std::string name, number;		// variables for name and number
	output << prompt_name;			// prompt for input
	getline(input, name, '\n');		// input
	output << prompt_number;		// prompt for input
	getline(input, number, '\n');	// input
	setName(name);					// set name
	setNumber(number);				// set number
}

void PhoneRecord::print(size_t name_length, std::ostream & output, char filler) const
{
	std::string n = inflate_string(nickname, name_length, StrAlign::left, filler);	// format name
	std::string num = inflate_string(getNumber(), 20, StrAlign::right, filler);		// format number
	output << n << num << '\n';														// output
}


// There is definition of comparison operators below
// comparison by nickname with standard std::string comparison operators
bool operator<(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname < b.nickname; }
bool operator>(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname > b.nickname; }
bool operator==(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname == b.nickname; }
bool operator<=(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname <= b.nickname; }
bool operator>=(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname >= b.nickname; }









//								 Phonebook methods:

std::vector<PhoneRecord>::iterator Phonebook::findPlaceForRecord(const PhoneRecord & r)
{
	for (std::vector<PhoneRecord>::iterator i = phbook.begin(); i != phbook.end(); i++) {
		if (*i > r) {	//if i becomes less (lexicographically) than new record
			return i;
		}
	}
	return phbook.end();
}

void Phonebook::addRecord(std::string name, std::string number, bool checknum)
{
	PhoneRecord r(name, number);								// create record
	std::vector<PhoneRecord>::iterator i = findPlaceForRecord(r);	//find place for record in the book
	phbook.emplace(i, r);	// adds new record to the list of records
}

void Phonebook::addRecord(PhoneRecord r)
{
	std::vector<PhoneRecord>::iterator i = findPlaceForRecord(r);	//find place for record in the book
	phbook.emplace(i, r);	// adds new record to the list of records
}

void Phonebook::inputRecord(std::istream & input, std::ostream & output, std::string prompt_name, std::string prompt_number)
{
	PhoneRecord r;	// place for input
	r.input();		// input
	addRecord(r);	// adding result
}

void Phonebook::input(std::string terminator, std::istream & input, std::ostream & output, std::string prompt_name, std::string prompt_number)
{
	PhoneRecord r;											// place for result
	do {
		while (true) {										// always
			r.input(input, output, prompt_name, prompt_number);	// input record
			if (r.getNumber() == terminator) { break; }		// if it's end od the input ask user if he really wanto to exit
			addRecord(r);									// add record to the list
		}
	} while (!did_user_accept("Do you really want to exit?"));	// continue if user don't want to exit
}

void Phonebook::input(size_t amount, std::istream & input, std::ostream & output, std::string prompt_name, std::string prompt_number)
{
	PhoneRecord r;							// place for input
	for (size_t i = 0; i < amount; i++) {	// for 'amount' records
		r.input(input, output, prompt_name, prompt_number);	// input
		addRecord(r);						// add record to the list
	}
}

void Phonebook::print(size_t name_length, std::ostream & output, char filler)
{
	output << "Printing phonebook with " << phbook.size() << " records:\n";					// message
	output << " #   " << " name" << inflate_string("number ", name_length + 16, StrAlign::right) << '\n';	// table header
	size_t n = 0;																			// counter
	for (std::vector<PhoneRecord>::iterator i = phbook.begin(); i != phbook.end(); i++) {		// for each record in records
		output << ' ' << inflate_string(std::to_string(++n), 4);							// print # of element
		(*i).print(name_length, output, filler);											// print table row
	}
}
