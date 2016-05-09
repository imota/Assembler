#include<iostream>
#include "SemanticAnalyser.h"



SemanticAnalyser& SemanticAnalyser::instance() {
	static SemanticAnalyser sa;
	return sa;
}


void SemanticAnalyser::makeAnalysis(std::vector<Token*>& tks, std::vector<SimbleTableElement>& st,
					  std::vector<DefinitionTableElement>& dt, std::vector<UseTableElement>& ut){

	tokens = tks;
	simbleTable = st;
	definitionTable = dt;
	useTable = ut;

	checkSectionOrder();
	checkRepeatedLabels();
}

//This method checks if SECTION TEXT appears before SECTION DATA, 
//as well as if they appear more than once or at all
void SemanticAnalyser::checkSectionOrder() {
	bool text_found = 0;
	uint number_sec_text = 0;
	bool data_found = 0;
	uint number_sec_data = 0;

	for(size_t i = 0; i < tokens.size(); i++) {
		if(tokens[i]->name == "SECTION"){
			if(i + 1 < tokens.size()){
				if(tokens[i+1]->name == "TEXT"){
					text_found = 1;
					number_sec_text++;
					if(number_sec_text > 1)
						printError(tokens[i+1]->line_number, "SECTION TEXT APPEARS MORE THAN ONCE");
				}
				else if(tokens[i+1]->name == "DATA"){
					data_found = 1;
					number_sec_data++;
					if(not text_found)
						printError(tokens[i+1]->line_number, "SECTION DATA APPEARS BEFORE SECTION TEXT");
					if(number_sec_data > 1)
						printError(tokens[i+1]->line_number, "SECTION DATA APPEARS MORE THAN ONCE");
				}
			}
		}
	}

	if(not text_found)
		printError(-1, "SECTION TEXT NOT SPECIFIED");
	if(not data_found)
		printError(-1, "SECTION DATA NOT SPECIFIED");
}

void SemanticAnalyser::checkRepeatedLabels() {
	for(size_t i = 0; i < simbleTable.size(); i++){
		for(size_t j = i+1; j < simbleTable.size(); j++){
			if(simbleTable[i].name == simbleTable[j].name){
				std::string message;
				message = "MULTIPLE DEFINITIONS OF LABEL ";
				message.append(simbleTable[j].name);
				printError(simbleTable[j].line_number, message);
			}
		}
	}
}



//This Method prints an error message
//errorType <- SEMANTIC
void SemanticAnalyser::printError(int line, std::string message, std::string errorType){
	if(line > -1)
		std::cout << std::endl << errorType << " ERROR on line " << line << ": " << message << std::endl;
	if(line == -1)
		std::cout << std::endl << errorType << " ERROR: " << message << std::endl;
	
}