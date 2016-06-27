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
#include "mounter.h"

typedef unsigned char Byte;

int main(int argc, char* argv[]) {
	if(argc == 4){
		std::string frname(argv[1]);
		std::string foutname(argv[2]);
		std::string foutbin(argv[3]);
		std::vector<LineOfFile> vector_of_elements = PreProcessor::instance().preProcessFile(frname);
		std::vector<Token> parsed_str = Parser::instance().Parse(vector_of_elements);

		for(int i = 0; i < parsed_str.size(); i++)
			parsed_str[i] = TokenCreator::instance().identifyTokenType(parsed_str[i], Invented);

		Translator2::instance().translate(parsed_str, foutname);

		Mounter::instance().text = Translator2::instance().text_bin;
		Mounter::instance().data = Translator2::instance().data_bin;
		Mounter::instance().mount(foutbin);
	}
	else
		std::cout << "Wrong number of arguments!\n";
	return 0;
}