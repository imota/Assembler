#include "token.h"

std::string Token::Type() {
	return type;
}

bool TokenCreator::isTokenValid(std::string name) {
	for (int i=0; i < name.size(); i++) {
		if (not isalpha(name[i]) and name[i] != '_') {
			return false;
		}
	}
	return true;
}