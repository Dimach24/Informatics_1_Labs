#ifndef MY_UTF_8_CONVERTING_LIB_INCLUDED
#define MY_UTF_8_CONVERTING_LIB_INCLUDED

#include <Windows.h>
#include <iostream>
void UTFconvert(const char str[], size_t n, char* out, char fill_unknown_with = '@');
void UTFconvert(const std::string& str, char* out, char fill_unknown_with = '@');

std::string UTFtoString(const char str[], size_t n, char fill_unknown_with = '@');
std::string UTFtoString(const std::string& str, char fill_unknown_with = '@');

void UTFout(std::ostream& stream, const char str[], size_t n, char fill_unknown_with = '@');

void UTFout(std::ostream& stream, const std::string& str, char fill_unknown_with = '@');
std::string StringToUTF(std::string s);
#endif // !MY_UTF-8_CONVERTING_LIB_INCLUDED


