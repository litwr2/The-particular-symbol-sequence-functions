#include <iostream>
#include <cstring>
#include "next-id.h"

#define TEST_IT 1

const std::string IdentifierFuctions::id_sign1_set = "ABCEHIKLNOPRSTUWXYZ";
const std::string IdentifierFuctions::id_sign2_set = "123456789";

std::string IdentifierFuctions::GenerateNextIdentifier(const std::string &identifier) {
	int l = identifier.length();
	std::string result(identifier);
	char former = identifier[l - 2], latter = identifier[l - 1];
	if (latter < '9') {
		result[l - 1] = latter + 1;
		return result;
	}
	else if (former < 'Z') {
		while (std::strchr(IdentifierFuctions::id_sign1_set.c_str(), ++former) == 0);
		result[l - 2] = former;
		result[l - 1] = '1';
		return result;
	}
	else {
		if (l > 2) {
			result = GenerateNextIdentifier(result.substr(0, l - 3)) + "-A1";
			if (result.length() < 30)
				return result;
			throw "id overflow";
		}
		else
			return "A1-A1";
	}
}

max_uint IdentifierFuctions::GetNumberByIdentifier(std::string s) {
	max_uint n = 0, m;
	for (;;) {
		double r;
		m = IdentifierFuctions::id_sign1_set.find_first_of(s.substr(0, 1))*9 + IdentifierFuctions::id_sign2_set.find_first_of(s.substr(1, 1));
		r = (double)n*171 + m;
		n = n*171 + m;
		if (r - .5 > n) throw "the number is too large";
		if (s.length() > 2) {
			if (r + .5 > ++n) throw "the number is too large";
			s = s.substr(3, std::string::npos);
		}
		else
			return n;
	}
}

std::string IdentifierFuctions::GetIdentifierByNumber(max_uint n) {
	std::string s;
	max_uint r, f = 0;
	do {
		if (f == 1) n--; else f = 1;
		r = n%171;
		n /= 171;
		s = std::string("-") + IdentifierFuctions::id_sign1_set[r/9] + IdentifierFuctions::id_sign2_set[r%9] + s;
	}
	while (n != 0);
	s = s.substr(1, std::string::npos);
	return s;
}

bool IdentifierFuctions::CheckIdentifier(std::string s) {
	if (s.find_first_not_of(IdentifierFuctions::id_sign1_set + IdentifierFuctions::id_sign2_set + "-") != std::string::npos || s.length() > 29)
		return false;
	for (;;) {
		if (s.find_first_of(IdentifierFuctions::id_sign1_set) != 0 || s.find_first_of(IdentifierFuctions::id_sign2_set) != 1)
			return false;
		if (s.length() > 2) {
			if (s[2] != '-')
				return false;
			s = s.substr(3, std::string::npos);
		}
		else
			return true;
	}
}

#if TEST_IT
int main() { //test our function
	std::string s;
	max_uint n;
	for (;;) {
		try {
			std::cout << "Enter an ID (press Ctrl-C to exit): ";
			std::cin >> s;
			if (!IdentifierFuctions::CheckIdentifier(s)) {
				std::cout << "A wrong ID entered!\n\n";
				continue;
			}
			std::cout << "The next ID = " << IdentifierFuctions::GenerateNextIdentifier(s) << std::endl;
			std::cout << "The entered ID number = " << (n = IdentifierFuctions::GetNumberByIdentifier(s)) << std::endl;
			std::cout << "The ID gotten by its number = " << IdentifierFuctions::GetIdentifierByNumber(n) << std::endl;
			std::cout << std::endl;
		}
		catch (const char *s) {
			std::cout << "Problem: " << s << "\n\n";
		}
	}
	return 0;
}
#endif
