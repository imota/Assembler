#include<iostream>
#include<fstream>
#include<string>
#include "PreProcessor.h"
#include "FirstPass.h"
#include "parser.h"
#include "token.h"

std::string chooseFile() {
	int option;
	std::cout << "Test file: \n[1] ../TestFiles/moda.asm\n[2] ../TestFiles/modb.asm\n[3] ../TestFiles/triangulo.asm\nOption: ";
	std::cin >> option;
	switch(option){
		case 1:
			return "../TestFiles/moda.asm";
		case 2:
			return "../TestFiles/modb.asm";
		case 3:
			return "../TestFiles/triangulo.asm";
		default:
			std::cout << "Option not recognized. Program will close now.\n";
			return "";
	}	
}

int main() {

	std::string frname = chooseFile();
	std::vector<LineOfFile> vector_of_elements = PreProcessor::instance().preProcessFile(frname);
	std::vector<Token> parsed_str = Parser::instance().Parse(vector_of_elements);

	TokenCreator tc;

	for (int i=0;i<parsed_str.size();i++) {
		//std::cout << parsed_str[i].name << std::endl;
			tc.isTokenValid(parsed_str[i]);
			//if (tc.isTokenValid(parsed_str[i]))
			//	std::cout << parsed_str[i].name << " - " << parsed_str[i].line_number << std::endl;
			//	int j = 0;	
	}

	return 0;
}