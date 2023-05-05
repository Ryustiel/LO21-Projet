#pragma once
#include "Card.h"
#include "..\exception\ShottenTottenException.h"

class BoardException : public ShottenTottenException { using ShottenTottenException::ShottenTottenException; };

enum class Side { none, j1, j2 };
enum class Combination { sum, straight, flush, three_of_a_kind, straight_flush};

class Border {
private:
	size_t max_size;
	size_t size_j1;
	size_t size_j2;
	const Card** combination_j1;
	const Card** combination_j2;
	Side revendication;
public:
	Border(): max_size(3), size_j1(0), size_j2(0), combination_j1(new const Card*[max_size]), combination_j2(new const Card* [max_size]), revendication(Side::none) {}
	~Border() { delete[] combination_j1; delete[] combination_j2; }
  const Side& getRevendication() const { return revedication; }
	void addCard(const Card& card, const Side side);
  const Card& Border::removeCard(const Card& card, const Side side);
	void changeMaxSize(const size_t size);
  const Side& isWon();
  static const Combination& combinaisonFullEval(const Card& c1, const Card& c2, const Card& c3);
};

class Board {
private:
	Border* borders;
	size_t border_nb;
public:
	Board(size_t size = 9) : border_nb(size), borders(new Border[size]) {}
	~Board() { delete[] borders; }
	void addCard(const Card& card, const Side side, const unsigned int n);
  const Card& Board::removeCard(const Card& card, const Side side, const unsigned int n);
  const Side& isBorderWon(const unsigned int n) const;
};