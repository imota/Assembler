#ifndef TRAB1_SB_ZAGO_ICARO_TRANSLATOR
#define TRAB1_SB_ZAGO_ICARO_TRANSLATOR

#include <vector>
#include "token.h"
#include "keywords.h"

class Translator {
  public:
  	std::vector<Token> translate(std::vector<Token> original_code);
  private:
  	std::vector<Token> translateToken(Token original_token);
};

#endif