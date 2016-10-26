#include "string_utils.h"
void leftTrimString(std::string& str) {
	str = str.substr(str.find_first_not_of(" \n\r\t"));
}

void rightTrimString(std::string& str) {
	str.erase(str.find_last_not_of(" \n\r\t") - 1);
}

void trimString(std::string& str) {
	rightTrimString(str);
	leftTrimString(str);
}

bool startsWith(std::string& str, std::string test) {
	if (str.size() < test.size()) {
		return false;
	}
	return str.substr(0, test.size()) == test;
}