#include<iostream>
#include "FirstPass.h"


FirstPass::FirstPass() {}
FirstPass::~FirstPass() {}

FirstPass& FirstPass::instance() {
	static FirstPass fp;
	return fp;
}