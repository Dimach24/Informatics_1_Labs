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

size_t choose_list(uint16_t n, const char* list, std::ostream& out, std::istream& in)
{
	while (1) {											// always
		const char* s = list;							// pointer to the first char of the string
		for (size_t i = 0; i < n; i++) {				// for natural numbers from 1 to n
			out << '\t' << i + 1 << ". " << s << '\n';	// output option with number
			s += strlen(s) + 1;							// set pointer to the next option start
		}
		out << ">>> ";									// prompt for input
		std::string answer;								// string for the answer
		getline(in, answer);							// get choice
		uint16_t answer_n = atoi(answer.c_str());		// convert answer from string to the int
		if (answer_n >= 1 && answer_n <= n) {			// if choice is correct
			system("cls");								// clear console
			return answer_n;							// return choice
		}
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
	std::string name = "", number = "";		// variables for name and number
	output << prompt_name;			// prompt for input
	while (name == "") {
		getline(input, name, '\n');		// input
	}
	output << prompt_number;		// prompt for input
	while (number == "") {
		getline(input, number, '\n');	// input
	}
	setName(name);					// set name
	setNumber(number);				// set number
}
void PhoneRecord::print(size_t name_length, std::ostream & output, char filler) const
{
	std::string name = inflate_string(nickname, name_length, StrAlign::left, filler);	// format name
	std::string num = inflate_string(getNumber(), 20, StrAlign::right, filler);		// format number
	output << name << num << '\n';													// output
}


// There is definition of comparison operators below
// comparison by nickname with standard std::string comparison operators
// NOTA BENE: case-sensitive
bool operator<(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname < b.nickname; }
bool operator>(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname > b.nickname; }
bool operator==(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname == b.nickname; }
bool operator<=(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname <= b.nickname; }
bool operator>=(const PhoneRecord & a, const PhoneRecord & b) { return a.nickname >= b.nickname; }

int8_t compair(const PhoneRecord & a, const PhoneRecord & b)
{
	size_t al = a.nickname.size(), bl = b.nickname.size();					// characters amount
	for (size_t ai = 0, bi = 0; ai < al && bi < bl; ai++, bi++) {			// for each char
		char ac = tolower(a.nickname[ai]), bc = tolower(b.nickname[bi]);	// changing case if it needs
		if (ac > bc) {
			// if current a char is more than current b char
			return 1;
		} else if (ac < bc) {
			// if current b char is more than current a char
			return -1;
		}
	}
	if (al == bl) { return 0; }		// equal strings
	if (al < bl) { return -1; }		// a is substr of b
	return 1;						// b is substr of a
}







//								 Phonebook methods:

void Phonebook::addRecord(std::string name, std::string number, bool checknum)
{
	PhoneRecord r(name, number);								// create record
	std::vector<PhoneRecord>::iterator i = findRecord(r);		//find place for record in the book
	phbook.emplace(i, r);								// adds new record to the vector of records
}

void Phonebook::addRecord(PhoneRecord r)
{
	std::vector<PhoneRecord>::iterator i = findRecord(r);	//find place for record in the book
	phbook.emplace(i, r);							// adds new record to the vector of records
}

void Phonebook::inputRecord(std::istream & input, std::ostream & output, std::string prompt_name, std::string prompt_number)
{
	PhoneRecord r;	// place for input
	r.input();		// input
	addRecord(r);	// adding result
}

void Phonebook::input(std::string terminator, std::istream & input, std::ostream & output, std::string prompt_name, std::string prompt_number, std::string exit_q, const char* yes_0_no)
{
	PhoneRecord r;											// place for result
	do {
		while (true) {										// always
			r.input(input, output, prompt_name, prompt_number);	// input record
			if (r.getNumber() == terminator) { break; }		// if it's end od the input ask user if he really wanto to exit
			addRecord(r);									// add record to the vector
		}
		output << exit_q << std::endl;
	} while (choose_list(2, yes_0_no, output) == 2);	// continue if user don't want to exit
}
void Phonebook::inputFromFile(std::ifstream & fin)
{
	PhoneRecord r;						// buffer PhoneRecord
	while (fin.good()) {				// while there is no EOF
		r.input(fin, std::cout, "", "");	// input record
		addRecord(r);					// add record to the phonebook
	}
}
void Phonebook::input(size_t amount, std::istream & input, std::ostream & output, std::string prompt_name, std::string prompt_number)
{
	PhoneRecord r;							// place for input
	for (size_t i = 0; i < amount; i++) {	// for 'amount' records
		r.input(input, output, prompt_name, prompt_number);	// input
		addRecord(r);						// add record to the vector
	}
}

void Phonebook::print(size_t name_length, std::ostream & output, char filler)
{
	if (!name_length) {						// if zero
		name_length = maxNameLength() + 3;	// use max name leght
	}
	output << " #   " << " name" << inflate_string("number ", name_length + 16, StrAlign::right) << '\n';	// table header
	size_t n = 0;																			// counter
	for (std::vector<PhoneRecord>::const_iterator i = phbook.cbegin(); i != phbook.cend(); i++) {		// for each record in records
		output << ' ' << inflate_string(std::to_string(++n), 4);							// print # of element
		(*i).print(name_length, output, filler);											// print table row
	}
}



std::vector<PhoneRecord>::iterator Phonebook::findRecord(const PhoneRecord & rec)
{
	if (!phbook.size()) { return phbook.begin(); }			// if phonebook is empty - push first
	size_t l = static_cast<size_t>(-1ll), r = phbook.size();// l=0xFFF...F=-1 - left border, r - right border
	size_t m;												// middle
	while (r - l > 1) {										// while element is not found
		m = r + l;											//
		m /= 2;												// middle index calculated
		if (compair(phbook[m], rec) != -1) {				// if searching placed before
			r = m;											// move right border
		} else {											// else
			l = m;											// move left border
		}
	}
	return phbook.begin() + 1 + l;							// return iterator to this element
}

size_t Phonebook::maxNameLength()
{
	size_t mnl = 0;								// current max, min string size is 0
	for (auto record : phbook) {				// for each record in phbook
		size_t tmp = record.getName().size();	// get name length
		if (mnl < tmp) {						// if current max is less then the record name length
			mnl = tmp;							// make the current max equal to the record name length
		}
	}
	return mnl;									// return result
}


std::pair<std::string, size_t> getCSVField(const std::string & s, size_t from, char sep)
{
	std::string result = "";			// string for result
	bool is_in_quotes = false;			// is there quote before
	size_t i = from;					// index of the first checking char
	for (; i < s.size() && (is_in_quotes || s[i] != sep); i++) {
		// for each char in quotes or in the string or before 'sep' char
		if (s[i] == '"') {	// if there is the quote here
			is_in_quotes = !is_in_quotes;	// switch the flag
			continue;						// continue
		}									//else
		result = result + s[i];				// add char to result string
	}
	return std::pair<std::string, size_t>(result, i + 1);	// pair of the csv field and index of the next one
}

void Phonebook::addCSVRecord(std::istream & stream, const std::vector<std::string>&fields)
{
	std::string buf;							// buffer string
	size_t start_i = 0;							// index of the current field start
	std::vector<std::string> contact_values;	// fields values vector
	getline(stream, buf, '\n');					// get contact fields to the buffer
	while (buf.size() > start_i) {				// while end of the line is not reached
		std::pair<std::string, size_t> tmp = getCSVField(buf, start_i);
		// get field
		contact_values.push_back(tmp.first);	// add the field
		start_i = tmp.second;					// set next field start index
	}
	if (!contact_values.size()) { return; }		// exit if it is the empty line
	std::string name = "", number = "";			// strings for name and number
	for (size_t i = 0; i < fields.size(); i++) {// for each field
		if (fields[i] == "Name") {				// if it's name field
			name = contact_values[i];			// copy to name string
		} else if (fields[i] == "Phone 1 - Value") {	//if it's number field
			number = contact_values[i];			// copy to the number string
		}
	}
	size_t start = 0;							// start index in the number string			
	name = UTFtoString(name);					// convert name string according to 1251 codepage
	if (number.find(":::") != std::string::npos) {	// if more than 1 number defined
		while (1) {									// always
			size_t i = 1;
			size_t n = number.find(":::", start);	// look for the second number
			if (n == std::string::npos) {			// if there is not more numbers
				addRecord(name+" ("+std::to_string(i++)+")", number.substr(start));
													// add record with this number
				break;								// exit
			}										// else
			addRecord(name, number.substr(start, n));//split the string and add record with this number
			start = n + 3;							// next time start with next number
		}
	} else {
		addRecord(name, number);					// add record
	}

}
void Phonebook::importPhonebook(std::istream & stream)
{
	std::string buf;							// string bufer
	getline(stream, buf, '\n');					// get string
	std::vector<std::string> fields;			// vector for csv fields
	size_t start_i = 0;							// the field strart index
	while (buf.size() > start_i) {				// while it's not the end of the string
		std::pair<std::string, size_t> tmp = getCSVField(buf, start_i);
		// get this field and index of the next one
		fields.push_back(tmp.first);			// add the field name to the fields vector
		start_i = tmp.second;					// set next field start index
	}
	while (!stream.eof()) {						// while it's not the end of the file
		addCSVRecord(stream, fields);			// add record with fields names from vector and
												// field values from the .csv stream
	}

}

void Phonebook::exportPhonebook(std::ostream & stream)
{
	stream << StringToUTF("Name,Phone") << std::endl;			// csv header
	for (auto r : phbook) {									// for each record in phonebook
		stream << StringToUTF('"' + r.getName() + "\"," + r.getNumber()) << std::endl;
		// make csv representation of the record,
		// convert it from the 1251 codepage to the UTF-8
		// and write it to the stream
	}
}

void Phonebook::deleteRecord(std::vector<PhoneRecord>::iterator p_record)
{
	phbook.erase(p_record);	// delete recerd from the vector by iterator
}

bool Phonebook::isTail(std::vector<PhoneRecord>::iterator p_record)
{
	return p_record == phbook.end();	// is the iterator the end iterator
}
bool Phonebook::isHead(std::vector<PhoneRecord>::iterator p_record)
{
	return p_record == phbook.begin();	// is it the first element
}

bool Phonebook::isEmpty()
{
	return phbook.empty();
}
