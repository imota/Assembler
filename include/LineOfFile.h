#ifndef TRAB1_SB_ZAGO_ICARO_LINE_OF_FILE
#define TRAB1_SB_ZAGO_ICARO_LINE_OF_FILE

struct LineOfFile{
	LineOfFile(std::string& s, uint n) : line(s), number(n) {}
	std::string line;
	uint number;
};

#endif