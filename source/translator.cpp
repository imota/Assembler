#include "translator.h"

std::vector<Token> Translator::translate(std::vector<Token> original_code) {
	std::vector<Token> new_code;

	for (int i=0;i<original_code.size();i++) {
		std::vector<Token> translated_token = translateToken(original_code[i]);
		new_code.insert(new_code.end(), translated_token.begin(),translated_token.end());
	}

	return new_code;
}

std::vector<Token> Translator::translateToken(Token original_token) {
	std::vector<Token> translated_token;

	std::vector<std::string> translation;
	if (original_token.Type() == "LABEL") {
		translated_token.push_back(original_token);
		return translated_token;
	}
	else if (Instructions(Invented).isValid(original_token.name))
		translation = Instructions(IA32).inventedToIA32(original_token.name);
	else if (Directives(Invented).isValid(original_token.name))
		translation = Directives(IA32).inventedToIA32(original_token.name);


	for (int i=0;i<translation.size();i++)
		translated_token.push_back(Token(translation[i], original_token.line_number));

	//std::cout << original_token.name << " -> ";
	//for (int i=0;i<translated_token.size();i++)
	//	std::cout << translated_token[i].name << " ";
	//std::cout << std::endl;

	return translated_token;
}