#include <iostream>

class Token {
  public:
  	virtual std::string getOpcode(std::string name) = 0;
	std::string Type();
  private:	
  	std::string type;
};

class TokenCreator {
  public:
  	bool isTokenValid(std::string name);
  	//Token generateToken();
  private:
  	//bool isLabel();
  	//bool isInstruction();
  	//bool isOperando();
};