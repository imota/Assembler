#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include <sstream>
#include "keywords.h"
#include "token.h"
#include "TokenCreator.h"
#include "translator2.h"
#define INIT_SECTION_TEXT 0x08048000
#define INIT_SECTION_DATA 0x08049000
#define LECHAR 0
#define ESCREVECHAR 0x1f
#define LESTR 0x44
#define ESCREVESTR 0x6a
#define LEINT 0x8a
#define ESCREVEINT 0xe0

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

	std::string charI = 	"\nLerChar: ENTER 0,0\n"
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

	address_data = INIT_SECTION_DATA; address_text = INIT_SECTION_TEXT;
	IObin = "\xc8\x00\x00\x00"         	
			 "\x50"                   	
			 "\xb8\x03\x00\x00\x00"      	
			 "\xbb\x00\x00\x00\x00"       	
			 "\xba\x02\x00\x00\x00"       	
			 "\xcd\x80"                	
			 "\x81\x21\xff\x00\x00\x00"    	
			 "\x58"                   	
			 "\xc9"                   	 
			 "\xc3"                   	
			 "\xc8\x00\x00\x00"          	
			 "\x50"                   	
			 "\x81\x09\x00\x0a\x00\x00"    	
			 "\xb8\x04\x00\x00\x00"       	
			 "\xbb\x01\x00\x00\x00"       	
			 "\xba\x02\x00\x00\x00"       	
			 "\xcd\x80"                	
			 "\x81\x21\xff\x00\x00\x00"    	
			 "\x58"                   	
			 "\xc9"                   	  
			 "\xc3"                   	    
			 "\xc8\x00\x00\x00"          	
			 "\xbf\x00\x00\x00\x00"       	
			 "\x49"                   	
			 "\x41"                   	
			 "\xb8\x03\x00\x00\x00"       	
			 "\xbb\x00\x00\x00\x00"       	
			 "\xba\x01\x00\x00\x00"       	
			 "\xcd\x80"               	
			 "\x47"                   	
			 "\x80\x39\x0a"             	
			 "\x75\xe8"                	
			 "\x89\xf8"                	
			 "\xc9"                   	  
			 "\xc3"                   	
			 "\xc8\x00\x00\x00"          	
			 "\x50"                   	
			 "\x49"                   	
			 "\x41"                   	
			 "\xb8\x04\x00\x00\x00"       	
			 "\xbb\x01\x00\x00\x00"       	
			 "\xba\x01\x00\x00\x00"       	
			 "\xcd\x80"                	
			 "\x80\x39\x0a"             	
			 "\x75\xe9"                	
			 "\x58"                   	
			 "\xc9"                   	 
			 "\xc3"                   	
			 "\xc8\x04\x00\x00"          	
			 "\x50"                  	
			 "\xc7\x07\x00\x00\x00\x00"    	
			 "\xbe\x00\x00\x00\x00"       	
			 "\xb8\x03\x00\x00\x00"       	
			 "\xbb\x00\x00\x00\x00"       	
			 "\x89\xe9"                	
			 "\x83\xe9\x04"             	
			 "\xba\x01\x00\x00\x00"       	
			 "\xcd\x80"                	
			 "\x83\x39\x0a"             	
			 "\x74\x08"                	
			 "\x46"                  
			 "\x83\x29\x30"             	
			 "\xff\x31"                	
			 "\xeb\xdd"                	
			 "\xb9\x01\x00\x00\x00"
			 "\xbb\x0a\x00\x00\x00"       	
			 "\xba\x00\x00\x00\x00"       	
			 "\x58"                   	
			 "\xf7\xe1"                	
			 "\x01\x07"                	
			 "\x89\xc8"                	
			 "\xf7\xe3"                	
			 "\x89\xc1"                	
			 "\x4e"                   	
			 "\x83\xfe\x00"             	
			 "\x75\xea"                	
			 "\x58"                   	
			 "\xc9"                   	  
			 "\xc3"                   	
			 "\xc8\x04\x00\x00"          
			 "\x50"                   	
			 "\xbb\x0a\x00\x00\x00"      	
			 "\xbe\x00\x00\x00\x00"       	
			 "\x8b\x07"                	
			 "\xba\x00\x00\x00\x00"       	
			 "\xf7\xf3"                	
			 "\x52"                   	
			 "\x46"                   	
			 "\x83\xf8\x00"             	
			 "\x75\xf2"                	
			 "\x89\xe9"                	
			 "\x83\xe9\x04"         
			 "\x8f\x01"      
			 "\x83\x01\x30"             	  
			 "\xb8\x04\x00\x00\x00"       	    
			 "\xbb\x01\x00\x00\x00"       	    
			 "\xba\x01\x00\x00\x00"       	   
			 "\xcd\x80"                	    
			 "\x4e"                   	    
			 "\x83\xfe\x00"             	    
			 "\x75\xe4"                	   
			 "\xc6\x45\xfc\x0a"          	   
			 "\x89\xe9"                   
			 "\x83\xe9\x04"             	    
			 "\xb8\x04\x00\x00\x00"       	    
			 "\xbb\x01\x00\x00\x00"       	    
			 "\xba\x01\x00\x00\x00"       	    
			 "\xcd\x80"                	    
			 "\x58"                   	
			 "\xc9"                   	  
			 "\xc3";
}

void Translator2::generateAsmFile(){ //TODO: change cout to file
	std::ofstream myfile;
	myfile.open(foutname);
	for(std::string& s : defines) {
		myfile << s << std::endl;
	}
	myfile << "SECTION .bss\n";
	for(std::string& s : sectionbss) {
		myfile << s << std::endl;
	}
	myfile << "SECTION .DATA\n";
	for(std::string& s : sectiondata) {
		myfile << s << std::endl;
	}
	myfile << "SECTION .TEXT\nglobal _start\n_start:\n";
	for(std::string& s : sectiontext) {
		myfile << s << std::endl;
	}
	for(std::string& s : IOfunctions) {
		myfile << s << std::endl;
	}
	myfile.close();
}

void Translator2::translate(std::vector<Token> tks, std::string outputFileName){
	tokens = tks;
	foutname = outputFileName;
	init();
	Opcodes hash(Invented);
	for(size_t i = 0; i < tokens.size(); i++){
		if(tokens[i].Type() == "INSTRUCTION"){
			i = checkPrevLabel(i);
			i = (this->*functions[hash.opcode(tokens[i].name)])(i); //Calls the corresponding method in the vector of function pointers
		}
		else if(tokens[i].Type() == "DIRECTIVE") {
			i = (this->*functions[hash.opcode(tokens[i].name)])(i);
		}
	}

	text_bin.append(IObin);
	generateAsmFile();
}

void Translator2::repLabels(){
	for(Label l : labels){
		std::stringstream stream;
		stream << std::hex << l.address;
		std::string result(stream.str());
		while(result.size() < 8)	result.insert(result.begin(), '0');
		for(int i = result.size()-2; i >= 0; i = i-2){
			result.insert(result.begin()+i, 92);
			result.insert(result.begin()+i+1, 'x');
		}
		size_t found = text_bin.find(l.name);
		while(found != std::string::npos){
			text_bin.replace(text_bin.begin()+found, text_bin.begin()+found+l.name.size(), result);
			found = text_bin.find(l.name);
		}
	}

	for(Call c : calls){
		std::stringstream stream;
		stream << std::hex << c.type + address_text - c.address;
		std::string result(stream.str());
		while(result.size() < 8)	result.insert(result.begin(), '0');
		for(int i = result.size()-2; i >= 0; i = i-2){
			result.insert(result.begin()+i, 92);
			result.insert(result.begin()+i+1, 'x');
		}
		size_t found = text_bin.find(c.name);
		while(found != std::string::npos){
			text_bin.replace(text_bin.begin()+found, text_bin.begin()+found+c.name.size(), result);
			found = text_bin.find(c.name);
		}
	}

	for(Jump j : jumps){
		std::stringstream stream;
		stream << std::hex << getLabelAddress(j.label) - j.address;
		std::string result(stream.str());
		while(result.size() < 8)	result.insert(result.begin(), result[0]);
		for(int i = result.size()-2; i >= 0; i = i-2){
			result.insert(result.begin()+i, 92);
			result.insert(result.begin()+i+1, 'x');
		}
		size_t found = text_bin.find(j.name);
		while(found != std::string::npos){
			text_bin.replace(text_bin.begin()+found, text_bin.begin()+found+j.name.size(), result);
			found = text_bin.find(j.name);
		}
	}
}

int Translator2::getLabelAddress(std::string s){
	for(Label l : labels)
		if(l.name == s)
			return l.address;
	return 0;
}

size_t Translator2::checkPrevLabel(int i){
	if(i!=0)
		if(tokens[i-1].Type() == "LABEL"){
			i--;
			sectiontext.push_back(tokens[i].name);
			tokens[i].name.pop_back();
			Label aux(tokens[i].name, address_text);
			labels.push_back(aux);
			tokens.erase(tokens.begin()+i);
		}
	return i;
}

std::string Translator2::labelName(Token& tk){
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
	address_text += 6;
	text_bin.append("\x03\x05");
	text_bin.append(tokens[i+1].name);
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::sub(int i) {
	std::string line = "SUB EAX, [";
	line.append(labelName(tokens[i+1]));
	address_text += 6;
	text_bin.append("\x2b\x05");
	text_bin.append(tokens[i+1].name);
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::mult(int i) { 
	std::string line = "MUL dword [";
	line.append(labelName(tokens[i+1]));
	address_text += 6;
	text_bin.append("\xf7\x25");
	text_bin.append(tokens[i+1].name);
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
} 

size_t Translator2::div(int i) { 
	std::string line = "SUB EDX, EDX";
	address_text += 2;
	text_bin.append("\x29\xd2");
	sectiontext.push_back(line);
	line = "DIV dword [";
	line.append(labelName(tokens[i+1]));
	address_text += 6;
	text_bin.append("\xf7\x35");
	text_bin.append(tokens[i+1].name);
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmp(int i) {
	std::string line = "JMP ";
	line.append(labelName(tokens[i+1]));
	text_bin.append("\xe9");
	address_text += 5;
	std::string name = "jmp";
	name.push_back(jumps.size());
	text_bin.append(name);
	Jump aux(name, address_text, tokens[i+1].name);
	jumps.push_back(aux);
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmpn(int i) {
	std::string line = "CMP EAX, 0";
	address_text += 3;
	text_bin.append("\x83\xf8\x00");
	sectiontext.push_back(line);
	line = "JL ";
	line.append(labelName(tokens[i+1]));
	address_text += 6;
	text_bin.append("\x0f\x8c");
	std::string name = "jmp";
	name.push_back(jumps.size());
	text_bin.append(name);
	Jump aux(name, address_text, tokens[i+1].name);
	jumps.push_back(aux);
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmpp(int i) {
	std::string line = "CMP EAX, 0";
	address_text += 3;
	text_bin.append("\x83\xf8\x00");
	sectiontext.push_back(line);
	line = "JG ";
	line.append(labelName(tokens[i+1]));
	address_text += 6;
	text_bin.append("\x0f\x8f");
	std::string name = "jmp";
	name.push_back(jumps.size());
	text_bin.append(name);
	Jump aux(name, address_text, tokens[i+1].name);
	jumps.push_back(aux);
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::jmpz(int i) {
	std::string line = "CMP EAX, 0";
	address_text += 3;
	text_bin.append("\x83\xf8\x00");
	sectiontext.push_back(line);
	line = "JE ";
	line.append(labelName(tokens[i+1]));
	address_text += 6;
	text_bin.append("\x0f\x84");
	std::string name = "jmp";
	name.push_back(jumps.size());
	text_bin.append(name);
	Jump aux(name, address_text, tokens[i+1].name);
	jumps.push_back(aux);
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::copy(int i) {
	std::string line = "MOV ESI, [";
	line.append(labelName(tokens[i+1]));
	address_text += 6;
	text_bin.append("\x8b\x35");
	text_bin.append(tokens[i+1].name);
	line.push_back(']');
	sectiontext.push_back(line);
	line = "MOV DWORD[";
	line.append(labelName(tokens[i+2]));
	address_text += 6;
	text_bin.append("\x89\x35");
	text_bin.append(tokens[i+2].name);
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
	address_text += 5;
	text_bin.append("\xa1");
	text_bin.append(tokens[i+1].name);
	line.push_back(']');
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::store(int i) {
	std::string line = "MOV DWORD[";
	line.append(labelName(tokens[i+1]));
	address_text += 5;
	text_bin.append("\xa3");
	text_bin.append(tokens[i+1].name);
	line.append("], EAX");
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::input(int i) {
	std::string line = "MOV EDI, ";
	line.append(labelName(tokens[i+1]));
	address_text += 5;
	text_bin.append("\xbf");
	text_bin.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL LerInteiro";
	text_bin.append("\xe8");
	std::string name = "call";
	name.push_back(calls.size());
	text_bin.append(name);
	Call aux(name, address_text, LEINT);
	calls.push_back(aux);

	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}
size_t Translator2::output(int i) {
	std::string line = "MOV EDI, ";
	line.append(labelName(tokens[i+1]));
	address_text += 5;
	text_bin.append("\xbf");
	text_bin.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL EscreverInteiro";
	text_bin.append("\xe8");
	std::string name = "call";
	name.push_back(calls.size());
	text_bin.append(name);
	Call aux(name, address_text, ESCREVEINT);
	calls.push_back(aux);
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}

size_t Translator2::stop(int i) {
	address_text += 12;
	text_bin.append("\xb8\x01\x00\x00\x00\xbb\x00\x00\x00\x00\xcd\x80");
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
	line.append(labelName(tokens[i+1]));
	address_text += 5;
	text_bin.append("\xb9");
	text_bin.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL LerChar";
	text_bin.append("\xe8");
	std::string name = "call";
	name.push_back(calls.size());
	text_bin.append(name);
	Call aux(name, address_text, LECHAR);
	calls.push_back(aux);
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;

}
size_t Translator2::c_output(int i) {
	std::string line = "MOV ECX, ";
	line.append(labelName(tokens[i+1]));
	address_text += 5;
	text_bin.append("\xb9");
	text_bin.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL EscreverChar";
	text_bin.append("\xe8");
	std::string name = "call";
	name.push_back(calls.size());
	text_bin.append(name);
	Call aux(name, address_text, ESCREVECHAR);
	calls.push_back(aux);
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}
size_t Translator2::s_input(int i) {
	std::string line = "MOV ECX, ";
	line.append(labelName(tokens[i+1]));
	address_text += 5;
	text_bin.append("\xb9");
	text_bin.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL LerString";
	text_bin.append("\xe8");
	std::string name = "call";
	name.push_back(calls.size());
	text_bin.append(name);
	Call aux(name, address_text, LESTR);
	calls.push_back(aux);
	sectiontext.push_back(line);
	tokens.erase(tokens.begin()+i+1);
	tokens.erase(tokens.begin()+i);
	return --i;
}
size_t Translator2::s_output(int i) {
	std::string line = "MOV ECX, ";
	line.append(labelName(tokens[i+1]));
	address_text += 5;
	text_bin.append("\xb9");
	text_bin.append(tokens[i+1].name);
	sectiontext.push_back(line);
	line = "CALL EscreverString";
	sectiontext.push_back(line);
	text_bin.append("\xe8");
	std::string name = "call";
	name.push_back(calls.size());
	text_bin.append(name);
	Call aux(name, address_text, ESCREVESTR);
	calls.push_back(aux);
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
	tokens[i-1].name.pop_back();
	Label aux(tokens[i-1].name, address_data);
	labels.push_back(aux);
	if (isInteger(tokens[i+1].name)){
		line.append(tokens[i+1].name);
		std::string::size_type sz;
		address_data += 4*std::stoi(tokens[i+1].name, &sz);
		tokens.erase(tokens.begin()+i+1);
	}
	else{
		line.append("1");
		address_data += 4;
	}
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
	tokens[i-1].name.pop_back();
	Label aux(tokens[i-1].name, address_data);
	labels.push_back(aux);
	address_data += 4;
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