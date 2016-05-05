#include "token.h"

Token::Token(std::string name, int line_number) : name(name), line_number(line_number) {}

std::string Token::Type() {
	return type;
}

bool TokenCreator::isTokenValid(Token word) {
	//if (isNumber(word.name))
	//	std::cout << word.name << std::endl;

	for (int i=0;i<word.name.size();i++) {
		if (not isalpha(word.name[i])) {
			if (word.name[i] != '_') {
				if (not (word.name[i] == ':' and i == word.name.size()-1)) {
					std::cout << word.name[i] << std::endl;	
				}
			}
		}
	}
	return true;
}

void TokenCreator::generateError(Token word) {
	std::cout << word.name << std::endl;
}

bool TokenCreator::startsWithNumber(std::string token) {
	return isdigit(token[0]);
}

bool TokenCreator::isNumber(std::string token) {
	for (int i=0;i<token.size();i++) 
		if (!isdigit(token[i]))
			return false;
	return true;
}