#ifndef TRAB1_SB_ZAGO_ICARO_ERROR
#define TRAB1_SB_ZAGO_ICARO_ERROR

#include <iostream>

class Error {
  public:
  	static Error& instance();
  	void message(std::string type, std::string message, int line = -1);
  	bool error = 0;
  private:
  	Error() {}
};

#endif