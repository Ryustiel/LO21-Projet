#include "../head/Deck.h"

const Card& Deck::draw() {
	if (size == 0) throw stException("Error: Drawing empty deck.");
	return *cards[size--];
}


void Deck::add(const Card& c) {
	if (size == maxSize) {
		maxSize += 20;
		Card** newCards = new Card * [maxSize];
		for (size_t i = 0; i <= size; ++i) *newCards[i] = *cards[i];
		delete[] cards;
		cards = newCards;
	}
	cards[size++] = &c;
}