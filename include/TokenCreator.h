#ifndef TRAB1_SB_ZAGO_ICARO_TOKEN_CREATOR
#define TRAB1_SB_ZAGO_ICARO_TOKEN_CREATOR

#include <iostream>
#include <vector>
#include "LineOfFile.h"
#include "token.h"
#include "keywords.h"
#include "Error.h"

class TokenCreator {
  public:
  	static TokenCreator& instance();
    bool isTokenValid(Token word);
    void generateError(Token word);

  	Token identifyTokenType(Token token);
  private:
    TokenCreator() {}
  	bool isLabel(Token token);
  	bool isInstruction(Token token);
  	bool isDirective(Token token);

    bool startsWithNumber(std::string token);
    bool isNumber(std::string token);
    bool isSpecialCharacter(char c);
    bool isValidSum(Token token);
    std::string error_type = "Lexic";
};

#endif
