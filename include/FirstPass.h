#ifndef TRAB1_SB_ZAGO_ICARO_FIRSTPASS
#define TRAB1_SB_ZAGO_ICARO_FIRSTPASS

#include<iostream>
#include<vector>
#include<string>
#include "PreProcessor.h"
#include "token.h"

struct SimbleTableElement {
	SimbleTableElement(std::string s, uint n, bool r) : name(s), value(n), relative(r) {}
	std::string name;
	uint value;
	bool relative;
};

struct DefinitionTableElement{
	DefinitionTableElement(std::string s, uint a) : name(s), address(a) {}
	std::string name;
	uint address;

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
	void makePass(std::vector<Token*>& tks);


private:
	std::vector<Token*> tokens;
	std::vector<SimbleTableElement> simbleTable;
	std::vector<DefinitionTableElement> definitionTable;
	std::vector<UseTableElement> useTable;

	FirstPass();
	void writeTables();

};
#endif


