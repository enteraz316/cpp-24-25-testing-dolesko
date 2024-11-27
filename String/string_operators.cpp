#include "string.h"
//Операторы:
std::istream& operator>>(std::istream& in, String& other);

std::ostream& operator<<(std::ostream& out, const String& other);

String operator+(const String& first, const String& second);

bool operator==(const String& first, const String& second);

bool operator!=(const String& first, const String& second);

bool operator<(const String& first, const String& second);

bool operator>(const String& first, const String& second);

bool operator>=(const String& first, const String& second);

bool operator<=(const String& first, const String& second);