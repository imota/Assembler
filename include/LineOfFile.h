#ifndef LINE_OF_FILE_H_
#define LINE_OF_FILE_H_

struct LineOfFile{
	LineOfFile(std::string& s, uint n) : line(s), number(n) {}
	std::string line;
	uint number;
};

#endif