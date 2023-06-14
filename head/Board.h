#pragma once
#include <iostream>
#include "../exception/ShottenTottenException.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <list>
#include <array>
#include <vector>

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
const bool recursiveCombinationType(int* baseComb, const PlacableCard*const* possibleCards,  const size_t maxSize, int* max, const size_t size =0);

class Stone {
private:
	size_t max_size;
	vector<const PlacableCard*> combination_p1;
	vector<const PlacableCard*> combination_p2;
	const CombatMode* combat_mode = nullptr;
	Side revendication;
	Side firstCompleted;

public:
	Stone()
		: max_size(3),
		combination_p1(0),
		combination_p2(0), revendication(Side::none),
		firstCompleted(Side::none) {}
	~Stone() {
	}
	Stone(const Stone&) = delete;
	Stone& operator=(const Stone&) = delete;
	size_t getMaxSize() const { return max_size; }
	size_t getSizeP1() const { return combination_p1.size(); }
	size_t getSizeP2() const { return combination_p2.size(); }
	size_t getSideSize(Side s) const { return s == Side::s1 ? combination_p1.size() : combination_p2.size(); }
	const PlacableCard* getCard(Side s, unsigned int n) { return (s == Side::s1) ? combination_p1[n] : combination_p2[n]; }
	bool isFull(Side s) {
		return revendication != Side::none || (s == Side::s1 ? getSizeP1() : getSizeP2()) == max_size;
	}
	const vector<const PlacableCard*> getCombinationP1() const { return combination_p1; }
	const vector<const PlacableCard*> getCombinationP2() const { return combination_p2; }
	/*const PlacableCard** getCombinationSide(Side s) const {
		if (s == Side::none) throw ShottenTottenException("(Stone::getCombinationSide()) - Side s can't be none.");
		if (s == Side::s1) return combination_p1;
		return combination_p2;
	}*/
	Side getFirstCompleted() const { return firstCompleted; }
	const Side getRevendication() const { return revendication; }
	const CombatMode* getCombatMode() const { return combat_mode; }

	void setMaxSize(const size_t size);
	void setCombatMode(const CombatMode* cM);
	void setRevendication(Side s);

	void addCard(const PlacableCard& card, const Side side);
	void removeCard(const PlacableCard& card, const Side side);

	// ITERATOR : methods
	/*StoneIterator begin(Side side) {
		if (side == Side::s1) { return StoneIterator(combination_p1, 0); }
		else { return StoneIterator(combination_p2, 0); }
		}
	StoneIterator end(Side side) {
		if (side == Side::s1) { return StoneIterator(combination_p1, size_p1); }
		else { return StoneIterator(combination_p2, size_p2); }
	}*/
	
	//determine if the border is won by any side
	const Side evaluateWinningSide(const PlacableCard** AvailableCards, const size_t availableCardsCount) const;
	//same but with complete stone
	const Side evaluateWinningSide() const;

	//Return the best and the worse of all possible variations of an incomplete card combination
	static const PlacableCard** bestVariation(const PlacableCard** possibleCards, const size_t pcn, const PlacableCard** incompleteCombination, const size_t icn, const size_t desiredSize, CombinationType combinationToBeat, const size_t sumToBeat, bool combat_mode_mud_prensence);

	//Determines the type out of a complete card combination, sets the sum of the cards in max if given
	static const CombinationType evaluateCompleteCombinaison(const PlacableCard*const* c, size_t combination_size, int* max = nullptr);

	//Determines the type out of an incomplete card combination, sets the sum of the cards in max if given
	static const CombinationType evaluateCombinaison(const PlacableCard*const* c, size_t combination_size, int* max = nullptr);

	//Return which Combination (same size) is the strongest
	static const Side compareCombination(const PlacableCard* c1[], const PlacableCard* c2[], int combination_size, bool combat_mode_mud_prensence = 0); //ajouter un argument ; bool/énum "evaluationType" 

	//Compare the value of two Combinations type
	static const Side compareCombinationType(const CombinationType& p1, const CombinationType& p2);
};

class Board {
private:
	vector<Stone> stones; //const Stone* ?

	// indique si les checks prÃ©cÃ©dents ont dÃ©terminÃ© que la partie Ã©tait gagnÃ©e
	bool won = false; 

public:
	Board(size_t size = 9) : stones(size) {}
    ~Board() = default;
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
	Stone& getStone(unsigned int n){ 
		if (n < 0 || n > 9) throw ShottenTottenException("getStone : incorrect stone number n");
		return stones[n];
	}
	const Stone& getStone(unsigned int n) const {
		if (n < 0 || n > 9) throw ShottenTottenException("getStone : incorrect stone number n");
		return stones[n];
	}
	size_t getStoneNb() const { return stones.size(); }

	void addCard(const PlacableCard& card, const Side side, const unsigned int n) { if (n > 9) throw BoardException("Board addCard error : 0<=n<9"); stones[n].addCard(card, side); };
	void getPlayableStones(PlacableCard* c) { std::cout << "\nBoard::getPlayableStones();"; }
	bool full(Side side) {
		for (auto& s : stones) {
			if (!s.isFull(side))
				return false;
		}
		return true;
	}
	// ITERATOR : methods
	//BoardIterator begin() { return stones.begin(); }
	//BoardIterator end() { return BoardIterator(stones, stone_nb); }

	vector<Stone>& getStones() { return stones; }

	//Return which side as won a specific stone
	const Side evaluateStoneWinningSide(const unsigned int n, const PlacableCard** AvailableCards, const size_t availableCardsCount) const;
	//same thing but for complete stone
	const Side evaluateStoneWinningSide(const unsigned int n) const;

	//Evaluates if the game is won
	const Side evaluateGameWinner() const;
};
