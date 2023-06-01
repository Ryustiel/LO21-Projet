#include "../head/Hand.h"

void Hand::add(const Card& c) {
    if (size == max_size) {
        throw HandException("Hand add Card : this hand is full");
    }
    cards[size++] = &c;
}

void Hand::play(const Card& c) {
    size_t i = 0;
    while (cards[i] != &c && i < size) {
        ++i;
    }
    if (i == size) { throw HandException("Hand play Card : this Card isn't part of this hand"); }
    c.activate();
    withdraw(c);
}

void Hand::withdraw(const Card& c) {
    size_t i = 0;
    while (cards[i] != &c && i < size) {
        ++i;
    }
    if (i == size) { throw HandException("Hand play Card : this Card isn't part of this hand"); }
    // les cartes sont enlevées de cette manière inneficace afin de garder leur ordre pour un affichage plus agréable.
    while (i < size-1) {
        cards[i] = cards[i + 1];
        ++i;
    }
    --size;
}
