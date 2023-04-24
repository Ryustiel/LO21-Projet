#include "Card.h"
#include "../exception/ShottenTottenException.h"

class Deck {
private:
	const Card** cards = new Card*[0];
	size_t maxSize = 0;
	size_t size =  0;
	~Deck() {
		delete[] cards;
	}
public:
	bool isEmpty() const { return size == 0; }
	const Card& draw();
	void add(const Card& c);
};