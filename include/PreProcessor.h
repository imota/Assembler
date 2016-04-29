#ifndef TRAB1_SB_ZAGO_ICARO_PREPROCESSOR
#define TRAB1_SB_ZAGO_ICARO_PREPROCESSOR

#include<iostream>
#include<string>
#include<vector>

class PreProcessor {
public:
	PreProcessor(std::string& frname);
	~PreProcessor();
	void changeReadFileName(std::string& newname);
	std::vector<std::string>& giveStringVector();
	void removeComments();
	void removeEmptySpaces();
	void preProcessFile();
	void readFileToStrings();
	void printStrings();




private:
	std::string frname;	//name of file to read
	std::vector<std::string> preProcessed; //vector of pre-processed file lines

};

bool isSpaceOrTab(char c);

#endif