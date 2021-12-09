//utf-8Converting.h
#ifndef MY_UTF_8_CONVERTING_LIB_INCLUDED
#define MY_UTF_8_CONVERTING_LIB_INCLUDED

#include <Windows.h>
#include <iostream>

/// <summary>
/// Converts from the utf-8 to the 1251 codepage
/// </summary>
/// <param name="str">- input string</param>
/// <param name="n">- input string size, 0 if it's NULL-terminated string</param>
/// <param name="out">- a pointer to the output c-string</param>
/// <param name="fill_unknown_with">- char, unknown charc will be filled with in result string</param>
void UTFconvert(const char str[], size_t n, char* out, char fill_unknown_with = '@');

/// <summary>
/// Convert std::string from utf-8 to cp 1251
/// </summary>
/// <param name="str">- input string</param>
/// <param name="out">- a pointer to the output c-string</param>
/// <param name="fill_unknown_with">- char, unknown charc will be filled with in result string</param>
void UTFconvert(const std::string& str, char* out, char fill_unknown_with = '@');

/// <summary>
/// Converts from utf-8 to the cp 1251
/// </summary>
/// <param name="str">input c-string</param>
/// <param name="n">- input string size, 0 if it's NULL-terminated string</param>
/// <param name="fill_unknown_with">- char, unknown charc will be filled with in result string</param>
/// <returns>std::string - result</returns>
std::string UTFtoString(const char str[], size_t n, char fill_unknown_with = '@');

/// <summary>
/// Converts from utf-8 to the cp 1251
/// </summary>
/// <param name="str">input string</param>
/// <param name="fill_unknown_with">- char, unknown charc will be filled with in result string</param>
/// <returns>std::string - result</returns>
std::string UTFtoString(const std::string& str, char fill_unknown_with = '@');

/// <summary>
/// Convert string from cp 1251 to utf-8
/// </summary>
/// <param name="s">input string</param>
/// <returns>std::string as utf-8 string</returns>
std::string StringToUTF(std::string s);
#endif // !MY_UTF-8_CONVERTING_LIB_INCLUDED


