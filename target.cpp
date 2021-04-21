#include <iostream>
#include "png-mutator.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	std::vector<uint8_t> data(Data, Data+Size);

	inverte(data);

	return 0;
}
