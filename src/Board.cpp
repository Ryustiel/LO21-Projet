#include "../head/Board.h"

void Stone::addCard(const Card &card, const Side side) { //add card on a given side of the stone
  const Card **combination;
  size_t *size;
  switch (side) {
  case Side::s1:
	combination = combination_p1;
	size = &size_p1;
	break;
  case Side::s2:
	combination = combination_p2;
	size = &size_p2;
	break;
  default:
	throw BoardException("Border addCard : unvalid side");
	break;
  }
  if (*size == max_size) {
	throw BoardException("Border addCard : this side of the border is full");
  }

  combination[(* size)++] = &card;
  if (*size == max_size && firstCompleted == Side::none)
	firstCompleted = side;
}

const Card &Stone::removeCard(const Card &card, const Side side) { //remove a card on a given side of the stone
  const Card **combination;
  size_t *size;
  switch (side) {
  case Side::s1:
	combination = combination_p1;
	size = &size_p1;
	break;
  case Side::s2:
	combination = combination_p2;
	size = &size_p2;
	break;
  default:
	throw BoardException("Border addCard : unvalid side");
	break;
  }
  if (*size == 0) {
	throw BoardException(
		"Border removeCard : this side of the border is empty");
  }
  size_t i = 0;
  while (combination[i] != &card && i < *size) {
	i++;
  }
  if (i == max_size) {
	throw BoardException("Border removeCard : this side of the border doesn't "
						 "contain this Card");
  }
  const Card &temp = *combination[i];
  combination[i] = combination[*size--];
  return temp;
}

void Stone::setMaxSize(const size_t size) {
  if (size == max_size) {
	return;
  }
  const Card **new_combination_j1 = new const Card *[size];
  const Card **new_combination_j2 = new const Card *[size];
  for (int i = 0; i < size_p1; i++) {
	new_combination_j1[i] = combination_p1[i];
  }
  for (int i = 0; i <= size_p2; i++) {
	new_combination_j2[i] = combination_p2[i];
  }
  delete[] combination_p1;
  delete[] combination_p2;
  combination_p1 = new_combination_j1;
  combination_p2 = new_combination_j2;
}

const bool recursiveCombinationType(int* baseComb, const Card* possibleCards[], const size_t maxSize, int* maxSum, const size_t size) {
	*maxSum = 0;
	if (size == maxSize) {
		int min = baseComb[0];
		int max = baseComb[0];
		*maxSum = baseComb[0];
		for (size_t i = 1; i < maxSize; i++) {
			for (size_t j = 0; j < i; ++j) {
				if (baseComb[i] == baseComb[j])
					return false;
			}
			if (baseComb[i] < min)
				min = baseComb[i];
			if (baseComb[i] > max)
				max = baseComb[i];
			*maxSum += baseComb[i];
		}
		return (min == max - maxSize + 1);
	}
	for (auto& nb : possibleCards[size]->possibleNumber()) {
		baseComb[size] = toInt(nb);
		if (recursiveCombinationType(baseComb, possibleCards, maxSize, maxSum, size + 1)) {
			return true;
		}
	}
	return false;
}

void swap(const Card** cards, int pos1, int pos2) {
	const Card* temp;
	temp = cards[pos1];
	cards[pos1] = cards[pos2];
	cards[pos2] = temp;
}

int partition(const Card** cards, int start, int end, int pivot) {
	int i = start;
	int j = start;
	while (i <= end) {
		if (toInt(cards[i]->higherPossibleNumber()) < pivot) {
			i++;
		}
		else {
			swap(cards, i, j);
			i++;
			j++;
		}
	}
	return j - 1;
}

void quickSort(const Card** cards, int end, int start = 0) {
	if (start < end) {
		int pivot = toInt(cards[end]->higherPossibleNumber());
		int pos = partition(cards, start, end, pivot);

		quickSort(cards, pos - 1, start);
		quickSort(cards, end, pos + 1);
	}
}

const CombinationType Stone::evaluateCombinaison(const Card* c[], size_t combination_size, int* max) {//evaluation of a full card combination
	list<Color> commonColors(Colors);
	list<Number> commonNumbers(Numbers);
	array<list<const Card*>, 9> cardNumberTable = array<list<const Card*>, 9>();
	int maxSum = 0;
	for (int i = 0; i < combination_size; i++) {
		//Search for common colors amongst the incomplete combination for eventual flush
		list<Color> commonColorsCpy(commonColors);
		for (auto& pc : commonColorsCpy) {
			if (!c[i]->canBeUsedAs(pc)) {
				commonColors.remove(pc);
			}
		}

		//Search for common number amongst the incomplete combination for eventual straight or three-of-a-kind
		list<Number> commonNumbersCpy(commonNumbers);
		for (auto& pn : commonNumbersCpy) {
			if (!c[i]->canBeUsedAs(pn)) {
				commonNumbers.remove(pn);
			}
			else {
				cardNumberTable[toInt(pn) - 1].push_front(c[i]);
			}
		}
		maxSum += toInt(c[i]->higherPossibleNumber());
	}

	bool flush = !commonColors.empty();

	if (commonNumbers.empty()) {
		if (recursiveCombinationType(new int[combination_size], c, combination_size, max)) {
			cout << "evaluateCombinaison : check" << endl;
			if (flush)
				return CombinationType::straight_flush;
			return CombinationType::straight;
		}
	}

	//toak
	if (!commonNumbers.empty()) {
		*max = toInt(commonNumbers.back()) * combination_size;
		return CombinationType::three_of_a_kind;
	}
	*max = maxSum;
	//flush
	if (flush)
		return CombinationType::flush;

	return CombinationType::sum;
}

//WARNING : mind the order of c1 and c2 arguments !!!
const Side Stone::compareCombination(const Card* c1[], const Card* c2[], int combination_size, bool combat_mode_mud_prensence) {
	int sum_s1 = 0;
	int sum_s2 = 0;
	const CombinationType combiType_s1 = evaluateCombinaison(c1, combination_size, &sum_s1);
	const CombinationType combiType_s2 = evaluateCombinaison(c2, combination_size, &sum_s2);

	//comparing combinations types
	if(!combat_mode_mud_prensence) {
		const Side typeEval = compareCombinationType(combiType_s1, combiType_s2);
		if (typeEval != Side::none) return typeEval;
	}

	//comparing combinations sums
	if (sum_s1 > sum_s2) return Side::s1;
	else if (sum_s2 > sum_s1) return Side::s1;

	return Side::none;
}

list<const Card**> possibleIncompleteStraigh(array<list<const Card*>, 9>& cardNumberTable, const size_t desiredSize, const size_t numberOfAvailableCards, const size_t highestNum = 8) {

	if (desiredSize < numberOfAvailableCards || highestNum+1 < numberOfAvailableCards) { return list<const Card**>(); }

	list<const Card**> possibilities = list<const Card**>();

	if (numberOfAvailableCards == 0) {
		const Card* tab[9];
		for (size_t i = 0; i < 9; ++i) { tab[i] = nullptr; }
		possibilities.push_front(tab);
		return possibilities;
	}
	if (!cardNumberTable[highestNum].empty()) {
		for (auto& card : cardNumberTable[highestNum]) {
			array<list<const Card*>, 9> cardNumberListCpy(cardNumberTable);
			cardNumberListCpy[highestNum].remove(card);
			list<const Card**> subPossibilities = possibleIncompleteStraigh(cardNumberListCpy, desiredSize - 1, numberOfAvailableCards - 1, highestNum - 1);
			for (auto& sp : subPossibilities) {
				sp[highestNum] = card;
				possibilities.push_front(sp);
			}			
		}
	}
	list<const Card**> subPossibilities = possibleIncompleteStraigh(cardNumberTable, desiredSize - 1, numberOfAvailableCards, highestNum - 1);
	for (auto& sp : subPossibilities) {
		sp[highestNum] = nullptr;
		possibilities.push_front(sp);
	}
	return possibilities;
}

const Side Stone::compareCombinationType(const CombinationType& s1, const CombinationType& s2) {
	if (s1 == s2)
		return Side::none;
	if (s1 > s2) {
		return Side::s1;
	}
	else {
		return Side::s2;
	}
}


const Card** recursiveVariation(const Card** possibleCards, const size_t pcn, const Card** baseCombination, const size_t size, const size_t desiredSize, const CombinationType combinationToBeat,const size_t sumToBeat, bool combat_mode_mud_prensence) {

	if (size == desiredSize) {
		int max;
		CombinationType resultCombType= Stone::evaluateCombinaison(baseCombination, desiredSize, &max);
		if (combat_mode_mud_prensence) {
			if (max > sumToBeat) {
				return baseCombination;
			}
			else {
				return nullptr;
			}
		}
		cout << "\recursiveVariation : end of recursive function\n Combination type = " << toString(resultCombType) << endl;
		Side s = Stone::compareCombinationType(resultCombType, combinationToBeat);
		cout << "recursiveVariation : max sum : " << max << endl;
		if (s == Side::s1 || (s == Side::none && sumToBeat < max)) {
			return baseCombination;
		}
		return nullptr;
	}
	
	for (size_t i = 0; i < pcn; ++i) {
		baseCombination[size] = possibleCards[i];
		const Card* tmp = possibleCards[pcn - 1];
		possibleCards[pcn - 1] = possibleCards[i];
		possibleCards[i] = tmp;

		//besoin de décaler les éléments ?

		const Card** resultComb= recursiveVariation(possibleCards, pcn-1, baseCombination, size + 1, desiredSize, combinationToBeat,  sumToBeat, combat_mode_mud_prensence);
		if (resultComb != nullptr) {
			return resultComb;
		}
	}
	return nullptr;
}

const Card** Stone::bestVariation(const Card** possibleCards, const size_t pcn, const Card** incompleteCombination, const size_t icn, const size_t desiredSize, CombinationType combinationToBeat, const size_t sumToBeat, bool combat_mode_mud_prensence){
	quickSort(possibleCards, pcn-1);
	const Card** combi = new const Card*[desiredSize];
	for (size_t i = 0; i < desiredSize; ++i) {
		if (i < icn)
			combi[i] = incompleteCombination[i];
	}
	const Card** resultCombi = recursiveVariation(possibleCards, pcn, combi, icn, desiredSize, combinationToBeat, sumToBeat, combat_mode_mud_prensence);
	return resultCombi;
	

	return possibleCards;
}

const Side Stone::evaluateWinningSide(const Card** AvailableCards, const size_t availableCardsCount) const { //evaluate the combinations to determine a winning side (can be none)
	//in order to compare sides, at least one side must be complete
	const bool mud_fight = (combat_mode != nullptr && combat_mode->getName() == "Mud Fight");
	if (size_p1 == max_size && size_p2 == max_size) { //both sides are complete
		Side winningSide;
		winningSide = compareCombination(combination_p1, combination_p2, max_size, mud_fight);
		if (winningSide != Side::none) return winningSide;
		return firstCompleted;
	}
	//one side is complete and the other is not
	if (size_p1 == max_size && size_p2 != max_size) {
		//if a better combination than side 1's can't be determined, s1 can win the border
		int sum_p1;
		CombinationType combiType_p1 = evaluateCombinaison(combination_p1, max_size, &sum_p1);
		if (combat_mode != nullptr && combat_mode->getName() == "Mud Fight")
			combiType_p1 = CombinationType::sum;
		const Card** bestVar = bestVariation(AvailableCards, availableCardsCount, combination_p2, size_p2, max_size, combiType_p1, sum_p1, mud_fight);
		//no need to compare the combinations, only the existence of a better hypothetical combination
		if (bestVar != nullptr) {
			cout << "A better combination can be made on side S2 !" << endl;
			for (int i = 0; i < max_size; i++) {
				if (bestVar[i] != nullptr) {
					cout << "(Card name : " << bestVar[i]->getName() << endl;
				}
				else {
					cout << "nullptr" << endl;
				}
			}
			//existence of a hypothetical combination can't assure a win
			return Side::none;
		} //if a better combination can't be estimated, side s1 can win the stone
		return Side::s1;
	}
	//last case
	if (size_p1 != max_size && size_p2 == max_size) {
		//if a better combination than side s2's can't be determined, s2 can win the border
		int sum_p2;
		CombinationType combiType_p2 = evaluateCombinaison(combination_p2, max_size, &sum_p2);
		if (combat_mode != nullptr && combat_mode->getName() == "Mud Fight")
			combiType_p2 = CombinationType::sum;
		const Card** bestVar = bestVariation(AvailableCards, availableCardsCount, combination_p1, size_p1, max_size, combiType_p2, sum_p2,mud_fight); //conversion int to size_t !!!
		//no need to compare the combinations, only the existence of a better hypothetical combination
		if (bestVar != nullptr) {
			cout << "A better combination can be made on side S2 !" << endl;
			for (int i = 0; i < max_size; i++) {
				if (bestVar[i] != nullptr) {
					cout << "(Card name : " << bestVar[i]->getName() << endl;
				}
				else {
					cout << "nullptr" << endl;
				}
			}
			//existence of a hypothetical combination can't assure a win
			return Side::none;
		} //if a better combination can't be estimated, side s1 can win the stone
		return Side::s2;
	}
	//default return
	return Side::none;
}


const Side Board::evaluateStoneWinningSide(const unsigned int n,const Card** AvailableCards,const size_t availableCardsCount) const {
	if (n < 0 || n > stone_nb) throw ShottenTottenException("evaluateStoneWinningSide : incorrect stone number");
	const Side& revendication = stones[n].getRevendication();
	if (revendication != Side::none)
		return revendication;
	return stones[n].evaluateWinningSide(AvailableCards, availableCardsCount);
}


const Side Board::evaluateGameWinner() const {
	size_t count_p1 = 0;
	size_t p1_in_a_row = 0;
	size_t count_p2 = 0;
	size_t p2_in_a_row = 0;

	for (size_t i = 0; i < stone_nb; i++) {
		if (stones[i].getRevendication() == Side::s1) {
			count_p1 += 1;
			p1_in_a_row += 1;
			p2_in_a_row = 0;
		} else if (stones[i].getRevendication() == Side::s2) {
			count_p2 += 1;
			p2_in_a_row += 1;
			p1_in_a_row = 0;
		}
		else if (stones[i].getRevendication() == Side::none) {
			p1_in_a_row = 0;
			p2_in_a_row = 0;
		}

		if (count_p1 == 5) {
			cout << "5 stones won : Player 1 wins !" << endl;
			return Side::s1;
		}
		if (p1_in_a_row == 3) {
			cout << "3 consecutive stones won : Player 1 wins !" << endl;
			return Side::s1;
		}

		if (count_p2 == 5) {
			cout << "5 stones won : Player 2 wins !" << endl;
			return Side::s2;
		}
		if (p2_in_a_row == 3) {
			cout << "3 consecutive stones won : Player 2 wins !" << endl;
			return Side::s2;
		}
	}
	//cout << "The game continues !" << endl;
	return Side::none;
}