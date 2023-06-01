#pragma once
#include "Card.h"
#include "../exception/ShottenTottenException.h"

class HandException : public ShottenTottenException {
    ShottenTottenException::ShottenTottenException;
};

class Hand{
private:
    const Card** cards;
    size_t size;
    size_t max_size;
public:
    Hand(const Card** c, size_t n) : cards(c), size(n), max_size(n) {}
    void add(const Card& c);
    void withdraw(const Card& c);
    void play(const Card& c);
    size_t getSize() const { return size; }
    size_t getMaxSize() const { return max_size; }
    const Card* getCard(size_t i) const {
        if (i < 0 || i >= size) throw ShottenTottenException("get Card : incorrect card number i");
        return cards[i];
    }
};
