#include "binary.h"
#include <iostream>

int main(int argc, const char** argv) {

    if (argc<3) {
		std::cerr << "Need two arguments!" << std::endl;
        return 1;
    }

    const Binary big(argv[1]);
    const Binary small(argv[2]);

    const auto location = big.find(small);

    if (!location) {
		std::cerr << "No match" << std::endl;
        return 1;
    } else {
		const auto val = location.value();
		std::cerr << std::hex <<
			"Found @ 0x" << val << " - "
			<< "0x" << val+small.size() << std::endl;
        return 0;
    }
}
