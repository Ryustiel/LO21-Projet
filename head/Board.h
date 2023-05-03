#pragma once
#include "Card.h"
#include "..\exception\ShottenTottenException.h"

class BoardException : public ShottenTottenException { using ShottenTottenException::ShottenTottenException; };

enum class Side { none, j1, j2 };


class Border {
private:
	size_t max_size;
	size_t size_j1;
	size_t size_j2;
	const Card** combination_j1;
	const Card** combination_j2;
	Side revendication;
public:
	Border(): max_size(3), size_j1(0), size_j2(0), combination_j1(new Card*[max_size]), combination_j2(new Card* [max_size]), revendication(Side::none) {}
	~Border() { delete[] combination_j1; delete[] combination_j2; }
	void addCard(const Card& card, const Side side);
	void changeMaxSize(const size_t size);

};

class Board {
private:
	Border* borders;
	size_t border_nb;
public:
	Board(size_t size = 9) : border_nb(size), borders(new Border[size]) {}
	~Board() { delete[] borders; }
	void addCard(const Card& card, const Side side, const unsigned int n);
}