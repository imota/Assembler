#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "PreProcessor.h"
#include "FirstPass.h"
#include "parser.h"
#include "TokenCreator.h"
#include "translator.h"
#include "keywords.h"
#include "translator2.h"

int main(int argc, char* argv[]) {
	if(argc ==3){
		std::string frname(argv[1]);
		std::string foutname(argv[2]);
		std::vector<LineOfFile> vector_of_elements = PreProcessor::instance().preProcessFile(frname);
		std::vector<Token> parsed_str = Parser::instance().Parse(vector_of_elements);

		for(int i = 0; i < parsed_str.size(); i++)
			parsed_str[i] = TokenCreator::instance().identifyTokenType(parsed_str[i], Invented);

		Translator2::instance().translate(parsed_str, foutname);
	}
	else
		std::cout << "Wrong number of arguments!\n";
	return 0;
}