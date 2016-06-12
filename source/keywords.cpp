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

void KeyWords::createMap(assembly_language language) {
	if (language == Invented)
		createInventedAssembly();
	if (language == IA32)
		createIA32();	
}

std::vector<std::string> KeyWords::inventedToIA32(std::string name) {
	return invented_to_IA32[name];
}

Instructions::Instructions(assembly_language language) {
	createMap(language);
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

void Instructions::createIA32() {
	name_to_nofoperands.emplace("ADD", 2);
	name_to_nofoperands.emplace("SUB", 2);
	name_to_nofoperands.emplace("MULT", 2);
	name_to_nofoperands.emplace("DIV", 2);
	name_to_nofoperands.emplace("CMP", 2);
	name_to_nofoperands.emplace("JE", 1);
	name_to_nofoperands.emplace("JG", 1);
	name_to_nofoperands.emplace("JL", 1);
	name_to_nofoperands.emplace("MOV", 2);

	invented_to_IA32.emplace("ADD", std::vector<std::string>({"ADD", "EAX"}));
	invented_to_IA32.emplace("SUB", std::vector<std::string>({"SUB", "EAX"}));
	invented_to_IA32.emplace("MUL", std::vector<std::string>({"MULT", "EAX"}));
	invented_to_IA32.emplace("DIV", std::vector<std::string>({"SUB", "EDX", "EDX", "DIV", "EAX"}));
	invented_to_IA32.emplace("JMP", std::vector<std::string>({"JMP"}));
	invented_to_IA32.emplace("JMPZ", std::vector<std::string>({"CMP", "EAX", "0", "JE"}));
	invented_to_IA32.emplace("JMPP", std::vector<std::string>({"CMP", "EAX", "0", "JG"}));
	invented_to_IA32.emplace("JMPN", std::vector<std::string>({"CMP", "EAX", "0", "JL"}));
	invented_to_IA32.emplace("LOAD", std::vector<std::string>({"MOV", "EAX"}));
}

Directives::Directives(assembly_language language) {
	createMap(language);
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
	name_to_nofoperands.emplace("IF", 1);
}

void Directives::createIA32() {}

Opcodes::Opcodes(assembly_language language) {
	createMap(language);
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
	name_to_opcode.emplace("C_INPUT", 15);
	name_to_opcode.emplace("C_OUTPUT", 16);
	name_to_opcode.emplace("S_INPUT", 17);
	name_to_opcode.emplace("S_OUTPUT", 18);

	name_to_opcode.emplace("BEGIN", 19);
	name_to_opcode.emplace("END", 20);
	name_to_opcode.emplace("EQU", 21);
	name_to_opcode.emplace("SPACE", 22);
	name_to_opcode.emplace("CONST", 23);
	name_to_opcode.emplace("SECTION", 24);
	name_to_opcode.emplace("PUBLIC", 25);
	name_to_opcode.emplace("EXTERN", 26);
	name_to_opcode.emplace("IF", 27);
}

void Opcodes::createIA32() {}