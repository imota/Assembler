#include "keywords.h"

bool KeyWords::isValid(std::string name) {
	return map.find(name) != map.end();
}

Instructions::Instructions() {
	map.emplace("ADD", "01");
	map.emplace("SUB", "02");
	map.emplace("MULT", "03");
	map.emplace("DIV", "04");
	map.emplace("JMP", "05");
	map.emplace("JMPZ", "06");
	map.emplace("JMPP", "07");
	map.emplace("JMPN", "08");
	map.emplace("STORE", "09");
	map.emplace("LOAD", "10");
	map.emplace("COPY", "11");
	map.emplace("INPUT", "12");
	map.emplace("INPUT", "13");
	map.emplace("STOP", "14");
}

std::string Instructions::getOpcode(std::string name) {
	return map[name];
}

Directives::Directives() {
	map.emplace("BEGIN", "0");
	map.emplace("END", "0");
	map.emplace("EQU", "1");
	map.emplace("SPACE", "1"); //TODO: Use 0 as well
	map.emplace("CONST", "1");
}