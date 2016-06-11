#ifndef TRAB1_SB_ZAGO_ICARO_LEXIC_ERROR_VERIFIER
#define TRAB1_SB_ZAGO_ICARO_LEXIC_ERROR_VERIFIER

#include <vector>
#include "Error.h"
#include "token.h"
#include "keywords.h"
#include "LineOfFile.h"

class LexicErrorVerifier {
  public:
    LexicErrorVerifier() {};
    bool isTokenValid(Token word);
    void generateError(Token word);


  private:
    bool startsWithNumber(std::string token);
    bool isNumber(std::string token);
    bool isSpecialCharacter(char c);
    bool isValidSum(Token token);

    std::string error_type = "Lexic";
};