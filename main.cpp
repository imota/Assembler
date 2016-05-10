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

std::string chooseFile() {
	int option;
	std::cout << "Test file: \n[1] ../TestFiles/moda.asm\n[2] ../TestFiles/modb.asm\n[3] ../TestFiles/triangulo.asm\n[4] ../TestFiles/naofaznada.asm\nOption: ";
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
		default:
			std::cout << "Option not recognized. Program will close now.\n";
			return "";
	}	
}

int main() {

	std::string frname = chooseFile();
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
	
	Synthesizer::instance().synthesize(FirstPass::instance().getTokens(), 
											  FirstPass::instance().getSimbleTable(),
											  FirstPass::instance().getDefinitionTable(), 
											  FirstPass::instance().getUseTable());							  

	return 0;
}