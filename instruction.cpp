#include <iostream>
#include <string>
#include <unordered_map>

class Instructions {
  public:
  	Instructions();
	bool isValid(std::string name);
	std::string getOpcode(std::string name);
  private:
  	std::unordered_map<std::string, std::string> opcode_map;
};

Instructions::Instructions() {
	opcode_map.emplace("ADD", "01");
	opcode_map.emplace("SUB", "02");
	opcode_map.emplace("MULT", "03");
	opcode_map.emplace("DIV", "04");
	opcode_map.emplace("JMP", "05");
	opcode_map.emplace("JMPZ", "06");
	opcode_map.emplace("JMPP", "07");
	opcode_map.emplace("JMPN", "08");
	opcode_map.emplace("STORE", "09");
	opcode_map.emplace("LOAD", "10");
	opcode_map.emplace("COPY", "11");
	opcode_map.emplace("INPUT", "12");
	opcode_map.emplace("INPUT", "13");
	opcode_map.emplace("STOP", "14");
}

bool Instructions::isValid(std::string name) {
	return opcode_map.find(name) != opcode_map.end();
}

std::string Instructions::getOpcode(std::string name) {
	return opcode_map[name];
}

int main() {
	Instructions instructions;
	
	std::cout << instructions.isValid("INPUT") << std::endl;
	//std::cout << instructions.getOpcode("INPUT") << std::endl;
	std::cout << instructions.isValid("input") << std::endl;
		
	return 0;
}
