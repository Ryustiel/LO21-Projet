#pragma once

#include <vector>

namespace Utility {

	std::vector<unsigned int> boollistToIndices(bool* btable, const size_t size);
	
	int randint(unsigned int min, unsigned int max);

	int randchoice(bool* btable, const size_t size);
}