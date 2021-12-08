#include "utf-8Converting.h"	//lib header

void UTFconvert(const char str[], size_t n, char* out, char fill_unknown_with)
{
	if (!n) { n = strlen(str); }			// calculate string length if n is a NULL						
	wchar_t* wide_buffer = new wchar_t[n];	// buffer declaration and allocation
	MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, str, -1, wide_buffer, n);
						// convert string from utf-8 to utf-16 and write it to the buffer
	WideCharToMultiByte(1251, NULL, wide_buffer, -1, out, n, &fill_unknown_with, NULL);
						// convert string from utf-16 to cp1251 and write to the *out
	delete[] wide_buffer;					// free buffer
}


void UTFconvert(const std::string& str, char* out, char fill_unknown_with)
{
	UTFconvert(str.c_str(), str.size(), out, fill_unknown_with);	
	// convert string to the c-string, convert it to the cp1251 and write to the *out
}

std::string UTFtoString(const char str[], size_t n, char fill_unknown_with)
{
	if (!n) { n = strlen(str); }				// if n is a NULL, calculate string lenght
	char* buf = new char[n];					// buffer declaration and allocation
	UTFconvert(str, n, buf, fill_unknown_with);	// convert to the cp 1251 and write it to the buffer
	std::string result = buf;					// result string
	delete[] buf;								// free the buffer
	return result;								// return result
}


std::string UTFtoString(const std::string& str, char fill_unknown_with)
{
	return UTFtoString(str.c_str(), str.size(), fill_unknown_with);	
	// convert string to the c-string, convert it to cp 1251, create std::string and return it
}

std::string StringToUTF(std::string s)
{
	static char MYCHAR = '@';	// unknow chars will be replaced with this char
	size_t n = s.size();		// size of the string
	wchar_t* wide_buffer = new wchar_t[n];
								// the buffer declaration and allocation
	MultiByteToWideChar(1251, MB_PRECOMPOSED, s.c_str(), -1, wide_buffer, n);
								// converting from codepage 1251 to utf 16 and writing it 
								// to the buffer
	char* buffer = new char[n * 4];		// one more buffer
	WideCharToMultiByte(CP_UTF8, NULL, wide_buffer, -1, buffer, 4*n, &MYCHAR, NULL);
								// convert string from utf-16 buffer, to the cp 1251 
								// and write it to the second buffer
	delete[] wide_buffer;		// free utf-16 buffer
	std::string result = buffer;// create std::string and write result c-string to it
	delete[] buffer;			// free result buffer
	return result;				// return result std::string
}