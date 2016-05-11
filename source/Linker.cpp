#include<iostream>
#include<fstream>
#include "Linker.h"
#include "Error.h"

Linker& Linker::instance() {
	static Linker l;
	return l;
}

void Linker::linkFiles(std::string firstFile, std::string secondFile, std::string outfile){
	mod_a.fname = firstFile;
	mod_b.fname = secondFile;
	fout_name = outfile;

	initModules();
	checkForErrors();
	//if(not Error::instance().error){
		applyCorrectionFactor(mod_b);
		buildGlobalDefinitionTable();
		uniteCode();
		applyUseTableCorrections();
		writeToFile();
	//}
	//else
		//std::cout << "Linking not completed due to errors\n";

}

void Linker::checkForErrors() {
	for(UseTableElement& ut : mod_a.useTable){
		bool found = 0;
		for(DefinitionTableElement dt : mod_b.definitionTable){
			if(ut.name == dt.name)
				found = 1;
		}
		if(!found){
			std::string message;
			message.append(ut.name);
			message.append(" is used by first module and not defined by the second\n");
			Error::instance().message("LINKING", message, -1);
		}
	}

	for(UseTableElement& ut : mod_b.useTable){
		bool found = 0;
		for(DefinitionTableElement dt : mod_a.definitionTable){
			if(ut.name == dt.name)
				found = 1;
		}
		if(!found){
			std::string message;
			message.append(ut.name);
			message.append(" is used by second module and not defined by the first\n");
			Error::instance().message("LINKING", message, -1);
		}
	}

	for(DefinitionTableElement& uta : mod_a.definitionTable){
		for(DefinitionTableElement& utb : mod_b.definitionTable){
			if(uta.name == utb.name){
				std::string message;
				message.append("Label ");
				message.append(uta.name);
				message.append(" is defined by both modules\n");
				Error::instance().message("LINKING", message, -1);
			}
		}
	}
}

void Linker::initModules(){
	readModule(mod_a);
	readModule(mod_b);
	mod_a.correction_factor = 0;
	mod_b.correction_factor = mod_a.code.size();
}

void Linker::readModule(Module& mod){
	std::string word;
	std::ifstream file;
	file.open(mod.fname);
	bool flag_ut = 0, flag_dt = 0, flag_r = 0, flag_code = 0;
	while(file >> word){
		if(word == "TABLE")
			continue;
		if(word == "USE")				{ flag_ut = 1; flag_dt = 0; flag_r = 0; flag_code = 0; continue; }
		else if(word == "DEFINITION")	{ flag_ut = 0; flag_dt = 1; flag_r = 0; flag_code = 0; continue; }
		else if(word == "RELATIVE")		{ flag_ut = 0; flag_dt = 0; flag_r = 1; flag_code = 0; continue; }
		else if(word == "CODE")			{ flag_ut = 0; flag_dt = 0; flag_r = 0; flag_code = 1; continue; }

		if(flag_ut){
			std::string next_word;
			file >> next_word;
			UseTableElement new_ut(word, std::stoi(next_word));
			mod.useTable.push_back(new_ut);
		}

		else if(flag_dt){
			std::string next_word;
			file >> next_word;
			DefinitionTableElement new_dt(word, std::stoi(next_word));
			mod.definitionTable.push_back(new_dt);
		}

		else if(flag_r)
			mod.relatives.push_back(std::stoi(word));

		else if(flag_code)
			mod.code.push_back(std::stoi(word));
	}
	file.close();
}

void Linker::applyCorrectionFactor(Module& mod){
	for(UseTableElement& ut : mod.useTable)
		ut.sumAddress += mod.correction_factor;

	for(uint u : mod.relatives)
		mod.code[u] += mod.correction_factor;

	for(DefinitionTableElement& dt : mod.definitionTable)
		dt.address += mod.correction_factor;
}

void Linker::buildGlobalDefinitionTable() {
	for(DefinitionTableElement& dt : mod_a.definitionTable)
		global_dt.push_back(dt);

	for(DefinitionTableElement& dt : mod_b.definitionTable)
		global_dt.push_back(dt);
}

void Linker::uniteCode(){
	for(int c : mod_a.code)
		global_code.push_back(c);

	for(int c : mod_b.code)
		global_code.push_back(c);
}

void Linker::applyUseTableCorrections() {
	for(UseTableElement& ut : mod_a.useTable){
		for(DefinitionTableElement& dt : global_dt){
			if(ut.name == dt.name){
				global_code[ut.sumAddress] += dt.address;
				break;
			}
		}
	}

	for(UseTableElement& ut : mod_b.useTable){
		for(DefinitionTableElement& dt : global_dt){
			if(ut.name == dt.name){
				global_code[ut.sumAddress] += dt.address;
				break;
			}
		}
	}
}

void Linker::writeToFile() {
	std::ofstream file;
	file.open(fout_name);

	for(int c : global_code)
		file << c << " ";

	file.close();
	std::cout << "\nLinking was successful.\n";
}