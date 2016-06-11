#include "keywords.h"

bool KeyWords::isValid(std::string name) {
	return name_to_nofoperands.find(name) != name_to_nofoperands.end();
}

int KeyWords::numberOfOperands(std::string name) {
	return name_to_nofoperands[name];
}

int KeyWords::opcode(std::string name){
	return name_to_opcode[name];
}

Instructions::Instructions() {
	createInventedAssembly();
}

void Instructions::createInventedAssembly() {
	name_to_nofoperands.emplace("ADD", 1);
	name_to_nofoperands.emplace("SUB", 1);
	name_to_nofoperands.emplace("MULT", 1);
	name_to_nofoperands.emplace("DIV", 1);
	name_to_nofoperands.emplace("JMP", 1);
	name_to_nofoperands.emplace("JMPZ", 1);
	name_to_nofoperands.emplace("JMPP", 1);
	name_to_nofoperands.emplace("JMPN", 1);
	name_to_nofoperands.emplace("STORE", 1);
	name_to_nofoperands.emplace("LOAD", 1);
	name_to_nofoperands.emplace("COPY", 2);
	name_to_nofoperands.emplace("INPUT", 1);
	name_to_nofoperands.emplace("OUTPUT", 1);
	name_to_nofoperands.emplace("STOP", 0);	
}

void Instructions::createIA32() {}

Directives::Directives() {
	createInventedAssembly();
}

void Directives::createInventedAssembly() {
	name_to_nofoperands.emplace("BEGIN", 0);
	name_to_nofoperands.emplace("END", 0);
	name_to_nofoperands.emplace("EQU", 1);
	name_to_nofoperands.emplace("SPACE", 1); //TODO: Use 0 as well
	name_to_nofoperands.emplace("CONST", 1);
	name_to_nofoperands.emplace("SECTION", 1);
	name_to_nofoperands.emplace("PUBLIC", 1);
	name_to_nofoperands.emplace("EXTERN", 0);	
}

void Directives::createIA32() {}

Opcodes::Opcodes() {

}

void Opcodes::createInventedAssembly() {
	name_to_opcode.emplace("ADD", 1);
	name_to_opcode.emplace("SUB", 2);
	name_to_opcode.emplace("MULT", 3);
	name_to_opcode.emplace("DIV", 4);
	name_to_opcode.emplace("JMP", 5);
	name_to_opcode.emplace("JMPN", 6);
	name_to_opcode.emplace("JMPP", 7);
	name_to_opcode.emplace("JMPZ", 8);
	name_to_opcode.emplace("COPY", 9);
	name_to_opcode.emplace("LOAD", 10);
	name_to_opcode.emplace("STORE", 11);
	name_to_opcode.emplace("INPUT", 12);
	name_to_opcode.emplace("OUTPUT", 13);
	name_to_opcode.emplace("STOP", 14);
}

void Opcodes::createIA32() {}