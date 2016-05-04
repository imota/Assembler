#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <vector>
#include <unordered_map>
#include "LineOfFile.h"

class Parser {
  public:
  	static Parser& instance();
  	std::vector<LineOfFile> Parse(std::vector<LineOfFile> text);
  private:
  	Parser() {}
  	std::vector<LineOfFile> Parse(LineOfFile line);
};

#endif