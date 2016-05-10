#ifndef TRAB1_SB_ZAGO_ICARO_TOKEN_SYNTACTIC_ANALYSER
#define TRAB1_SB_ZAGO_ICARO_TOKEN_SYNTACTIC_ANALYSER

#include <vector>
#include "token.h"
#include "keywords.h"

class SyntacticAnalyser {
  public:
  	static SyntacticAnalyser& instance();
  	void analyseText(std::vector<Token> text);
  private:
  	SyntacticAnalyser() {}
  	void analyseLine(std::vector<Token> line);

  	std::vector<Token> removeLabelIfAny(std::vector<Token> line);
  	int verifyNumberOfOperands(std::vector<Token> line);
  	void verifyOperandsTypes(std::vector<Token> line);
  	void checkForMoreLabels(std::vector<Token> line);
};

#endif