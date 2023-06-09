#pragma once

#include <vector>

namespace Utility {

	std::vector<unsigned int> boolToIndices(bool* blist, size_t size);
	
	int randInt(unsigned int min, unsigned int max);

	int randChoice(bool* blist, size_t size);
}