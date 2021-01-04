#pragma once
#include <string>
#include <vector>

int ctoi(int c);

void Utility_StringSpit(const std::string& src, char delim, 
	std::vector<std::string>& out);


int random_number(int min_num, int max_num);
