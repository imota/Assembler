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
	std::vector<SimbleTableElement>& getSimbleTable();
	std::vector<DefinitionTableElement>& getDefinitionTable();
	std::vector<UseTableElement>& getUseTable();
	std::vector<Token*>& getTokens();

private:
	std::vector<Token*> tokens;
	std::vector<SimbleTableElement> simbleTable;
	std::vector<DefinitionTableElement> definitionTable;
	std::vector<UseTableElement> useTable;
	uint section_data_address = 0;

	void calculateSectionDataAddress();
	bool isJumpOperator(std::string name);
	int returnLabelValue(std::string name);
	void removeSectionDirectives();
	std::string getLabelByValue(uint value);
	bool isSectionText(std::string name);
	bool isSectionData(std::string name);
	bool isInteger(std::string s);
	void checkMemAddresses();
	bool isUseTableElement(std::string label);

	void checkSectionOrder();
	void checkRepeatedLabels();
	void checkMissingLabels();
	void checkInvalidJump();
	void checkDivisionZero();
	void checkStop();
	void checkStoreToConst();
	void checkMisplacedDirectivesAndOperators();


	void printError(int line, std::string message, std::string errorType = "SEMANTIC");


};





#endif