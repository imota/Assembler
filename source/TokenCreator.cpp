#include "TokenCreator.h"

bool TokenCreator::isTokenValid(Token word) {
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

void TokenCreator::generateError(Token word) {
	std::cout << "Invalid Token: " << word.name << " at line " << word.line_number << std::endl;
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

bool TokenCreator::isSpecialCharacter(char c) {
	return (not isalpha(c) and not isdigit(c));
}

bool TokenCreator::isValidSum(Token token) {
	std::vector<std::string> names;
	std::string name_tmp;

	for (int i=0;i<token.name.size();i++) {
		if (token.name[i] != '+') {
			name_tmp = name_tmp + token.name[i];
		}
		else {
			if (name_tmp == "")
				name_tmp = ".";
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

bool TokenCreator::isLabel(Token token) {
	return token.name[token.name.size()-1] == ':';
}

bool TokenCreator::isInstruction(Token token) {
	return Instructions().isValid(token.name);
}

bool TokenCreator::isDirective(Token token) {
	return Directives().isValid(token.name);;
}

Token TokenCreator::identifyTokenType(Token token) {
	std::string type;
	if (isLabel(token))
		type = "LABEL";
	else if (isInstruction(token))
		type = "OPERATOR";
	else if(isDirective(token))
		type = "DIRECTIVE";
	else
		type = "OPERAND";
	return Token(token.name, token.line_number, type);
}