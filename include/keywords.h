#ifndef TRAB1_SB_ZAGO_ICARO_KEYWORDS
#define TRAB1_SB_ZAGO_ICARO_KEYWORDS

#include <iostream>
#include <string>
#include <unordered_map>

enum assembly_language {
  IA32,
  Invented
};

class KeyWords {
  public:
  	bool isValid(std::string name);
  	int numberOfOperands(std::string name);
  	int opcode(std::string name);
  protected:
  	std::unordered_map<std::string, int> name_to_nofoperands;
  	std::unordered_map<std::string, int> name_to_opcode;

    void createMap(assembly_language language);
    virtual void createIA32() = 0;
    virtual void createInventedAssembly() = 0;
};

class Instructions : public KeyWords {
  public:
  	Instructions(assembly_language language);
  private:
    void createIA32();
    void createInventedAssembly();
};

class Directives : public KeyWords {
  public:
  	Directives(assembly_language language);
  private:
    void createIA32();
    void createInventedAssembly();
};

class Opcodes : public KeyWords {
  public:
    Opcodes(assembly_language language);
  private:
    void createIA32();
    void createInventedAssembly();
};

#endif