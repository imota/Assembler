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

	//checkMissingLabels();

	//calculateSectionDataAddress();
	//checkInvalidJump();

	checkStop();
	checkDivisionZero();
	checkStoreToConst();
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

//This method checks for labels declared more than once
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

//This method checks for labels used and Operands that were not defined
void SemanticAnalyser::checkMissingLabels() {
	for(Token*& tk : tokens){
		if(tk->type == "OPERAND"){
			bool found = 0;
			for(SimbleTableElement& st : simbleTable){
				if(tk->name == st.name){
					found = 1;
					break;
				}
			}
			if(not found){
				std::string message;
				message.append(tk->name);
				message.append(" NOT DECLARED");
				printError(tk->line_number, message);
			}
		}
	}
}


bool SemanticAnalyser::isJumpOperator(std::string name){
	if(name == "JPM" or name == "JMPN" or name == "JMPP" or name == "JMPZ")
		return 1;
	else
		return 0;
	
}

int SemanticAnalyser::returnLabelValue(std::string name){
	int sum_value = 0;
	for(SimbleTableElement& st : simbleTable)
		if(st.name == name){
			size_t found = name.find("+");
			if(found != std::string::npos){
				name.erase(name.begin(), name.begin() + found);
				sum_value = std::stoi(name);
			}
			return st.value + sum_value;
		}
	return -1;
}

void SemanticAnalyser::calculateSectionDataAddress() {
	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i]->name == "DATA"){
			if( i + 1 < tokens.size()){
				section_data_address = tokens[i+1]->memAddress;
			}
		}
	}
}

//This method checks if a jump is being made to the data section
void SemanticAnalyser::checkInvalidJump(){
	for(size_t i = 0; i < tokens.size(); i++){
		std::cout << "AQQQQUui" << isJumpOperator(tokens[i]->name) << " " << tokens[i]->name << std::endl;;
		if(isJumpOperator(tokens[i]->name)){
			std::cout << "LOOOOOL";
			if(i + 1 < tokens.size()){
				int labelValue = returnLabelValue(tokens[i+1]->name);
				std::cout << "LAAAABEL" << labelValue << std::endl;
				if(labelValue >= section_data_address){
					std::string message;
					message = "CANNOT JUMP TO ";
					message.append(tokens[i+1]->name);
					printError(tokens[i+1]->line_number, message);
				}
			}
		}
	}
}

std::string SemanticAnalyser::getLabelByValue(uint value){
	for(SimbleTableElement& st : simbleTable){
		if(st.value == value)
			return st.name;
	}
	return " ";
}

void SemanticAnalyser::checkDivisionZero(){
	//Find all consts with value 0
	std::vector<std::string> zeroConsts;
	for(size_t i = 0; i + 1 < tokens.size(); i++){
		if(tokens[i]->name == "CONST" and tokens[i+1]->name == "0"){
			std::string constLabel = getLabelByValue(tokens[i]->memAddress);
			zeroConsts.push_back(constLabel);
		}
	}

	for(std::string& labelZero : zeroConsts){
		for(size_t i = 0; i+1 < tokens.size(); i++){
			if(tokens[i+1]->name == labelZero and tokens[i]->name == "DIV")
				printError(tokens[i+1]->line_number, "DIVISION BY ZERO");
		}
	}
}

void SemanticAnalyser::checkStop(){
	uint foundBegin = 0;
	uint foundEnd = 0;
	uint foundStop = 0;
	for(Token*& tk : tokens){
		if(tk->name == "BEGIN"){
			foundBegin++;
			if(foundBegin > 1)
				printError(tk->line_number, "MULTIPLE DECLARATIONS OF DIRETIVE BEGIN");
		}
		else if(tk->name == "END"){
			foundEnd++;
			if(foundEnd > 1)
				printError(tk->line_number, "MULTIPLE DECLARATIONS OF DIRETIVE END");
		}
		else if(tk->name == "STOP")
			foundStop++;
	}

	if(not foundBegin and not foundStop and not foundEnd)
		printError(-1, "NO MODULE DIRECTIVES AND NO OPERATOR STOP DECLARED");
	if(foundBegin and not foundEnd)
		printError(-1, "CODE DECLARES DIRECTIVE BEGIN BUT NO DIRECTIVE END");
	if(not foundBegin and foundEnd)
		printError(-1, "CODE DECLARES DIRECTIVE END BUT NO DIRECTIVE BEGIN");
}

void SemanticAnalyser::checkStoreToConst(){
	//Find all consts
	std::vector<std::string> consts;
	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i]->name == "CONST"){
			std::string constLabel = getLabelByValue(tokens[i]->memAddress);
			consts.push_back(constLabel);
		}
	}

	for(std::string& con : consts){
		for(size_t i = 0; i+1 < tokens.size(); i++){
			if(tokens[i+1]->name == con and tokens[i]->name == "STORE"){
				std::string message = "MODIFICATION OF CONST VALUE ";
				message.append(con);
				printError(tokens[i+1]->line_number, message);
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