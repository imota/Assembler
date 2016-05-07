#include "token.h"

Token::Token(std::string name, int line_number, std::string type) : name(name), line_number(line_number), type(type) {}

std::string Token::Type() {
	return type;
}