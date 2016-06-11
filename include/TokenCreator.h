#ifndef TRAB1_SB_ZAGO_ICARO_TOKEN_CREATOR
#define TRAB1_SB_ZAGO_ICARO_TOKEN_CREATOR

#include <iostream>
#include <vector>
#include "LineOfFile.h"
#include "token.h"
#include "keywords.h"

class TokenCreator {
  public:
  	static TokenCreator& instance();

  	Token identifyTokenType(Token token);
  private:
    TokenCreator() {}
  	bool isLabel(Token token);
  	bool isInstruction(Token token);
  	bool isDirective(Token token);
};

class IA32_TokenCreator : TokenCreator {

};

class InventedAssembly_TokenCreator : TokenCreator {

};

#endif
