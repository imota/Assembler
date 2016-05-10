#ifndef TRAB1_SB_ZAGO_ICARO_SEMANTICANALYSER
#define TRAB1_SB_ZAGO_ICARO_SEMANTICANALYSER

#include<iostream>
#include<string>
#include<vector>
#include "FirstPass.h"
#include "token.h"

class SemanticAnalyser{
public:

	static SemanticAnalyser& instance();
	~SemanticAnalyser() {}
	void makeAnalysis(std::vector<Token*>& tks, std::vector<SimbleTableElement>& st,
					  std::vector<DefinitionTableElement>& dt, std::vector<UseTableElement>& ut);

private:
	std::vector<Token*> tokens;
	std::vector<SimbleTableElement> simbleTable;
	std::vector<DefinitionTableElement> definitionTable;
	std::vector<UseTableElement> useTable;
	uint section_data_address = 0;

	void checkSectionOrder();
	void checkRepeatedLabels();

	void checkMissingLabels();

	void calculateSectionDataAddress();
	void checkInvalidJump();
	bool isJumpOperator(std::string name);
	int returnLabelValue(std::string name);

	std::string getLabelByValue(uint value);
	void checkDivisionZero();
	void checkStop();
	void checkStoreToConst();

	void printError(int line, std::string message, std::string errorType = "SEMANTIC");


};





#endif