#include "translator.h"

void Translator::translate(std::vector<Token> original_code) {
	std::vector<std::string> new_code;

	for (int i=0;i<original_code.size();i++) {
		std::vector<std::string> translated_token = translateToken(original_code[i]);
		new_code.insert(new_code.end(), translated_token.begin(),translated_token.end());
	}
}

std::vector<std::string> Translator::translateToken(Token original_token) {
	std::vector<std::string> translated_token;

	if (Instructions(Invented).isValid(original_token.name)) {
		translated_token = Instructions(IA32).inventedToIA32(original_token.name);
	}
	std::cout << original_token.name << " -> ";
	for (int i=0;i<translated_token.size();i++)
		std::cout << translated_token[i] << " ";
	std::cout << std::endl;

	return translated_token;
}