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
	wchar_t *wide_buffer = nullptr;				// utf16 buffer declaration
	size_t wn = MultiByteToWideChar(1251, NULL, s.c_str(), s.size(), wide_buffer, 0);	
												// calculate buffer size
	wide_buffer = new wchar_t[wn + 1];			// allocate memroy for the buffer
	MultiByteToWideChar(1251, NULL, s.c_str(), s.size(), wide_buffer, wn);
												// convert cp1251 string to the utf-16 string 
												// and write it to the buffer
	wide_buffer[wn] = L'\0';					// end of the string
	char* buffer = nullptr;						// standart buffer allocation
	size_t n = WideCharToMultiByte(CP_UTF8, NULL, wide_buffer, wn, buffer, 0, NULL, NULL);
												// calculate buffer size
	buffer = new char[n + 1];					// allocate memory for the buffer
	WideCharToMultiByte(CP_UTF8, NULL, wide_buffer, wn, buffer, n, NULL, NULL);
												// convert string from utf16 to utf8
	buffer[n] = '\0';							// end of the string
	delete[] wide_buffer;						// free the wide buffer memory 
	std::string result = buffer;				// declaration of the result string with initiaization
	delete[] buffer;							// free the short buffer memry 
	return result;								// return result
}