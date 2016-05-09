#ifndef TRAB1_SB_ZAGO_ICARO_KEYWORDS
#define TRAB1_SB_ZAGO_ICARO_KEYWORDS

#include <iostream>
#include <string>
#include <unordered_map>

class KeyWords {
  public:
  	bool isValid(std::string name);
  protected:
  	std::unordered_map<std::string, std::string> map;
};

class Instructions : public KeyWords {
  public:
  	Instructions();
  	std::string getOpcode(std::string name);
};

class Directives : public KeyWords {
  public:
  	Directives();
};

#endif
