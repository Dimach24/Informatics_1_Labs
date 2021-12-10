//utf-8Converting.cpp
#include "utf-8Converting.h"	//lib header

void UTFconvert(const char str[], size_t n, char* out, char fill_unknown_with)
{
	if (!n) { n = strlen(str); }			// calculate string length if n is a NULL						
	wchar_t* wide_buffer = nullptr;			// buffer declaration
	size_t wn =MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, str, n, wide_buffer, 0);
											// calculate wide char c-string size
	wide_buffer = new wchar_t[wn+1];		// buffer allocation
	wide_buffer[wn] = L'\0';				// end of the string
	MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, str, n, wide_buffer, wn);
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
	wchar_t* wide_buffer=nullptr;		// wchar pointer declaration
	size_t n = MultiByteToWideChar(1251, NULL, s.c_str(), -1, wide_buffer, 0);
										// calculate size of the c-wstring
	wide_buffer = new wchar_t[n+1];		// buffer memory allocation
	wide_buffer[n]=L'\0';				// end of the string
	MultiByteToWideChar(1251, NULL, s.c_str(), -1, wide_buffer, n);
										// converting from codepage 1251 to utf 16 and writing it 
										// to the buffer with saving amount of wchars
	char* buffer = nullptr;				// char pointer declaration
	n=WideCharToMultiByte(CP_UTF8, NULL, wide_buffer, n, buffer, 0, NULL, NULL);
	buffer = new char[n+1];				// buffer allocation
	buffer[n] = '\0';					// end of the string
	WideCharToMultiByte(CP_UTF8, NULL, wide_buffer, n, buffer, n, NULL, NULL);
										// convert string from utf-16 buffer, to the cp 1251 
										// and write it to the second buffer
	delete[] wide_buffer;				// free utf-16 buffer
	std::string result = buffer;		// create std::string and write result c-string to it
	delete[] buffer;					// free result buffer
	return result;						// return result std::string
}