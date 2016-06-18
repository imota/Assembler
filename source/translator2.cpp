#include<vector>
#include<string>
#include "keywords.h"
#include "token.h"
#include "TokenCreator.h"
#include "translator2.h"

Translator2& Translator2::instance() {
	static Translator2 tr2;
	return tr2;
}

void Translator2::init() {
	functions.push_back(NULL);  	//0
	functions.push_back(&Translator2::add);  	//1
	functions.push_back(&Translator2::sub);  	//2
	functions.push_back(&Translator2::mult); 	//3
	functions.push_back(&Translator2::div);  	//4
	functions.push_back(&Translator2::jmp);  	//5
	functions.push_back(&Translator2::jmpn); 	//6
	functions.push_back(&Translator2::jmpp); 	//7
	functions.push_back(&Translator2::jmpz); 	//8
	functions.push_back(&Translator2::copy); 	//9
	functions.push_back(&Translator2::load); 	//10
	functions.push_back(&Translator2::store);	//11
	functions.push_back(&Translator2::input);	//12
	functions.push_back(&Translator2::output);	//13
	functions.push_back(&Translator2::stop);	 //14
	functions.push_back(&Translator2::c_input);  //15
	functions.push_back(&Translator2::c_output); //16
	functions.push_back(&Translator2::s_input);  //17
	functions.push_back(&Translator2::s_output); //18

	functions.push_back(&Translator2::begin); //19
	functions.push_back(&Translator2::end); //20
	functions.push_back(&Translator2::equ); //21
	functions.push_back(&Translator2::space); //22
	functions.push_back(&Translator2::const_asm); //23
	functions.push_back(&Translator2::section); //24
	functions.push_back(&Translator2::public_asm); //25
	functions.push_back(&Translator2::extern_asm); //26
	functions.push_back(&Translator2::if_asm); //27
}

void Translator2::generateAsmFile(){ //TODO: change cout to file
	std::cout << "\nsection .bss\n";
	for(std::string& s : sectionbss)	std::cout << s << std::endl;
	std::cout << "section .data\n";
	for(std::string& s : sectiondata)	std::cout << s << std::endl;
	std::cout << "section .text\n";
	for(std::string& s : sectiontext)	std::cout << s << std::endl;
}

void Translator2::translate(std::vector<Token> tks){
	tokens = tks;
	init();

	Opcodes hash(Invented);
	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i].Type() == "INSTRUCTION"){
			i = checkPrevLabel(i);
			i = (this->*functions[hash.opcode(tokens[i].name)])(i); //Calls the corresponding method in the vector of function pointers
		}
		else if(tokens[i].Type() == "DIRECTIVE")
			i = (this->*functions[hash.opcode(tokens[i].name)])(i);
	}

	generateAsmFile();
}

size_t Translator2::checkPrevLabel(int i){
	if(tokens[i-1].Type() == "LABEL"){
		i--;
		sectiontext.push_back(tokens[i].name);
		tokens.erase(tokens.begin()+i);
	}
	return i;
}

std::string Translator2::labelName(Token tk){
	size_t found = tk.name.find("+");
	if(found != std::string::npos){	//If found character '+' in tk.name
		char aux = tk.name[found+1];
		aux -= 0x30; aux *= 4; aux += 0x30;
		tk.name[found+1] = aux;
	}
	return tk.name;

}

/*
##############################################################
##############################################################
##############################################################
##############################################################
##############################################################
TRANSLATION FOR INSTRUCTIONS:
*/

size_t Translator2::add(int i) {
	std::string line = "ADD EAX, [";
	line.append(labelName(tokens[i+1]));
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::sub(int i) {
	std::string line = "SUB EAX, [";
	line.append(labelName(tokens[i+1]));
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::mult(int i) { 
	std::string line = "MUL dword [";
	line.append(labelName(tokens[i+1]));
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
} 

size_t Translator2::div(int i) { 
	std::string line = "SUB EDX, EDX";
	sectiontext.push_back(line);
	line = "DIV dword [";
	line.append(labelName(tokens[i+1]));
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmp(int i) {
	std::string line = "JMP ";
	line.append(labelName(tokens[i+1]));
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmpn(int i) {
	std::string line = "CMP EAX 0";
	sectiontext.push_back(line);
	line = "JL ";
	line.append(labelName(tokens[i+1]));
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmpp(int i) {
	std::string line = "CMP EAX 0";
	sectiontext.push_back(line);
	line = "JG ";
	line.append(labelName(tokens[i+1]));
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmpz(int i) {
	std::string line = "CMP EAX 0";
	sectiontext.push_back(line);
	line = "JE ";
	line.append(labelName(tokens[i+1]));
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::copy(int i) {
	std::string line = "MOV ESI, [";
	line.append(labelName(tokens[i+1]));
	line.push_back(']');
	sectiontext.push_back(line);
	line = "MOV DWORD[";
	line.append(labelName(tokens[i+2]));
	line.append("], ESI");
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+2);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::load(int i) {
	std::string line = "MOV EAX, [";
	line.append(labelName(tokens[i+1]));
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::store(int i) {
	std::string line = "MOV DWORD[";
	line.append(labelName(tokens[i+1]));
	line.append("], EAX");
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::input(int i) { return i; } //TODO
size_t Translator2::output(int i) { return i; } //TODO

size_t Translator2::stop(int i) {
	std::string line = "MOV EAX, 1";
	sectiontext.push_back(line);
	line = "MOV EBX, 0";
	sectiontext.push_back(line);
	line = "INT 80H";
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::c_input(int i) { return i; } //TODO
size_t Translator2::c_output(int i) { return i; } //TODO
size_t Translator2::s_input(int i) { return i; } //TODO
size_t Translator2::s_output(int i) { return i; } //TODO


/*
##############################################################
##############################################################
##############################################################
##############################################################
##############################################################
TRANSLATION FOR DIRECTIVES: (TODO)
*/

size_t Translator2::begin(int i) { return i; }
size_t Translator2::end(int i) { return i; }
size_t Translator2::equ(int i) { return i; }
size_t Translator2::space(int i) { return i; }
size_t Translator2::const_asm(int i) { return i; }
size_t Translator2::section(int i) { return i; }
size_t Translator2::public_asm(int i) { return i; }
size_t Translator2::extern_asm(int i) { return i; }
size_t Translator2::if_asm(int i) { return i; }