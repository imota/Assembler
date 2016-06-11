#include "TokenCreator.h"

TokenCreator& TokenCreator::instance() {
	static TokenCreator tc;
	return tc;
}

bool TokenCreator::isLabel(Token token) {
	return token.name[token.name.size()-1] == ':';
}

bool TokenCreator::isInstruction(Token token) {
	return Instructions(Invented).isValid(token.name);
}

bool TokenCreator::isDirective(Token token) {
	return Directives(Invented).isValid(token.name);;
}

Token TokenCreator::identifyTokenType(Token token) {
	std::string type;
	if (isLabel(token))
		type = "LABEL";
	else if (isInstruction(token))
		type = "INSTRUCTION";
	else if(isDirective(token))
		type = "DIRECTIVE";
	else
		type = "OPERAND";
	return Token(token.name, token.line_number, type);
}