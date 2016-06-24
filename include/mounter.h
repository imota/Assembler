#ifndef TRAB1_SB_ZAGO_ICARO_MOUNTER
#define TRAB1_SB_ZAGO_ICARO_MOUNTER

class Mounter {
  public:
  	static Mounter& instance();
  private:
  	Mounter() {}
};

#endif