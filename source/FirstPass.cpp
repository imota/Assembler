#include<iostream>
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

void FirstPass::makePass(std::vector<Token*>& tks){
	tokens = tks;
	writeTables();
}

void FirstPass::writeTables(){

	uint memCounter = 0;	//Counts the memory spaces

	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i]->Type() == "LABEL"){
			if( i + 1 < tokens.size() ){
				(tokens[i]->name).pop_back();	//Removes ":" from the end of string
				if(tokens[i+1]->name == "EXTERN"){
					SimbleTableElement newSimbleElement(tokens[i]->name, memCounter, false);
					simbleTable.push_back(newSimbleElement); //Add the label to simbleTable
					UseTableElement newUseElement(tokens[i]->name, memCounter);
					useTable.push_back(newUseElement);		//Add the label to useTable
					tokens.erase(tokens.begin()+i+1);
				}
				else{
					SimbleTableElement newSimbleElement(tokens[i]->name, memCounter, true);
					simbleTable.push_back(newSimbleElement); //Add the label to simbleTable
				}
			}
			tokens.erase(tokens.begin()+i);
			i--;
		}	
	}
}