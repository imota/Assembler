#ifndef TRAB1_SB_ZAGO_ICARO_SYNTHESIZER
#define TRAB1_SB_ZAGO_ICARO_SYNTHESIZER

#include<iostream>
#include<vector>
#include<string>
#include "PreProcessor.h"
#include "FirstPass.h"
#include "parser.h"
#include "token.h"
#include "TokenCreator.h"
#include "SemanticAnalyser.h"




class Synthesizer{
public:
	static Synthesizer& instance();
	~Synthesizer() {}
	void synthesize(std::vector<Token*>& tks, std::vector<SimbleTableElement>& st,
					  std::vector<DefinitionTableElement>& dt, std::vector<UseTableElement>& ut);

private:
	std::vector<Token*> tokens;
	std::vector<SimbleTableElement> simbleTable;
	std::vector<DefinitionTableElement> definitionTable;
	std::vector<UseTableElement> useTable;
	bool error = 0;
	std::string outFileName;

	void printLabels();
	void checkErrors();
};




#endif