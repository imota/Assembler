#ifndef TRAB1_SB_ZAGO_ICARO_TOKEN
#define TRAB1_SB_ZAGO_ICARO_TOKEN

#include <iostream>

class Token {
  public:
    Token(std::string name, int line_number, std::string type = "INVALID");
    std::string Type();
    std::string name;
    int line_number;
    std::string type;
    uint memAddress = -1;
};

#endif
