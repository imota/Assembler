#include "parser.h"

Parser& Parser::instance() {
	static Parser p;
	return p;
}

std::vector<LineOfFile> Parser::Parse(std::vector<LineOfFile> text) {
	std::vector<LineOfFile> parsed_text;

	for (int i=0; i < text.size(); i++) {
		std::vector<LineOfFile> parsed_line = Parse(text[i]);
		parsed_text.insert(parsed_text.end(), parsed_line.begin(), parsed_line.end());
	}
	return parsed_text;
}

std::vector<LineOfFile> Parser::Parse(LineOfFile line_of_file) {
	std::vector<LineOfFile> tokens;
	std::string word;

	for(int i=0; line_of_file.line[i] != '\n'; i++) {
		if (line_of_file.line[i] != ' ') {
			word += line_of_file.line[i];
		}
		else {
			tokens.push_back(LineOfFile(word, line_of_file.number));
			word.clear();
		}
	}
	tokens.push_back(LineOfFile(word, line_of_file.number));

	return tokens;
}