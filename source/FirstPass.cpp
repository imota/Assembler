#include<iostream>
#include "FirstPass.h"


FirstPass::FirstPass() {}
FirstPass::~FirstPass() {}

FirstPass& FirstPass::instance() {
	static FirstPass fp;
	return fp;
}

std::vector<SimbleTableElement>& FirstPass::getSimbleTable() { return simbleTable; }
std::vector<DefinitionTableElement>& FirstPass::getDefinitionTable() { return definitionTable; }
std::vector<UseTableElement>& FirstPass::getUseTable() { return useTable; }

void FirstPass::makePass(std::vector<Token*>& tks){
	tokens = tks;
	writeSimbleTable();
}

void FirstPass::writeSimbleTable(){


}