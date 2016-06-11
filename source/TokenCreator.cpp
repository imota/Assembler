#include "TokenCreator.h"

TokenCreator& TokenCreator::instance() {
	static TokenCreator tc;
	return tc;
}

bool TokenCreator::isLabel(Token token) {
	return token.name[token.name.size()-1] == ':';
}

bool TokenCreator::isInstruction(Token token) {
	return Instructions(language).isValid(token.name);
}

bool TokenCreator::isDirective(Token token) {
	return Directives(language).isValid(token.name);;
}

bool TokenCreator::isMemoryAddress(Token token) {
	return (token.name[0] == '[' and token.name[token.name.size()-1] == ']');
}

Token TokenCreator::identifyTokenType(Token token, assembly_language language) {
	std::string type;
	this->language = language;
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