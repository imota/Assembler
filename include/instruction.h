#ifndef TRAB1_SB_ZAGO_ICARO_PREPROCESSOR
#define TRAB1_SB_ZAGO_ICARO_PREPROCESSOR

#include <iostream>
#include <string>
#include <unordered_map>

class Instructions {
  public:
  	Instructions();
	bool isValid(std::string name);
	std::string getOpcode(std::string name);
  private:
  	std::unordered_map<std::string, std::string> opcode_map;
};

#endif