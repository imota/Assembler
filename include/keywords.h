#ifndef TRAB1_SB_ZAGO_ICARO_KEYWORDS
#define TRAB1_SB_ZAGO_ICARO_KEYWORDS

#include <iostream>
#include <string>
#include <unordered_map>

class KeyWords {
  public:
  	bool isValid(std::string name);
  	int numberOfOperands(std::string name);
  	int opcode(std::string name);
  protected:
  	std::unordered_map<std::string, int> name_to_nofoperands;
  	std::unordered_map<std::string, int> name_to_opcode;
};

class Instructions : public KeyWords {
  public:
  	Instructions();
};

class Directives : public KeyWords {
  public:
  	Directives();
};

class Opcodes : public KeyWords {
public:
	Opcodes();

};

#endif