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

void Board::addCard(const Card& card, const Side side, const unsigned int n) {
	if (n >= border_nb) { throw BoardException("Board add Card : unexistant border"); }
	borders[n].addCard(card, side);
}
