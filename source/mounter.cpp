#include "mounter.h"

Mounter& Mounter::instance() {
	static Mounter m;
	return m;
}