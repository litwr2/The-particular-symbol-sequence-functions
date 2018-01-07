#ifndef NEXT_ID_GENERATOR
#define NEXT_ID_GENERATOR

#include <string>

typedef unsigned long long max_uint;

struct IdentifierFuctions {
	static const std::string id_sign1_set, id_sign2_set;
	static std::string GenerateNextIdentifier(const std::string&);
	static max_uint GetNumberByIdentifier(std::string);
	static std::string GetIdentifierByNumber(max_uint);
	static bool CheckIdentifier(std::string);
};

#endif
