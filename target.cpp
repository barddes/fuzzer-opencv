#include <iostream>
#include "png-mutator.h"

void inverte(std::vector<uint8_t>& data) {
	try {
		Png png = Png(data);
		std::cout << "Width:  " << png.width() << std::endl;
		std::cout << "Height: " << png.height() << std::endl;
	} catch (...) {
		return;
	}

	throw;
}



extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	std::vector<uint8_t> data(Data, Data+Size);

	inverte(data);

	return 0;
}
