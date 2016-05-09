#ifndef TRAB1_SB_ZAGO_ICARO_TOKEN_SYNTACTIC_ANALYSER
#define TRAB1_SB_ZAGO_ICARO_TOKEN_SYNTACTIC_ANALYSER

#include <vector>
#include "token.h"

class SyntacticAnalyser {
  public:
  	static SyntacticAnalyser& instance();
  	void analyseText(std::vector<Token> text);
  private:
  	SyntacticAnalyser() {}
  	void analyseLine(std::vector<Token> line);
};

#endif