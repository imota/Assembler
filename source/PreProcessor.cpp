#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<locale>
#include "PreProcessor.h"

bool isSpaceOrTab(char c){
	if(c == ' ' or c == '\t' or c == '\r')
		return 1;
	else
		return 0;
}

PreProcessor& PreProcessor::instance() {
	static PreProcessor pp;
	return pp;
}

PreProcessor::~PreProcessor() {}

void PreProcessor::changeReadFileName(std::string& newname)  { frname = newname; }
std::vector<LineOfFile>& PreProcessor::giveStringVector() { return preProcessed; }

void PreProcessor::readFileToStrings() {

	std::ifstream ifs(frname);
	std::string line;
	size_t i = 1;
	std::locale loc;	//To use function toupper

	if(ifs.is_open()){

		while(std::getline(ifs, line)){		//Read line from file
			for(char& c : line) { c = std::toupper(c,loc); } //Converts every character to uppercase
			line.push_back('\n');
			LineOfFile newLine(line, i);
			preProcessed.push_back(newLine);
			i++;
		}

		ifs.close();
	}
	else std::cout << "File not found\n";

}


void PreProcessor::removeComments() {

	
	for(LineOfFile& eachLine : preProcessed){
		size_t found = (eachLine.line).find_first_of(";");	//look for ';'
		if(found != std::string::npos){						//if found
			while((eachLine.line).size() != found)
				(eachLine.line).pop_back();		//Remove it and all characters after it
			(eachLine.line).push_back('\n');
		}
	}
	
	
}

void PreProcessor::removeEmptySpaces() {

	for(size_t i = 0; i < preProcessed.size(); i++){

		//Remove first empty spaces
		while( isSpaceOrTab(preProcessed[i].line[0]) ){
			(preProcessed[i].line).erase((preProcessed[i].line).begin() + 0);
		}

		//Replace tabs for spaces and remove extra spaces
		for(size_t j = 1; j < (preProcessed[i].line).size(); j++){
			if(preProcessed[i].line[j] == '\t')
				preProcessed[i].line[j] = ' ';
			if(preProcessed[i].line[j] == ' ' && preProcessed[i].line[j-1] == ' '){
				(preProcessed[i].line).erase((preProcessed[i].line).begin() + j);
				j--;
			}
		}

		//Remove space between '+'. Example: "R + 1" becomes "R+1"
		for(LineOfFile& eachElement : preProcessed){
			for(size_t i = 0; i < eachElement.line.size(); i++){
				if(eachElement.line[i] == '+'){
					if(i+1 < eachElement.line.size()){
						if( isSpaceOrTab(eachElement.line[i+1]) )
							eachElement.line.erase(eachElement.line.begin() + i + 1);
					}
					if(i-1 >= 0){
						if( isSpaceOrTab(eachElement.line[i-1]) )
							eachElement.line.erase(eachElement.line.begin() + i - 1);
					}
				}
			}
		}

		//Remove empty elements
		//In ASCII any char with value less than 21 is not a letter/number/valid special character
		if(preProcessed[i].line[0] < 21 || (preProcessed[i].line).empty()){	//If first character of element is '\n'
			preProcessed.erase(preProcessed.begin() + i);	//Remove element
			i--;
		}

	}
	
}

std::vector<LineOfFile>& PreProcessor::preProcessFile(std::string frname) {
	this->frname = frname;
	readFileToStrings();
	removeComments();
	removeEmptySpaces();
	printStrings();
	return giveStringVector();
}

void PreProcessor::printStrings() {
	for(LineOfFile& eachElement : preProcessed)
		std::cout << eachElement.line;
}
