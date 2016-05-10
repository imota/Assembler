#ifndef TRAB1_SB_ZAGO_ICARO_FIRSTPASS
#define TRAB1_SB_ZAGO_ICARO_FIRSTPASS

#include<iostream>
#include<vector>
#include<string>
#include "PreProcessor.h"
#include "token.h"

struct SimbleTableElement {
	SimbleTableElement(std::string s, uint n, bool r, uint l) : name(s), value(n), relative(r), line_number(l) {}
	std::string name;
	uint value;
	bool relative;

	//These values help with posterior operations
	uint line_number;
	bool isConst = 0;
	float constValue = -1.5;
};

struct DefinitionTableElement{
	DefinitionTableElement(std::string s, int a = -1) : name(s), address(a) {}
	std::string name;
	int address;

};

struct UseTableElement {
	UseTableElement(std::string s, uint a) : name(s), sumAddress(a) {}
	std::string name;
	uint sumAddress;
};

class FirstPass {
public:
	static FirstPass& instance();
	~FirstPass();
	std::vector<SimbleTableElement>& getSimbleTable();
	std::vector<DefinitionTableElement>& getDefinitionTable();
	std::vector<UseTableElement>& getUseTable();
	std::vector<Token*>& getTokens();
	void makePass(std::vector<Token*>& tks);


private:
	std::vector<Token*> tokens;
	std::vector<SimbleTableElement> simbleTable;
	std::vector<DefinitionTableElement> definitionTable;
	std::vector<UseTableElement> useTable;
	std::vector<std::string> useNames;

	FirstPass();
	void writeTables();
	void printLabels();
	void printTables();
	bool countMem(std::string& name);
	void defineUseTableValues();
	void defineDefinitionTableValues();
	bool isInteger(std::string s);

};
#endif


