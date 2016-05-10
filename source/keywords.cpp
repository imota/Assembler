#include "keywords.h"

bool KeyWords::isValid(std::string name) {
	return map.find(name) != map.end();
}

int KeyWords::numberOfOperands(std::string name) {
	return map[name];
}

Instructions::Instructions() {
	map.emplace("ADD", 1);
	map.emplace("SUB", 1);
	map.emplace("MULT", 1);
	map.emplace("DIV", 1);
	map.emplace("JMP", 1);
	map.emplace("JMPZ", 1);
	map.emplace("JMPP", 1);
	map.emplace("JMPN", 1);
	map.emplace("STORE", 1);
	map.emplace("LOAD", 1);
	map.emplace("COPY", 2);
	map.emplace("INPUT", 1);
	map.emplace("OUTPUT", 1);
	map.emplace("STOP", 0);
}

Directives::Directives() {
	map.emplace("BEGIN", 0);
	map.emplace("END", 0);
	map.emplace("EQU", 1);
	map.emplace("SPACE", 1); //TODO: Use 0 as well
	map.emplace("CONST", 1);
	map.emplace("SECTION", 1);
	map.emplace("PUBLIC", 1);
	map.emplace("EXTERN", 0);
}