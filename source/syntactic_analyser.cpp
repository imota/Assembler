#include "syntactic_analyser.h"

SyntacticAnalyser& SyntacticAnalyser::instance() {
	static SyntacticAnalyser sa;
	return sa;
}

void SyntacticAnalyser::analyseText(std::vector<Token> text) {
	std::vector<Token> line;
	for (int i=0; i<text.size()-1; i++) {
		line.push_back(text[i]);
		if (text[i].line_number != text[i+1].line_number) {
			analyseLine(line);
			line.clear();
		}
	}
	line.push_back(text[text.size()-1]);
	analyseLine(line);
}

void SyntacticAnalyser::analyseLine(std::vector<Token> line) {

}