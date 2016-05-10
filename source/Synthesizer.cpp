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

	std::cout << "LISTA SINTETIZADOR: " << std::endl;
	printLabels();
}

void Synthesizer::printLabels() {
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