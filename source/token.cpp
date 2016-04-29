#include "token.h"

std::string Token::Type() {
	return type;
}

bool TokenCreator::isTokenValid(std::string name) {
	return true;
}

int main() {
	TokenCreator tk;
	
	std::cout << tk.isTokenValid("INPUT") << std::endl;
	
	return 0;
}
