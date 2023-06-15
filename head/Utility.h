#pragma once

#include <vector>
#include "../exception/ShottenTottenException.h"
#include <sstream>
#include <string>

namespace Utility {

	std::vector<unsigned int> boolToIndices(bool* blist, size_t size);
	
	int randInt(unsigned int min, unsigned int max);

	int randChoice(bool* blist, size_t size);

	struct stringbuilder
	{
		std::stringstream ss;
		template<typename T>
		stringbuilder& operator << (const T& data)
		{
			ss << data;
			return *this;
		}
		operator std::string() { return ss.str(); }
	};
}