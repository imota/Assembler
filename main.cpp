#include<iostream>
#include<fstream>
#include<string>
#include "PreProcessor.h"


int main() {

	std::string frname; //Name of the file to read

	//std::cout << "Give the name of the file to read: ";
	//std::cin >> frname;
	int option;
	std::cout << "Test file: \n[1] ../TestFiles/moda.asm\n[2] ../TestFiles/modb.asm\n[3] ../TestFiles/triangulo.asm\n Option: ";
	std::cin >> option;
	switch(option){
		case 1:
			frname = "../TestFiles/moda.asm";
			break;
		case 2:
			frname = "../TestFiles/modb.asm";
			break;
		case 3:
			frname = "../TestFiles/triangulo.asm";
			break;
		default:
			std::cout << "Option not recognized. Program will close now.\n";
			return 0;
			break;
	}

	PreProcessor prep(frname);
	prep.preProcessFile();
	//prep.printStrings();
	std::vector<std::string> vector_of_strings = prep.giveStringVector();



	return 0;
}