#ifndef TRAB1_SB_ZAGO_ICARO_TOKEN_CREATOR
#define TRAB1_SB_ZAGO_ICARO_TOKEN_CREATOR

#include <iostream>
#include "keywords.h"
#include "token.h"

class TokenCreator {
  public:
  	static TokenCreator& instance();

  	Token identifyTokenType(Token token); //ok
  private:
    TokenCreator() {}
  	bool isLabel(Token token); //ok
  	bool isInstruction(Token token);
  	bool isDirective(Token token);
};

class IA32_TokenCreator : TokenCreator {

};

class InventedAssembly_TokenCreator : TokenCreator {

};

#endif
