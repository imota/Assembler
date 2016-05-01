#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "PreProcessor.h"

bool isSpaceOrTab(char c){
	if(c == ' ' || c == '\t')
		return 1;
	else
		return 0;
}

PreProcessor::PreProcessor(std::string& frname) : frname(frname) { 
	//preProcessed.push_back(nullptr); 
}

PreProcessor::~PreProcessor() {}

void PreProcessor::changeReadFileName(std::string& newname)  { frname = newname; }
std::vector<LineOfFile>& PreProcessor::giveStringVector() { return preProcessed; }

void PreProcessor::readFileToStrings() {

	std::ifstream ifs(frname);
	std::string line;
	size_t i = 1;

	if(ifs.is_open()){

		while(std::getline(ifs, line)){		//Read line from file
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

		//Remove empty elements
		//In ASCII any char with value less than 21 is not a letter/number/valid special character
		if(preProcessed[i].line[0] < 21 || (preProcessed[i].line).empty()){	//If first character of element is '\n'
			preProcessed.erase(preProcessed.begin() + i);	//Remove element
			i--;
		}

	}
	
}

void PreProcessor::preProcessFile() {
	readFileToStrings();
	//printStrings();
	removeComments();
	//printStrings();
	removeEmptySpaces();
	//printStrings();
}

void PreProcessor::printStrings() {
	for(LineOfFile& eachElement : preProcessed)
		std::cout << eachElement.line;
}
