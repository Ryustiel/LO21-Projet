#include "..\head\Board.h"

void Border::addCard(const Card& card, const Side side) {
	const Card** combination;
	size_t* size;
	switch (side)
	{
	case Side::j1:
		combination = combination_j1;
		size = &size_j1;
		break;
	case Side::j2:
		combination = combination_j2;
		size = &size_j2;
		break;
	default:
		throw  BoardException("Border addCard : unvalid side");
		break;
	}
	if (*size == max_size) { throw BoardException("Border addCard : this side of the border is full"); }
	
	combination[++ * size] = &card;	
}

const Card& Border::removeCard(const Card& card, const Side side) {
  const Card** combination;
	size_t* size;
  	switch (side)
	{
	case Side::j1:
		combination = combination_j1;
		size = &size_j1;
		break;
	case Side::j2:
		combination = combination_j2;
		size = &size_j2;
		break;
	default:
		throw  BoardException("Border addCard : unvalid side");
		break;
	}
  if (*size == 0) { throw BoardException("Border removeCard : this side of the border is empty"); }
  size_t i = 0;
  while(combination[i] != &card && i < *size) {
    i++;
  }
  if (i == max_size) { throw BoardException("Border removeCard : this side of the border doesn't contain this Card"); }
  auto& temp = combination[i]; 
  combination[i] = combination[*size--];
  return temp;
}

void Border::changeMaxSize(const size_t size) {
	if (size == max_size) { return; }
	const Card** new_combination_j1 = new const Card * [size];
	const Card** new_combination_j2 = new const Card * [size];
	for (int i = 0; i < size_j1; i++) {
		new_combination_j1[i] = combination_j1[i];
	}
	for (int i = 0; i <= size_j2; i++) {
		new_combination_j2[i] = combination_j2[i];
	}
	delete[] combination_j1; delete[] combination_j2;
	combination_j1 = new_combination_j1; combination_j2 = new_combination_j2;
}

const Combination& Border::combinaisonFullEval(const Card&[] c,size_t n) {
  bool flush = true;
  bool toak = true;

  for (size_t i = 1; i < n; i++) {
    if (toInt(c[i-1].getNumber() != toInt(c[i].getNumber()) {
      toak = false;
      break;
    }
  }
  if (toak) return Combination::three_of_a_kind;
  
  for (size_t i = 1; i < n; i++) {
    if (c[i].getColor() != c[i-1].getColor()) {
      flush = false;
      break;
    }
  }

  int min = toInt(c[0].getNumber());
  int max = toInt(c[0].getNumber());
  for (size_t i = 1; i < n; i++) {
    if(toInt(c[i].getNumber()) < min)
      min = toInt(c[i].getNumber());
    if(toInt(c[i].getNumber()) > max)
      max = toInt(c[i].getNumber());
  }
  if (min == max + n) {
    if (flush) return Combination::straight_flush;
    return Combination::straight;
  }
  if (flush) return Combination::flush;
  return Combination::sum;
}

void Board::addCard(const Card& card, const Side side, const unsigned int n) {
	if (n >= border_nb) { throw BoardException("Board add Card : unexistant border"); }
	borders[n].addCard(card, side);
}

const Card& Board::removeCard(const Card& card, const Side side, const unsigned int n){
  if (n >= border_nb) { throw BoardException("Board add Card : unexistant border"); }
  borders[n].removeCard(card, side);
}

const Side& Board::isBorderWon(const unsigned int n) const {
  if (borders[n].getRevendication() != none ) return borders[n].getRevendication();
  return borders[n].isWon();
}

