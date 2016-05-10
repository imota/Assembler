#include<iostream>
#include<string>
#include "FirstPass.h"


FirstPass::FirstPass() {}
FirstPass::~FirstPass() {}

FirstPass& FirstPass::instance() {
	static FirstPass fp;
	return fp;
}

std::vector<SimbleTableElement>& FirstPass::getSimbleTable() 		 { return simbleTable; }
std::vector<DefinitionTableElement>& FirstPass::getDefinitionTable() { return definitionTable; }
std::vector<UseTableElement>& FirstPass::getUseTable() 				 { return useTable; }
std::vector<Token*>& FirstPass::getTokens()							 { return tokens; }

void FirstPass::makePass(std::vector<Token*>& tks){
	tokens = tks;
	writeTables();
	//printLabels();
	//printTables();
}

bool FirstPass::isInteger(std::string s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

void FirstPass::writeTables(){

	uint memCounter = 0;	//Counts the memory spaces

	for(size_t i = 0; i < tokens.size(); i++){
		tokens[i]->memAddress = memCounter;

		//if(tokens[i]->type == "LABEL"){ //LABEL
		if(tokens[i]->name[tokens[i]->name.size() - 1] == ':'){ //LABEL
			if( i + 1 < tokens.size() ){
				(tokens[i]->name).pop_back();		//Removes ":" from the end of string

				if(tokens[i+1]->name == "EXTERN"){	//LABEL: EXTERN
					SimbleTableElement newSimbleElement(tokens[i]->name, memCounter, false, tokens[i]->line_number);
					simbleTable.push_back(newSimbleElement); //Add the label to simbleTable
					useNames.push_back(tokens[i]->name);		//Label is extern and will be in Use Table
					tokens.erase(tokens.begin()+i+1);
				}
				else{
					SimbleTableElement newSimbleElement(tokens[i]->name, memCounter, true, tokens[i]->line_number);
					simbleTable.push_back(newSimbleElement); //Add the label to simbleTable
				}
			}
			tokens.erase(tokens.begin()+i);
			i--;
		}

		else if(tokens[i]->name == "PUBLIC"){
			if( i + 1 < tokens.size() ){
				DefinitionTableElement newDefElement(tokens[i+1]->name);
				definitionTable.push_back(newDefElement);
				tokens.erase(tokens.begin()+i+1);
				tokens.erase(tokens.begin()+i);
				i--;
			}
		}

		else if (countMem(tokens[i]->name)){	//If the element uses memory space
			if(tokens[i]->name == "SPACE"){
				if( i + 1 < tokens.size() ){
					if(isInteger(tokens[i+1]->name)){
						if( std::stoi(tokens[i+1]->name) > 0 ){
							memCounter += std::stoi(tokens[i+1]->name); //Sums number of memory bytes it uses
							i++;	//Dont analyse next token, it is a parameter for the directive SPACE
						}
					}
					else
						memCounter++;
				}
			}

			else if(tokens[i]->name == "CONST"){
				if( i + 1 < tokens.size() ){
					memCounter++;
					i++;	//Dont analyse next token, it is a parameter for the directive CONST
				}
			}

			else
				memCounter++;
		}
	}

	defineUseTableValues();
	defineDefinitionTableValues();
}

void FirstPass::printLabels() {
	uint line = 0;
	std::cout << std::endl << "After assembling tables:" << std::endl;
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

void FirstPass::printTables(){
	//Simble Table:
	std::cout << std::endl << "Simble table: " << std::endl;
	for(SimbleTableElement& row : simbleTable){
		std::cout << row.name << "\t" << row.value << "\t" << ((row.relative) ? 'r' : 'a' )<< std::endl;
	}

	//Use Table:
	std::cout << std::endl << "Use table: " << std::endl;
	for(UseTableElement& row : useTable){
		std::cout << row.name << "\t" << row.sumAddress << std::endl;
	}

	//Definition Table:
	std::cout << std::endl << "Definition table: " << std::endl;
	for(DefinitionTableElement& row : definitionTable){
		std::cout << row.name << "\t" << row.address << std::endl;
	}

}

bool FirstPass::countMem(std::string& name) {
	if(name != "BEGIN" and name != "END" and name != "EXTERN" and name != "PUBLIC"
	   and name != "PUBLIC" and name[name.size() -1 ] != ':' and name != "SECTION"
	   and name != "TEXT" and name!= "DATA")
		return 1;
	else
		return 0;
}

void FirstPass::defineUseTableValues(){
	for(std::string& str : useNames){
		for(Token*& tk : tokens){
			if(str == tk->name){
				UseTableElement newUseElement(tk->name, tk->memAddress);
				useTable.push_back(newUseElement);
			}
		}
	}
}

void FirstPass::defineDefinitionTableValues(){
	for(DefinitionTableElement& def : definitionTable){
		for(SimbleTableElement& simb : simbleTable){
			if(def.name == simb.name)
				def.address = simb.value;
		}
	}
}
