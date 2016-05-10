#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include "PreProcessor.h"
#include "FirstPass.h"
#include "parser.h"
#include "token.h"
#include "TokenCreator.h"
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
			break;
		default:
			std::cout << "No program assembled.\n";
			return "";
	}	
}

std::string chooseOutputFile(){
	std::string name;
	std::cout << "Type the name of the output file: ";
	std::cin >> name;
	//std::string fname = "../";
	//return fname.append(name);
	return name;
}

bool chooseFilesToLink(std::string& str1, std::string& str2){
	std::cout << "Type name of first file to link or type 0 to leave: ";
	std::cin >> str1;
	if(str1 == "0") {
		str2 = str1;
		std::cout << "No files linked\n";
		return 0;
	}
	std::cout << "Type name of second file to link or type 0 to leave: ";
	std::cin >> str2;
	if(str2 == "0") {
		std::cout << "No files linked\n";
		return 0;
	}
	return 1;
}

int main() {
	std::string frname;
	//while(1){

		frname = chooseInputFile();
		//if(frname == "") { break; }
		if(frname == "") {return 0;}
		std::vector<LineOfFile> vector_of_elements = PreProcessor::instance().preProcessFile(frname);
		std::vector<Token> parsed_str = Parser::instance().Parse(vector_of_elements);

		for(int i = 0; i < parsed_str.size(); i++) {
			if(TokenCreator::instance().isTokenValid(parsed_str[i]))
				parsed_str[i] = TokenCreator::instance().identifyTokenType(parsed_str[i]);
			else
				TokenCreator::instance().generateError(parsed_str[i]);
		}

		std::vector<Token*> parsed;
		for(size_t i = 0; i < parsed_str.size(); i++) { parsed.push_back(&parsed_str[i]); }
		FirstPass::instance().makePass(parsed);

		SemanticAnalyser::instance().makeAnalysis(FirstPass::instance().getTokens(), 
												  FirstPass::instance().getSimbleTable(),
												  FirstPass::instance().getDefinitionTable(), 
												  FirstPass::instance().getUseTable());
		
		Synthesizer::instance().synthesize(SemanticAnalyser::instance().getTokens(), 
										  SemanticAnalyser::instance().getSimbleTable(),
										  SemanticAnalyser::instance().getDefinitionTable(), 
										  SemanticAnalyser::instance().getUseTable(), chooseOutputFile());
	//}

	std::string str1, str2;
	if(chooseFilesToLink(str1, str2))
		Linker::instance().linkFiles(str1, str2, chooseOutputFile());

	return 0;
}