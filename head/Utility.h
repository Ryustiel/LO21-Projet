#pragma once

#include <vector>

namespace Utility {

	std::vector<unsigned int> boolToIndices(std::vector<bool> blist);
	
	int randInt(unsigned int min, unsigned int max);

	int randChoice(std::vector<bool> blist);
}