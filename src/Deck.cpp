#include"../head/Deck.h"


Deck::Deck(const Game& g) : cards(new const Card* [g.getCardCount()]), max_card_count(g.getCardCount()), card_count(g.getCardCount()) {
	for (unsigned int i = 0; i < g.getCardCount(); i++) cards[i] = &g.getCard(i);
}

Deck::~Deck() {
	delete[] cards;
}

const Card& Deck::draw() {
	if (isEmpty()) throw ShottenTottenException("draw error : deck is empty");
	unsigned int x = rand() % card_count;
	auto& c = *cards[x];
	cards[x] = cards[--card_count];
	return c;
}

const size_t Deck::drawMultiple(const Card** cards, const size_t number) {
	for (size_t i = 0; i < number; ++i) {
		if (isEmpty()) return i;
		cards[i] = &draw();
	}
	return number;
}

void Deck::addCard(const Card& c) {
	cards[card_count++] = &c;
}