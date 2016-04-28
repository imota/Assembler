#include <iostream>

class Token {
  public:
  	virtual std::string getOpcode(std::string name) = 0;
	std::string Type();
  private:	
  	std::string type;
};

std::string Token::Type() {
	return type;
}


class TokenCreator {
  public:
  	bool isTokenValid(std::string name);
  	//Token generateToken();
  private:
  	//bool isLabel();
  	//bool isInstruction();
  	//bool isOperando();
};

bool TokenCreator::isTokenValid(std::string name) {
	return true;
}

int main() {
	TokenCreator tk;
	
	std::cout << tk.isTokenValid("INPUT") << std::endl;
	
	return 0;
}
