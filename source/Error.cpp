#include "Error.h"

Error& Error::instance() {
	static Error e;
	return e;
}

void Error::message(std::string type, std::string message, int line) {
	std::cout << type;
	if (line >= 0)
		std::cout << " error at line " << line;
	std::cout <<  ": " << message << std::endl;
}