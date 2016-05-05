#ifndef TRAB1_SB_ZAGO_ICARO_PARSER
#define TRAB1_SB_ZAGO_ICARO_PARSER

#include <iostream>
#include <vector>
#include <unordered_map>
#include "LineOfFile.h"
#include "token.h"

class Parser {
  public:
  	static Parser& instance();
  	std::vector<Token> Parse(std::vector<LineOfFile> text);

  private:
  	Parser() {}
  	std::vector<Token> Parse(LineOfFile line);
};

#endif