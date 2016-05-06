#ifndef TRAB1_SB_ZAGO_ICARO_PREPROCESSOR
#define TRAB1_SB_ZAGO_ICARO_PREPROCESSOR

#include<iostream>
#include<string>
#include<vector>
#include "LineOfFile.h"

//Labels defined by directive EQU
struct DefinedLabel{
	DefinedLabel(std::string& n, int v) : name(n), value(v) {}
	std::string name;
	int value;
};

class PreProcessor {
public:
	static PreProcessor& instance();
	~PreProcessor();
	std::vector<LineOfFile>& preProcessFile(std::string frname);
	void printStrings();
private:
	std::string frname;	//name of file to read
	std::vector<LineOfFile> preProcessed; //vector of pre-processed file lines
	std::vector<DefinedLabel> definedLabels;

	PreProcessor() {}
	void changeReadFileName(std::string& newname);
	void readFileToStrings();
	void removeComments();
	void removeDirectivesEquIf();
	void removeEmptySpaces();
	std::vector<LineOfFile>& giveStringVector();

};

bool isSpaceOrTab(char c);

#endif