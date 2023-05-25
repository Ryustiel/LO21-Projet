#include "../head/Hand.h"

void Hand::add(const Card& c) {
	if (size == max_size) {
		throw HandException("Hand add Card : this hand is full");
	}
	cards[size++] = &c;
}

void Hand::play(const Card& c) {
	// recuperer le tableau existant
	// creer un nouveau tab de taille n + 1
	// copier le premier tableau
	// ajouter la carte
	size_t i = 0;
	while (cards[i] != &c && i < size) {
		++i;
	}
	if (i == size) { throw HandException("Hand play Card : this Card isn't part of this hand"); }
	c.activate();
}