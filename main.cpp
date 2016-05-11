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
	str1.insert(0, "../assembled/");
	str2.insert(0, "../assembled/");
	return 1;
}

int main() {
	std::string frname;
	while(true){

		frname = chooseInputFile();
		if(frname == "")
			break;
		frname.append(".asm");
		frname.insert(0, "../files/");

		std::vector<LineOfFile> vector_of_elements = PreProcessor::instance().preProcessFile(frname);
		std::vector<Token> parsed_str = Parser::instance().Parse(vector_of_elements);

		bool valid_line = true;
		std::vector<int> invalid_line_n;

		for(int i = 0; i < parsed_str.size(); i++) {
			if(TokenCreator::instance().isTokenValid(parsed_str[i])) {
				parsed_str[i] = TokenCreator::instance().identifyTokenType(parsed_str[i]);
			}
			else {
				TokenCreator::instance().generateError(parsed_str[i]);
				invalid_line_n.push_back(parsed_str[i].line_number);
			}
		}

		for (int i=0;i<parsed_str.size();i++) {
			if (std::find(invalid_line_n.begin(),invalid_line_n.end(),parsed_str[i].line_number) != invalid_line_n.end()) {
				parsed_str.erase(parsed_str.begin() + i);
				i--;
			}
		}

		parsed_str = SyntacticAnalyser::instance().analyseText(parsed_str);

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
		Error::instance().reset();
	}

	std::string str1, str2;
	if(chooseFilesToLink(str1, str2))
		Linker::instance().linkFiles(str1, str2, chooseOutputFile());

	return 0;
}