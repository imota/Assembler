#ifndef TRAB1_SB_ZAGO_ICARO_LINKER
#define TRAB1_SB_ZAGO_ICARO_LINKER

#include<iostream>
#include<string>
#include<vector>
#include "FirstPass.h"


struct Module{
	std::string fname;
	uint correction_factor;
	std::vector<uint> relatives;
	std::vector<UseTableElement> useTable;
	std::vector<DefinitionTableElement> definitionTable;
	std::vector<int> code;
};

class Linker{
public:
	static Linker& instance();
	void linkFiles(std::string firstFile, std::string secondFile, std::string outfile);

private:
	Module mod_a;
	Module mod_b;
	std::vector<DefinitionTableElement> global_dt;
	std::vector<int> global_code;
	std::string fout_name;
	Linker() {}

	void readModule(Module& mod);
	void initModules();
	void applyCorrectionFactor(Module& mod);
	void buildGlobalDefinitionTable();
	void uniteCode();
	void applyUseTableCorrections();
	void writeToFile();
};



#endif