#include "utf-8Converting.h"
void UTFconvert(const char str[], size_t n, char* out, char fill_unknown_with)
{
	if (!n) { n = strlen(str); }
	for (size_t i = 0; i < n; out[i++] = '\0');
	wchar_t* wide_buffer = new wchar_t[n];
	MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, str, -1, wide_buffer, n);
	WideCharToMultiByte(1251, NULL, wide_buffer, -1, out, n, &fill_unknown_with, NULL);
	delete[] wide_buffer;
}
void UTFconvert(const std::string& str, char* out, char fill_unknown_with)
{
	UTFconvert(str.c_str(), str.size(), out, fill_unknown_with);
}


std::string UTFtoString(const char str[], size_t n, char fill_unknown_with)
{
	if (!n) { n = strlen(str); }
	char* buf = new char[n];
	UTFconvert(str, n, buf, fill_unknown_with);
	std::string result = buf;
	delete[] buf;
	return result;
}
std::string UTFtoString(const std::string& str, char fill_unknown_with)
{
	return UTFtoString(str.c_str(), str.size(), fill_unknown_with);
}

void UTFout(std::ostream& stream, const char str[], size_t n, char fill_unknown_with)
{
	if (!n) { n = strlen(str); }
	char* multi_byte_buffer = new char[n];
	UTFconvert(str, n, multi_byte_buffer, fill_unknown_with);
	stream << multi_byte_buffer;
	delete[] multi_byte_buffer;
}
void UTFout(std::ostream& stream, const std::string& str, char fill_unknown_with)
{
	UTFout(stream, str.c_str(), str.size(), fill_unknown_with);
}