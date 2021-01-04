#include "Utility.h"
#include <sstream>

int ctoi(int c)
{
	return c - '0';
}

void Utility_StringSpit(const std::string& src, char delim,
	std::vector<std::string>& elems)
{
	std::stringstream ss;
	ss.str(src);
	std::string item;
	while (std::getline(ss, item, delim))
		elems.push_back(item);
}