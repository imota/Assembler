#include "syntactic_analyser.h"

bool isNumber(std::string token) {
	for (int i=0;i<token.size();i++) 
		if (!isdigit(token[i]))
			return false;
	return true;
}

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
	line = removeLabelIfAny(line);
	checkForMoreLabels(line);

	if (line[0].type == "DIRECTIVE" or line[0].type == "INSTRUCTION") {
		if (verifyNumberOfOperands(line) >= 0 )
			verifyOperandsTypes(line);
	}
	else {
		std::cout << "Missing Operand at " << line[0].line_number << std::endl;
	}
}

std::vector<Token> SyntacticAnalyser::removeLabelIfAny(std::vector<Token> line) {
	std::vector<Token> new_line;
	int start = line[0].type == "LABEL" ? 1 : 0;
	for (int i=start;i<line.size();i++)
		new_line.push_back(line[i]);
	return new_line;
}

void SyntacticAnalyser::checkForMoreLabels(std::vector<Token> line) {
	for (int i=0;i<line.size();i++) {
		if (line[i].type == "LABEL")
			std::cout << "More than 1 label at " << line[0].line_number << std::endl;
	}
}

int SyntacticAnalyser::verifyNumberOfOperands(std::vector<Token> line) {
	int n_operands = line.size()-1;
	KeyWords k;
	if ((line[0].type == "DIRECTIVE")) k = Directives();
	else k = Instructions();
	
	if (n_operands != k.numberOfOperands(line[0].name)) {
		std::cout << "Wrong number of operands at " << line[0].line_number << std::endl;
		return -1;
	}
	return n_operands;
}

void SyntacticAnalyser::verifyOperandsTypes(std::vector<Token> line) {
	std::string type = line[0].type;

	for (int i=1; i<line.size(); i++) {
		if (type == "INSTRUCTION") {
				if (not(line[i].type == "OPERAND" and not isNumber(line[i].name)))
					std::cout << "Wrong operator types at " << line[i].line_number << std::endl;
		}
		if (type == "DIRECTIVE") {
				if (line[0].name == "SECTION") {
					if (not (line[1].name == "TEXT" or line[1].name == "DATA"))
						std::cout << "Not a valid section at " << line[i].line_number << std::endl;
				}
				else if (line[0].name == "SPACE" or line[0].name == "CONST") {
					if (not(isNumber(line[i].name)))
						std::cout << "Wrong operator types at " << line[i].line_number << std::endl;
				}
				else if (not(line[i].type == "OPERAND")) {
					std::cout << "Wrong operator types at " << line[i].line_number << std::endl;
				} 
			}
	}
}	
