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

};

struct UseTableElement {
	std::string name;
	uint sumValue;
};

class FirstPass {
public:
	FirstPass();
	~FirstPass();

private:
	std::vector<LineOfFile> textFile;

};








#endif


