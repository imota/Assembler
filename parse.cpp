#include <iostream>
#include <Vector>

std::vector<std::string> Parse(std::string line) {
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
	std::string line = "LABEL:\n a add one";
	std::vector<std::string> tokens = Parse(line);
	
	for (int i=0;i<tokens.size();i++)
		std::cout << tokens[i] << std::endl;
}
