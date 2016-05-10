#include<iostream>
#include<vector>
#include<string>
#include "Synthesizer.h"

Synthesizer& Synthesizer::instance() {
	static Synthesizer sy;
	return sy;
}

void Synthesizer::synthesize(std::vector<Token*>& tks, std::vector<SimbleTableElement>& st,
					  std::vector<DefinitionTableElement>& dt, std::vector<UseTableElement>& ut){
	tokens = tks;
	simbleTable = st;
	definitionTable = dt;
	useTable = ut;
}