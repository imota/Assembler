#ifndef TRAB1_SB_ZAGO_ICARO_TOKEN_SYNTACTIC_ANALYSER
#define TRAB1_SB_ZAGO_ICARO_TOKEN_SYNTACTIC_ANALYSER

#include <vector>
#include "token.h"
#include "keywords.h"
#include "Error.h"

class SyntacticAnalyser {
  public:
  	static SyntacticAnalyser& instance();
  	std::vector<Token> analyseText(std::vector<Token> text);
  private:
  	SyntacticAnalyser() {}
  	bool analyseLine(std::vector<Token> line);

  	std::vector<Token> removeLabelIfAny(std::vector<Token> line);
  	int verifyNumberOfOperands(std::vector<Token> line);
  	bool verifyOperandsTypes(std::vector<Token> line);
  	bool checkForMoreLabels(std::vector<Token> line);
    std::string error_type = "Syntactic";
};

#endif