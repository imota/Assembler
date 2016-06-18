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

	std::string charI = "LerChar: ENTER 0,0\n"
							"PUSH EAX\n"
							"MOV EAX,3\n"
							"MOV EBX,0\n"
							"MOV EDX,2\n"
							"INT 80H\n"
							"AND DWORD [ECX], 0xFF\n" //Clean ENTER
							"POP EAX\n"
							"LEAVE\n"
							"RET\n";
	IOfunctions.push_back(charI);
		std::string charO = "EscreverChar: ENTER 0,0\n"
							"PUSH EAX\n"
							"OR DWORD [ECX],0x0A00\n"
							"MOV EAX,4\n"
							"MOV EBX,1\n"
							"MOV EDX,2\n"
							"INT 80H\n"
							"AND DWORD [ECX],0xFF\n"
							"POP EAX\n"
							"LEAVE\n"
							"RET\n";
	IOfunctions.push_back(charO);
	std::string stringI = 	"LerString: ENTER 0,0\n"
							"MOV EDI, 0\n"
							"DEC ECX\n"
							"LOOP_LERSTRING: INC ECX\n"
							"MOV EAX,3\n"
							"MOV EBX,0\n"
							"MOV EDX,1\n"
							"INT 80H\n"
							"INC EDI\n"
							"CMP BYTE [ECX], 0xA\n"
							"JNZ LOOP_LERSTRING\n"
							"MOV EAX, EDI\n"
							"LEAVE\n"
							"RET\n";
	IOfunctions.push_back(stringI);
	std::string stringO = 	"EscreverString: ENTER 0,0\n"
							"PUSH EAX\n"
							"DEC ECX\n"
							"LOOP_ESCREVERSTRING: INC ECX\n"
							"MOV EAX,4\n"
							"MOV EBX,1\n"
							"MOV EDX,1\n"
							"INT 80H\n"
							"CMP BYTE [ECX],0xA\n"
							"JNZ LOOP_ESCREVERSTRING\n"
							"POP EAX\n"
							"LEAVE\n"
							"RET\n";
	IOfunctions.push_back(stringO);
	std::string intI = 		"LerInteiro: ENTER 4,0\n"
							"PUSH EAX\n"
							"MOV DWORD [EDI],0\n"
							"MOV ESI, 0\n"
							"LOOP_LERINTEIRO: MOV EAX,3\n"
							"MOV EBX,0\n"
							"MOV ECX,EBP\n"
							"SUB ECX,4\n"
							"MOV EDX,1\n"
							"INT 0x80\n"
							"CMP DWORD [ECX], 0xA\n"
							"JZ NEXT_LERINTEIRO\n"
							"INC ESI\n"
							"SUB DWORD [ECX], 0x30\n"
							"PUSH DWORD [ECX]\n"
							"JMP LOOP_LERINTEIRO\n"
							"NEXT_LERINTEIRO: MOV ECX, 1\n"
							"MOV EBX, 10\n"
							"SOMA_LERINTEIRO: MOV EDX, 0\n"
							"POP EAX\n"
							"MUL ECX\n"
							"ADD DWORD [EDI], EAX\n"
							"MOV EAX, ECX\n"
							"MUL EBX\n"
							"MOV ECX, EAX\n"
							"DEC ESI\n"
							"CMP ESI,0\n"
							"JNZ SOMA_LERINTEIRO\n"
							"POP EAX\n"
							"LEAVE\n"
							"RET\n";
	IOfunctions.push_back(intI);
	std::string intO = 		"EscreverInteiro: ENTER 4,0\n"
							"PUSH EAX\n"
							"MOV EBX, 10\n"
							"MOV ESI, 0\n"
							"MOV EAX, [EDI]\n"
							"CALC_ESCREVERINTEIRO: MOV EDX, 0\n"
							"DIV EBX\n"
							"PUSH EDX\n"
							"INC ESI\n"
							"CMP EAX, 0\n"
							"JNZ CALC_ESCREVERINTEIRO\n"
							"MOV ECX, EBP\n"
							"SUB ECX, 4\n"
							"LOOP_ESCREVERINTEIRO: POP DWORD [ECX]\n"
							"ADD DWORD [ECX], 0x30\n"
							"MOV EAX, 4\n"
							"MOV EBX, 1\n"
							"MOV EDX, 1\n"
							"INT 80H\n"
							"DEC ESI\n"
							"CMP ESI, 0\n"
							"JNZ LOOP_ESCREVERINTEIRO\n"
							"MOV BYTE [EBP-4], 0xA\n"
							"MOV ECX, EBP\n"
							"SUB ECX, 4\n"
							"MOV EAX, 4\n"
							"MOV EBX, 1\n"
							"MOV EDX, 1\n"
							"INT 0x80\n"
							"POP EAX\n"
							"LEAVE\n"
							"RET\n";
	IOfunctions.push_back(intO);
}

void Translator2::generateAsmFile(){ //TODO: change cout to file
	for(std::string& s : defines)		std::cout << s << std::endl;
	std::cout << "\nsection .bss\n";
	for(std::string& s : sectionbss)	std::cout << s << std::endl;
	std::cout << "section .data\n";
	for(std::string& s : sectiondata)	std::cout << s << std::endl;
	std::cout << "section .text\n";
	for(std::string& s : sectiontext)	std::cout << s << std::endl;
	for(std::string& s : IOfunctions)	std::cout << s << std::endl;
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
	if(found != std::string::npos)	//If found character '+' in tk.name
		tk.name.insert(found+1,"4*");
	return tk.name;

}

//This method returns true if a string is an integer
bool Translator2::isInteger(std::string s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
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
	std::string line = "CMP EAX, 0";
	sectiontext.push_back(line);
	line = "JL ";
	line.append(labelName(tokens[i+1]));
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmpp(int i) {
	std::string line = "CMP EAX, 0";
	sectiontext.push_back(line);
	line = "JG ";
	line.append(labelName(tokens[i+1]));
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmpz(int i) {
	std::string line = "CMP EAX, 0";
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

size_t Translator2::input(int i) {
	std::string line = "MOV EDI, ";
	line.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL LerInteiro";
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}
size_t Translator2::output(int i) {
	std::string line = "MOV EDI, ";
	line.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL EscreverInteiro";
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

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

size_t Translator2::c_input(int i) {
	std::string line = "MOV ECX, ";
	line.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL LerChar";
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;

}
size_t Translator2::c_output(int i) {
	std::string line = "MOV ECX, ";
	line.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL EscreverChar";
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}
size_t Translator2::s_input(int i) {
	std::string line = "MOV ECX, ";
	line.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL LerString";
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}
size_t Translator2::s_output(int i) {
	std::string line = "MOV ECX, ";
	line.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL EscreverString";
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}


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

/*This method translates from Invented ASM:
LABEL: EQU IMM
TO IA-32 ASM:
LABEL EQU IMM*/
size_t Translator2::equ(int i) {
	std::string line;
	tokens[i-1].name.pop_back();
	line.append(tokens[i-1].name);
	line.append(" ");
	line.append(tokens[i].name);
	line.append(" ");
	line.append(tokens[i+1].name);
	defines.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	tokens.erase(tokens.begin()+i-1);
	i -= 2;
	return i;
}

/*This method translates from Invented ASM:
LABEL: SPACE IMM(optional)
TO IA-32 ASM AT SECTION .BSS:
LABEL: RESD IMM*/
size_t Translator2::space(int i) {
	std::string line = tokens[i-1].name;
	line.append(" RESD ");
	if (isInteger(tokens[i+1].name)){
		line.append(tokens[i+1].name);
		tokens.erase(tokens.begin()+i+1);
	}
	else
		line.append("1");
	sectionbss.push_back(line);
	tokens.erase(tokens.begin()+i);
	tokens.erase(tokens.begin()+i-1);
	i -= 2;
	return i;
}

/*This method translates from Invented ASM:
LABEL: CONST IMM
TO IA-32 ASM AT SECTION .DATA:
LABEL: DD IMM*/
size_t Translator2::const_asm(int i) {
	std::string line = tokens[i-1].name;
	line.append(" DD ");
	line.append(tokens[i+1].name);
	sectiondata.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	tokens.erase(tokens.begin()+i-1);
	i -= 2;
	return i;
}
size_t Translator2::section(int i) {
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}
size_t Translator2::public_asm(int i) { return i; }
size_t Translator2::extern_asm(int i) { return i; }
size_t Translator2::if_asm(int i) { return i; } //TODO