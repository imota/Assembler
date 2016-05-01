#ifndef TRAB1_SB_ZAGO_ICARO_PREPROCESSOR
#define TRAB1_SB_ZAGO_ICARO_PREPROCESSOR

#include<iostream>
#include<string>
#include<vector>

struct LineOfFile{
	LineOfFile(std::string& s, uint n) : line(s), number(n) {}
	std::string line;
	uint number;
};

class PreProcessor {
public:
	PreProcessor(std::string& frname);
	~PreProcessor();
	void changeReadFileName(std::string& newname);
	std::vector<LineOfFile>& giveStringVector();
	void removeComments();
	void removeEmptySpaces();
	void preProcessFile();
	void readFileToStrings();
	void printStrings();




private:
	std::string frname;	//name of file to read
	std::vector<LineOfFile> preProcessed; //vector of pre-processed file lines

};

bool isSpaceOrTab(char c);

#endif