#include "translator.h"

void Translator::translate(std::vector<Token> original_code) {
	std::vector<Token> new_code;

	for (int i=0;i<original_code.size();i++) {
		std::vector<Token> translated_token = translateToken(original_code[i]);
		new_code.insert(new_code.end(), translated_token.begin(),translated_token.end());
	}
}

std::vector<Token> Translator::translateToken(Token original_token) {
	std::vector<Token> translated_token;

	
	
	return translated_token;
}