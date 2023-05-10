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
	cards[x] = cards[card_count--];
	return c;
}