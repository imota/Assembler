#ifndef TRAB2_SB_ZAGO_ICARO_TRANSLATOR2
#define TRAB2_SB_ZAGO_ICARO_TRANSLATOR2

#include<vector>
#include<string>
#include "keywords.h"
#include "token.h"
#include "TokenCreator.h"

struct Label{
	Label(std::string n, int a) : name(n), address(a) {}
	std::string name;
	int address;
};
struct Call{
	Call(std::string n, int a, int t) : name(n), address(a), type(t) {}
	std::string name;
	int address;
	int type;
};
struct Jump{
	Jump(std::string n, int a, std::string l) : name(n), address(a), label(l) {}
	std::string name;
	int address;
	std::string label;
};

//This class translates Tokens from Invented assembly into IA32 assembly
class Translator2 {
public:
	static Translator2& instance();
	void translate(std::vector<Token> tks, std::string outputFileName);
	std::string text_bin;
	std::string data_bin;

private:
	std::vector<std::string> defines;
	std::vector<std::string> sectionbss;
	std::vector<std::string> sectiondata;
	std::vector<std::string> sectiontext;
	std::vector<std::string> IOfunctions;
	std::vector<Token> tokens;
	std::vector<size_t (Translator2::*)(int)> functions;
	std::string foutname;
	int address_data, address_text;
	std::vector<Label> labels;
	std::vector<Call> calls;
	std::vector<Jump> jumps;
	std::string IObin;

	size_t add(int i);
	size_t sub(int i);
	size_t mult(int i);
	size_t div(int i);
	size_t jmp(int i);
	size_t jmpn(int i);
	size_t jmpp(int i);
	size_t jmpz(int i);
	size_t copy(int i);
	size_t load(int i);
	size_t store(int i);
	size_t input(int i);
	size_t output(int i);
	size_t stop(int i);
	size_t c_input(int i);
	size_t c_output(int i);
	size_t s_input(int i);
	size_t s_output(int i);

	size_t begin(int i);
	size_t end(int i);
	size_t equ(int i);
	size_t space(int i);
	size_t const_asm(int i);
	size_t section(int i);
	size_t public_asm(int i);
	size_t extern_asm(int i);
	size_t if_asm(int i);

	size_t checkPrevLabel(int i);
	std::string labelName(Token& tk);
	bool isInteger(std::string s);
	void generateAsmFile();
	void init();
	void repLabels();
	int getLabelAddress(std::string s);
};

#endif