#include<iostream>
#include<sstream>
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
	checkMisplacedDirectivesAndOperators();
	calculateSectionDataAddress();
	checkInvalidJump();
	removeSectionDirectives();

	checkRepeatedLabels();
	checkMissingLabels();

	checkStop();
	checkDivisionZero();
	checkStoreToConst();
	checkMemAddresses();
}

void SemanticAnalyser::removeSectionDirectives(){
	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i]->name == "SECTION" or tokens[i]->name == "TEXT" or tokens[i]->name == "DATA"){
			tokens.erase(tokens.begin() + i);
			i--;
		}
	}
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

//This method returns TRUE if a string only has numerical digits
bool SemanticAnalyser::isInteger(std::string s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

//This method checks for labels used and Operands that were not defined
void SemanticAnalyser::checkMissingLabels() {
	for(Token*& tk : tokens){
		if(tk->type == "OPERAND" and not isInteger(tk->name)){
			std::string name_aux = tk->name;

			size_t foundPlus = name_aux.find("+");
			if(foundPlus != std::string::npos)
				name_aux.erase(foundPlus, name_aux.size() - 1);

			bool found = 0;
			for(SimbleTableElement& st : simbleTable){
				if(name_aux == st.name){
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
	if(name == "JMP" or name == "JMPN" or name == "JMPP" or name == "JMPZ")
		return 1;
	else
		return 0;
	
}

int SemanticAnalyser::returnLabelValue(std::string name){
	int sum_value = 0;
	size_t found = name.find("+");
	std::string name_aux = name;
	if(found != std::string::npos){
		name.erase(found, name.size() - 1);
		name_aux.erase(0,found);
		sum_value = std::stoi(name_aux);
	}
	for(SimbleTableElement& st : simbleTable)
		if(st.name == name){
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
		if(isJumpOperator(tokens[i]->name)){
			if(i + 1 < tokens.size()){
				int labelValue = returnLabelValue(tokens[i+1]->name);
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
			if( (tokens[i+1]->name == labelZero or tokens[i+1]->memAddress == 0) and tokens[i]->name == "DIV")
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

bool SemanticAnalyser::isSectionText(std::string name){
	if(name == "ADD" or name == "SUB" or name == "MULT" or name == "DIV" or 
		name == "JMP" or name == "JMPN" or name == "JMPP" or name == "JMPZ" or 
		name == "COPY" or name == "LOAD" or name == "STORE" or name == "INPUT" or
		name == "OUTPUT" or name == "STOP")
		return 1;
	else
		return 0;

}
bool SemanticAnalyser::isSectionData(std::string name){
	if(name == "SPACE" or name == "CONST")
		return 1;
	else
		return 0;
}

void SemanticAnalyser::checkMisplacedDirectivesAndOperators(){
	bool secText = 0;
	bool secData = 0;
	for(size_t i = 0; i+1 < tokens.size(); i++){
		if(tokens[i]->name == "SECTION" and tokens[i+1]->name == "TEXT"){
			secText = 1; secData = 0;
		}
		else if(tokens[i]->name == "SECTION" and tokens[i+1]->name == "DATA"){
			secData = 1; secText = 0;
		}

		if(secData){
			if(isSectionText(tokens[i]->name)){
				std::string message;
				message.append(tokens[i]->name);
				message.append(" SHOULD BE IN SECTION TEXT");
				printError(tokens[i]->line_number, message);
			}
		}
		else if(secText){
			if(isSectionData(tokens[i]->name)){
				std::string message;
				message.append(tokens[i]->name);
				message.append(" SHOULD BE IN SECTION DATA");
				printError(tokens[i]->line_number, message);
			}
		}
	}
}

void SemanticAnalyser::checkMemAddresses() {
	std::vector<uint> spaceMem;
	uint memCounter = 0;
	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i]->name == "BEGIN" or tokens[i]->name == "END")
			continue;
		else if(tokens[i]->name == "SPACE"){
			if(i+1 < tokens.size()){
				if(isInteger(tokens[i+1]->name)){
					for(int j = 0; j < std::stoi(tokens[i+1]->name); j++){
						spaceMem.push_back(memCounter);
						memCounter++;
					}
				}
				else{
					spaceMem.push_back(memCounter);
					memCounter++;
				}

			}
		}
		else if(not isInteger(tokens[i]->name)){
			memCounter++;
		}
	}

	for(size_t i = 0; i+1 < tokens.size(); i++){
		if(tokens[i]->name == "LOAD"){
			int value = returnLabelValue(tokens[i+1]->name);
			if(value < section_data_address and not isUseTableElement(tokens[i+1]->name))
				printError(tokens[i+1]->line_number, "CANNOT LOAD FROM A LABEL NOT DECLARED IN DATA SECTION");
		}
		else if(tokens[i]->name == "STORE"){
			int value = returnLabelValue(tokens[i+1]->name);
			bool validSpace = 0;
			for(uint space : spaceMem){
				if(value == space){
					validSpace = 1;
					break;
				}
			}
			if(not validSpace){
				std::string message;
				message.append(tokens[i+1]->name);
				message.append(" DOES NOT POINT TO A RESERVED MEMORY ADDRESS");
				printError(tokens[i+1]->line_number, message);
			}
		}
		
	}
}

bool SemanticAnalyser::isUseTableElement(std::string label){
	for(UseTableElement& ut : useTable){
		if(ut.name == label)
			return 1;
	}
	return 0;

}

//This Method prints an error message
//errorType <- SEMANTIC
void SemanticAnalyser::printError(int line, std::string message, std::string errorType){
	if(line > -1)
		std::cout << std::endl << errorType << " ERROR on line " << line << ": " << message << std::endl;
	if(line == -1)
		std::cout << std::endl << errorType << " ERROR: " << message << std::endl;
	
}