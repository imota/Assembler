#include "syntactic_analyser.h"

bool isNumber(std::string token) {
	int start = token[0] == '-' ? 1:0;
	for (int i=start;i<token.size();i++) 
		if (!isdigit(token[i]))
			return false;
	return true;
}

bool isNegative(std::string token) {
	return (isNumber(token) and token[0] == '-');
}

SyntacticAnalyser& SyntacticAnalyser::instance() {
	static SyntacticAnalyser sa;
	return sa;
}

std::vector<Token> SyntacticAnalyser::analyseText(std::vector<Token> text) {
	std::vector<Token> new_text;
	std::vector<Token> line;
	for (int i=0; i<text.size()-1; i++) {
		line.push_back(text[i]);
		if (text[i].line_number != text[i+1].line_number) {
			if (analyseLine(line))
				new_text.insert(new_text.end(), line.begin(), line.end());
			line.clear();
		}
	}
	line.push_back(text[text.size()-1]);
	if (analyseLine(line))
		new_text.insert(new_text.end(), line.begin(), line.end());

	return new_text;
}

bool SyntacticAnalyser::analyseLine(std::vector<Token> line) {
	line = removeLabelIfAny(line);
	if (checkForMoreLabels(line))
		return false;

	if (line[0].type == "DIRECTIVE" or line[0].type == "INSTRUCTION") {
		if (verifyNumberOfOperands(line) >= 0 ) {
			if  (not verifyOperandsTypes(line))
				return false;
		}
		else {
			Error::instance().message(error_type, "Wrong number of operands", line[0].line_number);
			return false;
		}
	}
	else
		return false;
	
	return true;
}

std::vector<Token> SyntacticAnalyser::removeLabelIfAny(std::vector<Token> line) {
	std::vector<Token> new_line;
	int start = line[0].type == "LABEL" ? 1 : 0;
	for (int i=start;i<line.size();i++)
		new_line.push_back(line[i]);
	return new_line;
}

bool SyntacticAnalyser::checkForMoreLabels(std::vector<Token> line) {
	for (int i=0;i<line.size();i++) {
		if (line[i].type == "LABEL") {
			Error::instance().message(error_type, "More than 1 label", line[0].line_number);
			return true;
		}
	}
	return false;
}

int SyntacticAnalyser::verifyNumberOfOperands(std::vector<Token> line) {
	int n_operands = line.size()-1;
	KeyWords *k;
	if ((line[0].type == "DIRECTIVE")) k = new Directives(Invented);
	else k = new Instructions(Invented);

	if (line[0].name == "SPACE") {
		if (n_operands == 0)
			return 0;
	}
	
	if (n_operands != k->numberOfOperands(line[0].name)) {
		return -1;	
	}
	return n_operands;
}

bool SyntacticAnalyser::verifyOperandsTypes(std::vector<Token> line) {
	std::string type = line[0].type;

	for (int i=1; i<line.size(); i++) {
		if (type == "INSTRUCTION") {
				if (not(line[i].type == "OPERAND" and not isNumber(line[i].name))) {
					Error::instance().message(error_type, "Wrong operator types", line[0].line_number);
					return false;
				}
		}
		if (type == "DIRECTIVE") {
				if (line[0].name == "SECTION") {
					if (not (line[1].name == "TEXT" or line[1].name == "DATA")) {
						Error::instance().message(error_type, "Not a valid section", line[0].line_number);
						return false;
					}
				}
				else if (line[0].name == "SPACE" or line[0].name == "CONST") {
					if (not(isNumber(line[i].name))) {
						Error::instance().message(error_type, "Wrong operator types", line[0].line_number);
						return false;
					}
					else if (line[0].name == "SPACE" and isNegative(line[i].name)) {
						Error::instance().message(error_type, "SPACE does not accept negative values", line[0].line_number);
						return false;
					}
				}
				else if (not(line[i].type == "OPERAND")) {
					Error::instance().message(error_type, "Wrong operator types", line[0].line_number);
					return false;
				} 
			}
	}
	return true;
}	
