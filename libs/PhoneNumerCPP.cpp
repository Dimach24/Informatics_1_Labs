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

size_t choose_list(uint16_t n, const char * list, std::ostream& out, std::istream& in)
{
	while (1) {
		const char* s = list;
		for (size_t i = 0; i < n; i++) {
			out << '\t' << i + 1 << ". " << s << '\n';
			s += strlen(s) + 1;
		}
		out << ">>> ";
		std::string answer;
		getline(in, answer);
		uint16_t answer_n = atoi(answer.c_str());
		if (answer_n >= 1 && answer_n <= n) {
			system("cls");
			return answer_n;
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
	std::string name="", number="";		// variables for name and number
	output << prompt_name;			// prompt for input
	while (name == "") {
		getline(input, name, '\n');		// input
	}
	output << prompt_number;		// prompt for input
	while(number==""){
	getline(input, number, '\n');	// input
	}
	setName(name);					// set name
	setNumber(number);				// set number
}
void PhoneRecord::print(size_t name_length, std::ostream& output, char filler) const
{
	std::string name = inflate_string(nickname, name_length, StrAlign::left, filler);	// format name
	std::string num = inflate_string(getNumber(), 20, StrAlign::right, filler);		// format number
	output << name << num << '\n';													// output
}
void PhoneRecord::print_utf(size_t name_length, std::ostream& output, char filler) const
{
	std::string name = UTFtoString(nickname);										// convert from unicode
	name = inflate_string(name, name_length, StrAlign::left, filler);				// format name
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
	size_t al = a.nickname.size(), bl = b.nickname.size();						// characters amount
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
	std::vector<PhoneRecord>::iterator i = findRecord(r);	//find place for record in the book
	phbook.emplace(i, r);	// adds new record to the vector of records
}

void Phonebook::addRecord(PhoneRecord r)
{
	std::vector<PhoneRecord>::iterator i = findRecord(r);	//find place for record in the book
	phbook.emplace(i, r);	// adds new record to the vector of records
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
		output << exit_q<<std::endl;
	} while (choose_list(2,yes_0_no,output)==2);	// continue if user don't want to exit
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

void Phonebook::print(size_t name_length, std::ostream& output, char filler)
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


std::pair<std::string, size_t> get_csv_field(const std::string & s, size_t from, char sep = ',')
{
	std::string result = "";
	bool is_in_quates = false;
	size_t i = from;
	for (; i < s.size() && (is_in_quates || s[i] != sep); i++) {
		if (s[i] == '"') {
			is_in_quates = !is_in_quates;
			continue;
		}
		result = result + s[i];
	}
	return std::pair<std::string, size_t>(result, i + 1);
}
void Phonebook::addCSVRecord(std::istream & stream, const std::vector<std::string>&fields)
{
	std::string buf;
	size_t start_i = 0;
	std::vector<std::string> contact_values;
	getline(stream, buf, '\n');
	while (buf.size() > start_i) {
		std::pair<std::string, size_t> tmp = get_csv_field(buf, start_i);
		contact_values.push_back(tmp.first);
		start_i = tmp.second;
	}
	if (!contact_values.size()) { return; }
	std::string name = "", number = "";
	for (size_t i = 0; i < fields.size(); i++) {
		if (fields[i] == "Name") {
			name = contact_values[i];
		} else if (fields[i] == "Phone 1 - Value") {
			number = contact_values[i];
		}
	}
	size_t start = 0;

	while (1) {
		size_t n = number.find(":::", start); //synonim
		if (n == std::string::npos) { addRecord(name, number.substr(start)); break; }
		addRecord(UTFtoString(name), number.substr(start, n));
		start = n + 3;
	}

}
void Phonebook::importPhonebook(std::istream & stream)
{
	// import from csv file
	std::string buf;
	getline(stream, buf, '\n');
	std::vector<std::string> fields;
	size_t start_i = 0;
	while (buf.size() > start_i) {
		std::pair<std::string, size_t> tmp = get_csv_field(buf, start_i);
		fields.push_back(tmp.first);
		start_i = tmp.second;
	}
	while (!stream.eof()) {
		addCSVRecord(stream, fields);
	}

}

void Phonebook::exportPhonebook(std::ostream& stream)
{
	stream << "Name,Phone 1 - Value" << std::endl;
	for (auto r : phbook) {
		stream << '"' << r.getName() << "\'," << r.getNumber() << std::endl;
	}
}

void Phonebook::deleteRecord(std::vector<PhoneRecord>::iterator p_record)
{
	phbook.erase(p_record);
}

bool Phonebook::isTail(std::vector<PhoneRecord>::iterator p_record)
{
	return p_record==phbook.end();
}
