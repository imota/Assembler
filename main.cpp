#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "PreProcessor.h"
#include "FirstPass.h"
#include "parser.h"
#include "TokenCreator.h"
#include "translator.h"
#include "keywords.h"
#include "translator2.h"

std::string chooseInputFile() {
	int option;
	std::string fname;
	std::cout << "Assemble file: \n[1] Type in the file name\n[2] Go to Linking menu\nOption: ";
	std::cin >> option;
	switch(option){
		case 1:
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
	name.insert(0, "../assembled/");
	return name;
}

int main() {
	std::string frname = "../TestFiles/zerinho.asm";

	std::vector<LineOfFile> vector_of_elements = PreProcessor::instance().preProcessFile(frname);
	std::vector<Token> parsed_str = Parser::instance().Parse(vector_of_elements);

	for(int i = 0; i < parsed_str.size(); i++)
		parsed_str[i] = TokenCreator::instance().identifyTokenType(parsed_str[i], Invented);

	Translator t;
	parsed_str = t.translate(parsed_str);
	
	/*for(int i = 0; i < parsed_str.size(); i++)
		parsed_str[i] = TokenCreator::instance().identifyTokenType(parsed_str[i], IA32);

	for (int i=0;i<parsed_str.size();i++) {
		std::cout << parsed_str[i].name << " is " << parsed_str[i].Type() << std::endl;
	}*/

	Translator2::instance().translate(parsed_str);
		
	return 0;
}