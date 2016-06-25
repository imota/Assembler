#ifndef TRAB1_SB_ZAGO_ICARO_MOUNTER
#define TRAB1_SB_ZAGO_ICARO_MOUNTER

#include <elfio/elfio.hpp>

class Mounter {
  public:
  	static Mounter& instance();
  	void mount(std::string foutname);

  	std::string text;
  	std::string data;
  private:
  	Mounter() {}
};

#endif