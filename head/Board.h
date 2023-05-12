#pragma once
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
		return "HAHAHAHAHAHAHA";
		break;
	}
}

const Card** bestStraighCompletion(list<const Card*> cardNumberTable[9], const Card** possibleCards, const size_t pcn, const size_t desiredSize, const size_t numberOfAvailableCards, const size_t highestNum = 9, const Card* partialResult[9] = nullptr);
const bool recursiveMachin(int* baseComb, const Card* possibleCards[],  const size_t maxSize, int* max, const size_t size =0);

class Stone {
private:
	size_t max_size;
	size_t size_p1;
	size_t size_p2;
	const Card** combination_p1;
	const Card** combination_p2;
	Side revendication;
	Side firstCompleted;

public:
	Stone()
		: max_size(3), size_p1(0), size_p2(0),
		combination_p1(new const Card* [max_size]),
		combination_p2(new const Card* [max_size]), revendication(Side::none),
		firstCompleted(Side::none) {}
	~Stone() {
		delete[] combination_p1;
		delete[] combination_p2;
	}
	const Side getRevendication() const { return revendication; }
	void addCard(const Card& card, const Side side);
	const Card& removeCard(const Card& card, const Side side);
	void changeMaxSize(const size_t size);
	
	//determine if the border is won by any side
	const Side isWon(const Card** AvailableCards, const size_t availableCardsCount) const;

	//Return all possible variations of an incomplete card combination
	static list<const Card**> combinationVariationFromIncompleteCombination(const Card** possibleCards, const size_t pcn, const Card** incompleteCombination, const size_t icn, const size_t desiredSize, size_t& nbOfComninationFound);
	
	//Return the best and the worse of all possible variations of an incomplete card combination
	static const Card** bestVariation(const Card** possibleCards, const size_t pcn, const Card** incompleteCombination, const size_t icn, const size_t desiredSize, CombinationType combinationToBeat, const size_t sumToBeat);

	//Determine the combination out of a card combination
	//a modifier pour les tactiques.
	static const CombinationType combinationTypeFromCompleteCombination(const Card* c[], size_t n, int* max = nullptr);

	//Return which Combination is the strongest
	static const Side compareCombination(const Card* c1[], const Card* c2[], size_t n);

	//Compare the value of two Combinations type
	static const Side compareCombinationType(const CombinationType& p1, const CombinationType& p2);

	/*
	//Compare the sum of all card numbers
	static const Side compareCombinationSum(const Clan* c1[], const Clan* c2[], size_t n);
		//Determine the sum of the card numbers
	static const size_t combinationSumFromCompleteCombination(const Clan* c[], size_t n);
	
	//Get which side has completed his side first
	const Side getFirstCompleted() { return firstCompleted; }
	*/

};

class Board {
private:
	Stone* borders;
	size_t border_nb;

public:
	Board(size_t size = 9) : border_nb(size), borders(new Stone[size]) {}
	~Board() { delete[] borders; }
	void addCard(const Card& card, const Side side, const unsigned int n);
	const Card& removeCard(const Card& card, const Side side,const unsigned int n);
	//Return which side as won a specific stone
	const Side isStoneWon(const unsigned int n,const Card** AvailableCards,const size_t availableCardsCount) const;
	//Return which side as won on the board
	const Side isBorderWon() const;
};