#include "LexicErrorVerifier.h"

bool LexicErrorVerifier::isTokenValid(Token word) {
	if (word.name.empty())
		return false;

	if (word.name.find("+") != std::string::npos) 
		return isValidSum(word);

	if (isNumber(word.name))
		return true;

	if (startsWithNumber(word.name))
		return false;

	for (int i=0;i<word.name.size();i++) {
		if (isSpecialCharacter(word.name[i]) and word.name[i] != '_') {
			if (not(word.name[i] == ':' and i == word.name.size()-1)) {
				return false;
			}
		}
	}

	return true;
}

bool LexicErrorVerifier::startsWithNumber(std::string token) {
	return isdigit(token[0]);
}

bool LexicErrorVerifier::isNumber(std::string token) {
	int start = token[0] == '-' ? 1:0;
	for (int i=start;i<token.size();i++) 
		if (!isdigit(token[i]))
			return false;
	return true;
}

bool LexicErrorVerifier::isSpecialCharacter(char c) {
	return (not isalpha(c) and not isdigit(c));
}

bool LexicErrorVerifier::isValidSum(Token token) {
	std::vector<std::string> names;
	std::string name_tmp;

	for (int i=0;i<token.name.size();i++) {
		if (token.name[i] != '+') {
			name_tmp = name_tmp + token.name[i];
		}
		else {
			if (name_tmp == "")
				name_tmp = "."; //any invalid character
			names.push_back(name_tmp);
			name_tmp.clear();
		}
	}
	if (name_tmp == "")
		name_tmp = ".";
	names.push_back(name_tmp);

	for (int i=1;i<names.size();i++)
		if (not isNumber(names[i]))	
			return false;

	Token first_element(names[0],token.line_number);
	return isTokenValid(first_element) and not isNumber(first_element.name);
}

void LexicErrorVerifier::generateError(Token word) {
	Error::instance().message(error_type, "Invalid token", word.line_number);
}
