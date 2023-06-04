// this is used by the Utility methods
#include <vector>
#include <cstdlib>
#include <ctime>

namespace Utility {
	int seed = std::time(0);

	std::vector<unsigned int> boollistToIndices(bool* btable, const size_t size) {
		// converts a bool array { true, false, true } into
		// an array of int indices { 0, 2 } where it's true
		std::vector<unsigned int> itable;
		for (size_t i = 0; i < size; i++) {
			if (btable[i] == true) { itable.push_back(i); }
		}
		return itable;
	}
	int randint(unsigned int min, unsigned int max) {
		std::srand(seed++);
		int n = rand() % (max - min); // max - min : the modulo operator
		return n + min;
	}
	int randchoice(bool* btable, const size_t size) {
		std::vector<unsigned int> itable = boollistToIndices(btable, size);
		unsigned int i = randint(0, itable.size()); // random number from table range
		return itable[i]; // random indice from the table
	}
}