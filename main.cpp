#include<iostream>
#include<fstream>
#include<string>
#include "PreProcessor.h"
#include "FirstPass.h"
#include "parser.h"

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

	std::string frname;
	frname = chooseFile();

	PreProcessor prep(frname);
	prep.preProcessFile();
	//prep.printStrings();
	std::vector<LineOfFile> vector_of_elements = prep.giveStringVector();

	std::vector<std::string> parsed_str = Parser::instance().Parse(vector_of_elements);

	for (int i=0;i<parsed_str.size();i++)
		std::cout << parsed_str[i] << " ";

	return 0;
}