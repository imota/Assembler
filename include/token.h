#ifndef TRAB1_SB_ZAGO_ICARO_TOKEN
#define TRAB1_SB_ZAGO_ICARO_TOKEN

#include <iostream>
#include "LineOfFile.h"

class Token {
  public:
    Token(std::string name, int line_number);
    virtual std::string getOpcode(std::string name) {}
    std::string Type();
    std::string name;
    int line_number;

  private:	
  	std::string type;
};

class TokenCreator {
  public:
    TokenCreator() {}
  	bool isTokenValid(Token word);
  	//Token generateToken();
  private:
    void generateError(Token word);
  	//bool isLabel();
  	//bool isInstruction();
  	//bool isOperando();

    bool startsWithNumber(std::string token);
    bool isNumber(std::string token);
    bool isSpecialCharacter(char c);
};

#endif