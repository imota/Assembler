#ifndef TRAB1_SB_ZAGO_ICARO_TRANSLATOR
#define TRAB1_SB_ZAGO_ICARO_TRANSLATOR

#include <vector>
#include "token.h"

class Translator {
  public:
  	void translate(std::vector<Token> original_code);
  private:
  	std::vector<Token> translateToken(Token original_token);
};

#endif