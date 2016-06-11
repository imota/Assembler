#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "PreProcessor.h"
#include "FirstPass.h"
#include "parser.h"
#include "token.h"
#include "TokenCreator.h"
#include "syntactic_analyser.h"
#include "SemanticAnalyser.h"
#include "Synthesizer.h"
#include "Linker.h"

std::string chooseInputFile() {
	int option;
	std::string fname;
	std::cout << "Assemble file: \n[1] ../TestFiles/moda.asm\n[2] ../TestFiles/modb.asm\n"
				"[3] ../TestFiles/triangulo.asm\n[4] ../TestFiles/naofaznada.asm\n"
				"[5] ../TestFiles/zerinho.asm\n[6] Type in the file name\n[0] Go to Linking menu\nOption: ";
	std::cin >> option;
	switch(option){
		case 1:
			return "../TestFiles/moda.asm";
		case 2:
			return "../TestFiles/modb.asm";
		case 3:
			return "../TestFiles/triangulo.asm";
		case 4:
			return "../TestFiles/naofaznada.asm";
		case 5:
			return "../TestFiles/zerinho.asm";
		case 6:
			std::cin >> fname;
			return fname;
		default:
			std::cout << "No program assembled.\n";
			return "";
	}	
}

std::string chooseOutputFile(){
	std::string name;
	std::cout << "Type the name of the output file: ";
	std::cin >> name;
	return name;
}

int main() {
	std::string frname = "../TestFiles/zerinho.asm";
	//frname = chooseInputFile();
	std::vector<LineOfFile> vector_of_elements = PreProcessor::instance().preProcessFile(frname);
	std::vector<Token> parsed_str = Parser::instance().Parse(vector_of_elements);
	for(int i = 0; i < parsed_str.size(); i++)
		parsed_str[i] = TokenCreator::instance().identifyTokenType(parsed_str[i]);

	
		
	return 0;
}