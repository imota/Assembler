#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "Synthesizer.h"
#include "keywords.h"
#include "Error.h"

Synthesizer& Synthesizer::instance() {
	static Synthesizer sy;
	return sy;
}

void Synthesizer::synthesize(std::vector<Token*>& tks, std::vector<SimbleTableElement>& st,
					  std::vector<DefinitionTableElement>& dt, std::vector<UseTableElement>& ut,
					  std::string fname){
	tokens = tks;
	simbleTable = st;
	definitionTable = dt;
	useTable = ut;
	outFileName = fname;
	relatives.clear();

	checkErrors();
	if(!error){
		getRelativeMemAddresses();
		writeToFile();
	}
	else{
		std::cout << std::endl << "Program was not assembled due to errors" << std::endl;
	}
}

int Synthesizer::returnLabelValue(std::string name){
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

void Synthesizer::checkErrors() {
	if(Error::instance().error)
		error = 1;
}

bool Synthesizer::isModule() {
	for(Token*& tk : tokens){
		if(tk->name == "BEGIN")
			return 1;
	}
	return 0;
}

bool Synthesizer::isInteger(std::string s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

void Synthesizer::getRelativeMemAddresses(){
	std::vector<std::string> relativeLabels;
	for(SimbleTableElement& st : simbleTable){
		if(st.relative)
			relativeLabels.push_back(st.name);
	}

	uint memCounter = 0;
	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i]->name == "BEGIN" or tokens[i]->name == "END")		//Dont occupy memory space
			continue;
		if(tokens[i]->name == "SPACE" or tokens[i]->name == "CONST")	//Arrived at SECTION DATA
			break;
		bool isRelative = 0;
		for(std::string r : relativeLabels){
			std::string aux = tokens[i]->name;
			size_t found = aux.find("+");
			if(found != std::string::npos)
				aux.erase(found, aux.size() - 1);
			if(r == aux)
				isRelative = 1;
		}
		if(isRelative)
			relatives.push_back(memCounter);
		memCounter++;
	}
}

void Synthesizer::writeTables(std::ofstream& myfile) {
	//Write Use Table
	myfile << "TABLE USE\n";
	for(UseTableElement& ut : useTable)
		myfile << ut.name << " " << ut.sumAddress << std::endl;

	//Write Definition Table
	myfile << "\nTABLE DEFINITION\n";
	for(DefinitionTableElement& dt : definitionTable)
		myfile << dt.name << " " << dt.address << std::endl;

	//Write Relatives
	myfile << "\nRELATIVE\n";
	for(uint r : relatives)
		myfile << r << " ";

	myfile << "\n\nCODE\n";
}

void Synthesizer::writeCode(std::ofstream& myfile) {
	Opcodes hash;
	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i]->name == "BEGIN" or tokens[i]->name == "END" or isInteger(tokens[i]->name))
			continue;
		else if(tokens[i]->type == "INSTRUCTION")
			myfile << hash.opcode(tokens[i]->name) << " ";
		else if(tokens[i]->type == "OPERAND"){
			myfile << returnLabelValue(tokens[i]->name) << " ";
		}
		else if(tokens[i]->name == "SPACE"){
			if(i + 1 < tokens.size()){
				if( isInteger(tokens[i+1]->name) ){
					for(size_t j = 0; j < std::stoi(tokens[i+1]->name); j++)	//Write as many zeros as there are reserved spaces
						myfile << "0 ";
				}
				else
					myfile << "0 ";
			}
			else
				myfile << "0 ";
		}
		else if(tokens[i]->name == "CONST")
			myfile << tokens[i+1]->name << " ";	//Write const value
	}
}

void Synthesizer::writeToFile() {
	std::ofstream myfile;
	myfile.open(outFileName);
	if(isModule()){
		writeTables(myfile);
	}
	writeCode(myfile);
	myfile.close();
}

void Synthesizer::printLabels() {
	uint line = 0;
	for(Token*& tk : tokens){
		if(tk->line_number != line){
			line = tk->line_number;
			std::cout << "\n" << tk->name;
		}
		else{
			std::cout << " " << tk->name;
		}
	}
}