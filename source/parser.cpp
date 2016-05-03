#include "parser.h"

Parser& Parser::instance() {
	static Parser p;
	return p;
}

std::vector<std::string> Parser::Parse(std::vector<LineOfFile> text) {
	std::vector<std::string> parsed_text;

	for (int i=0; i < text.size(); i++) {
		std::vector<std::string> parsed_line = Parse(text[i].line);
		parsed_text.insert(parsed_text.end(), parsed_line.begin(), parsed_line.end());

	}
	return parsed_text;
}

std::vector<std::string> Parser::Parse(std::string line) {
	std::vector<std::string> tokens;
	std::string word;

	for(int i=0; line[i] != '\n'; i++) {
		if (line[i] != ' ') {
			word += line[i];
		}
		else {
			tokens.push_back(word);
			word.clear();
		}
	}
	tokens.push_back(word);

	return tokens;
}