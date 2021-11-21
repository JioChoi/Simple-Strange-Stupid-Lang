#include <iostream>
#include "SSSlang.h"

int main(void) {
	SSSlang lang;
	lang.open("test.sss");
	lang.run();

	return 0;
}