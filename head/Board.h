#pragma once
#include <iostream>
#include "../exception/ShottenTottenException.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <list>
#include <array>

using namespace std;

class BoardException : public ShottenTottenException {
	using ShottenTottenException::ShottenTottenException;
};


enum class Side { none, s1, s2 };
enum class CombinationType {
	sum,
	straight,
	flush,
	three_of_a_kind,
	straight_flush
};

inline string toString(CombinationType c) {
	switch (c)
	{
	case CombinationType::sum:
		return "sum";
		break;
	case CombinationType::straight:
		return "straight";
		break;
	case CombinationType::flush:
		return "flush";
		break;
	case CombinationType::three_of_a_kind:
		return "three_of_a_kind";
		break;
	case CombinationType::straight_flush:
		return "straight_flush";
		break;
	default:
		throw ShottenTottenException("toString : unaccurate CombinationType c");
		break;
	}
}

//bestStraightCompletion is unused
const PlacableCard** bestStraightCompletion(list<const PlacableCard*> cardNumberTable[9], const PlacableCard** possibleCards, const size_t pcn, const size_t desiredSize, const size_t numberOfAvailableCards, const size_t highestNum = 9, const PlacableCard* partialResult[9] = nullptr);
const bool recursiveCombinationType(int* baseComb, const PlacableCard* possibleCards[],  const size_t maxSize, int* max, const size_t size =0);

class Stone {
private:
	size_t max_size;
	size_t size_p1;
	size_t size_p2;
	const PlacableCard** combination_p1;
	const PlacableCard** combination_p2;
	const CombatMode* combat_mode = nullptr;
	Side revendication;
	Side firstCompleted;

public:
	Stone()
		: max_size(3), size_p1(0), size_p2(0),
		combination_p1(new const PlacableCard* [max_size]),
		combination_p2(new const PlacableCard* [max_size]), revendication(Side::none),
		firstCompleted(Side::none) {}
	~Stone() {
		delete[] combination_p1;
		delete[] combination_p2;
	}
	size_t getMaxSize() const { return max_size; }
	size_t getSizeP1() const { return size_p1; }
	size_t getSizeP2() const { return size_p2; }
	size_t getSideSize(Side s) { return s == Side::s1 ? size_p1 : size_p2; }
	const PlacableCard** getCombinationP1() const { return combination_p1; }
	const PlacableCard** getCombinationP2() const { return combination_p2; }
	Side getFirstCompleted() const { return firstCompleted; }
	const Side getRevendication() const { return revendication; }
	const CombatMode* getCombatMode() const { return combat_mode; }

	void setMaxSize(const size_t size);
	void setCombatMode(const CombatMode* cM);
	void setRevendication(Side s);

	void addCard(const PlacableCard& card, const Side side);
	const PlacableCard& removeCard(const PlacableCard& card, const Side side);
	
	//determine if the border is won by any side
	const Side evaluateWinningSide(const PlacableCard** AvailableCards, const size_t availableCardsCount) const;
	//same but with complete stone
	const Side evaluateWinningSide() const;

	//Return the best and the worse of all possible variations of an incomplete card combination
	static const PlacableCard** bestVariation(const PlacableCard** possibleCards, const size_t pcn, const PlacableCard** incompleteCombination, const size_t icn, const size_t desiredSize, CombinationType combinationToBeat, const size_t sumToBeat, bool combat_mode_mud_prensence);

	//Determines the type out of a complete card combination, sets the sum of the cards in max if given
	static const CombinationType evaluateCompleteCombinaison(const PlacableCard* c[], size_t combination_size, int* max = nullptr);

	//Determines the type out of an incomplete card combination, sets the sum of the cards in max if given
	static const CombinationType evaluateCombinaison(const PlacableCard* c[], size_t combination_size, int* max = nullptr);

	//Return which Combination (same size) is the strongest
	static const Side compareCombination(const PlacableCard* c1[], const PlacableCard* c2[], int combination_size, bool combat_mode_mud_prensence = 0); //ajouter un argument ; bool/énum "evaluationType" 

	//Compare the value of two Combinations type
	static const Side compareCombinationType(const CombinationType& p1, const CombinationType& p2);
};

class Board {
private:
	Stone* stones; //const Stone* ?
	size_t stone_nb;

  // indique si les checks prÃ©cÃ©dents ont dÃ©terminÃ© que la partie Ã©tait gagnÃ©e
  bool won = false; 

public:
	Board(size_t size = 9) : stone_nb(size), stones(new Stone[size]) {}
	~Board() { delete[] stones; }
	Stone* getStones() const { return stones;  }
	Stone& getStone(unsigned int n) const{ 
		if (n < 0 && n > 9) throw ShottenTottenException("getStone : incorrect stone number n");
		return stones[n];
	}
	size_t getStoneNb() const { return stone_nb;  }

	void addCard(const PlacableCard& card, const Side side, const unsigned int n) const { if (n > 9) throw BoardException("Board addCard error : 0<=n<9"); stones[n].addCard(card, side); };
	const PlacableCard& removeCard(const PlacableCard& card, const Side side,const unsigned int n);
	void getPlayableStones(PlacableCard* c) { std::cout << "\nBoard::getPlayableStones();"; }

	//Return which side as won a specific stone
	const Side evaluateStoneWinningSide(const unsigned int n, const PlacableCard** AvailableCards, const size_t availableCardsCount) const;
	//same thing but for complete stone
	const Side evaluateStoneWinningSide(const unsigned int n) const;

	//Evaluates if the game is won
	const Side evaluateGameWinner() const;
};