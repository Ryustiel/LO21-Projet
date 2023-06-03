#include <cstdlib>
#include <ctime>
#include "../head/Utility.h"
// this is used by the SchottenTottenUtility methods
namespace Utility {
	int seed = std::time(0);

	std::vector<unsigned int> boolToIndices(bool* blist, size_t size) {
		// converts a bool array { true, false, true } into
		// an array of int indices { 0, 2 } where it's true
		std::vector<unsigned int> itable;
		for (size_t i = 0; i < size; i++) {
			if (blist[i] == true) { itable.push_back(i); }
		}
		return itable;
	}
	int randInt(unsigned int min, unsigned int max) {
		std::srand(seed++);
		int n = rand() % (max - min); // max - min : the modulo operator
		return n + min;
	}
	int randChoice(bool* blist, size_t size) {
		std::vector<unsigned int> itable = boolToIndices(blist, size);
		unsigned int i = randInt(0, itable.size()); // random number from table range
		return itable[i]; // random indice from the table
	}
}