#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <vector>
#include "LineOfFile.h"

class Parser {
  public:
  	std::vector<std::string> Parse(std::vector<LineOfFile> text);
  private:
  	std::vector<std::string> Parse(std::string line);
};

#endif