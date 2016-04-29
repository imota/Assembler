#include <iostream>
#include <vector>

class Parser {
  public:
  	std::vector<std::string> Parse(std::vector<std::string> text);
  //private:
  	std::vector<std::string> Parse(std::string line);
};

std::vector<std::string> Parser::Parse(std::vector<std::string> text) {
	std::vector<std::string> parsed_text;

	for (int i=0; i < text.size(); i++) {
		std::vector<std::string> parsed_line = Parse(text[i]);
		parsed_text.insert(parsed_text.end(), parsed_line.begin(), parsed_line.end());
	}

	return parsed_text;
}

std::vector<std::string> Parser::Parse(std::string line) {
	std::vector<std::string> tokens;
	std::string word;

	for(int i=0; i<line.size(); i++) {
		if (line[i] != ' ' and i != line.size()-1) {
			word += line[i];
		}
		else {
			tokens.push_back(word);
			word.clear();
		}
	}

	return tokens;
}

int main() {
	Parser p;

	std::string line1 = "LABEL: add one\n";
	std::string line2 = "OTHERLABEL: add two\n";

	std::vector<std::string> text;
	text.push_back(line1); text.push_back(line2);

	std::vector<std::string> tokens = p.Parse(text);
	
	for (int i=0;i<tokens.size();i++)
		std::cout << tokens[i] << std::endl;
}