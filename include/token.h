#ifndef TRAB1_SB_ZAGO_ICARO_PREPROCESSOR
#define TRAB1_SB_ZAGO_ICARO_PREPROCESSOR

#include <iostream>
#include <ctype.h>

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

#endif