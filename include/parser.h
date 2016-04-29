#include <iostream>
#include <vector>

class Parser {
  public:
  	std::vector<std::string> Parse(std::vector<std::string> text);
  private:
  	std::vector<std::string> Parse(std::string line);
};

void teste_parser() {
	Parser p;

	std::string line1 = "LABEL: add one\n";
	std::string line2 = "OTHERLABEL: add two\n";

	std::vector<std::string> text;
	text.push_back(line1); text.push_back(line2);

	std::vector<std::string> tokens = p.Parse(text);
	
	for (int i=0;i<tokens.size();i++)
		std::cout << tokens[i] << std::endl;
}