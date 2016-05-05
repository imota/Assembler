#ifndef TRAB1_SB_ZAGO_ICARO_FIRSTPASS
#define TRAB1_SB_ZAGO_ICARO_FIRSTPASS

#include<iostream>
#include<vector>
#include<string>
#include "PreProcessor.h"


struct SimbleTableElement {
	std::string name;
	uint value;
	bool relative;
};

struct DefinitionTableElement{
	std::string name;
	uint address;

};

struct UseTableElement {
	std::string name;
	uint sumAddress;
};

class FirstPass {
public:
	static FirstPass& instance();
	~FirstPass();

private:
	std::vector<*Token> textFile;
	std::vector<SimbleTableElement> simbleTable;
	std::vector<DefinitionTableElement> definitionTable;
	std::vector<UseTableElement> useTable;

	FirstPass();

};
#endif


