#ifndef TRAB1_SB_ZAGO_ICARO_PREPROCESSOR
#define TRAB1_SB_ZAGO_ICARO_PREPROCESSOR

#include<iostream>
#include<string>
#include<vector>
#include "LineOfFile.h"

class PreProcessor {
public:
	static PreProcessor& instance();
	~PreProcessor();
	std::vector<LineOfFile>& preProcessFile(std::string frname);
	void printStrings();
private:
	std::string frname;	//name of file to read
	std::vector<LineOfFile> preProcessed; //vector of pre-processed file lines

	PreProcessor() {}
	void changeReadFileName(std::string& newname);
	void readFileToStrings();
	void removeComments();
	void removeEmptySpaces();
	std::vector<LineOfFile>& giveStringVector();

};

bool isSpaceOrTab(char c);

#endif