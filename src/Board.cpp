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

  combination[++*size] = &card;
  if (*size == max_size)
	firstCompleted = side;
  else if (*size != max_size && firstCompleted != Side::none)
	firstCompleted = Side::none;
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

const bool recursiveCombinationType(int* baseComb, const Card* possibleCards[], const size_t maxSize, int* maxSum, const size_t size = 0) {
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

const CombinationType Stone::evaluateCombination(const Card* c[], size_t n, int* max = nullptr) {//evaluation of a full card combination
	list<Color> commonColors(Colors);
	list<Number> commonNumbers(Numbers);
	array<list<const Card*>, 9> cardNumberTable = array<list<const Card*>, 9>();
	int maxSum = 0;
	for (int i = 0; i < n; i++) {
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
		if (recursiveCombinationType(new int[n], c, n, max)) {
			cout << "evaluateCombination : check" << endl;
			if (flush)
				return CombinationType::straight_flush;
			return CombinationType::straight;
		}
	}
	
	//toak
	if (!commonNumbers.empty()){
		*max = toInt(commonNumbers.back()) * n;
		return CombinationType::three_of_a_kind;
	}
	*max = maxSum;
	//flush
	if (flush)
		return CombinationType::flush;

	return CombinationType::sum;
	
	/*
	bool flush = true;
	bool toak = true;

	for (size_t i = 1; i < n; i++) {
		if (toInt(c[i - 1]->higherPossibleNumber()) != toInt(c[i]->higherPossibleNumber())) {
			toak = false;
			break;
		}
	}
	if (toak)
		return CombinationType::three_of_a_kind;

	for (size_t i = 1; i < n; i++) {
		if (c[i]->getColor() != c[i - 1]->getColor()) {
			flush = false;
			break;
		}
	}
	int min = toInt(c[0]->getNumber());
	int max = toInt(c[0]->getNumber());
	for (size_t i = 1; i < n; i++) {
		if (toInt(c[i]->getNumber()) < min)
			min = toInt(c[i]->getNumber());
		if (toInt(c[i]->getNumber()) > max)
			max = toInt(c[i]->getNumber());
	}
	if (min == max + n) {
		if (flush)
			return CombinationType::straight_flush;
		return CombinationType::straight;
	}
	if (flush)
		return CombinationType::flush;
	return CombinationType::sum;*/
}
/*
list<const Card**> Stone::combinationVariationFromIncompleteCombination(const Card** possibleCards, const size_t pcn, const Card** incompleteCombination, const size_t icn, const size_t desiredSize, size_t& nbOfComninationFound) {
	nbOfComninationFound = 0;
	list<const Card**> variations;
	
	const Card** possibleCardsLeft = possibleCards; 
	const size_t pcnl = pcn;

	for (int i = 0; i < pcn; i++) {



	}
	return variations;
}
*/

const Side Stone::compareCombination(const Card* c1[], const Card* c2[], int combination_size) { //WARNING : mind the order of c1 and c2 arguments !!!
	int sum_s1 = 0;
	int sum_s2 = 0;
	const CombinationType combiType_s1 = evaluateCombination(c1, combination_size, &sum_s1);
	const CombinationType combiType_s2 = evaluateCombination(c2, combination_size, &sum_s2);

	//comparing combinations types
	const Side typeEval = compareCombinationType(combiType_s1, combiType_s2);
	if (typeEval != Side::none) return typeEval;

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


const Card** recursiveVariation(const Card** possibleCards, const size_t pcn, const Card** baseCombination, const size_t size, const size_t desiredSize, const  CombinationType combinationToBeat,const size_t sumToBeat) {

	if (size == desiredSize) {
		int max;
		CombinationType resultCombType= Stone::evaluateCombination(baseCombination, desiredSize, &max);
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


		const Card** resultComb= recursiveVariation(possibleCards, pcn-1, baseCombination, size + 1, desiredSize, combinationToBeat,  sumToBeat);
		if (resultComb != nullptr) {
			return resultComb;
		}
	}
	return nullptr;
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

void quickSort(const Card** cards, int end, int start =0) {
	if (start < end) {
		int pivot = toInt(cards[end]->higherPossibleNumber());
		int pos = partition(cards, start, end, pivot);

		quickSort(cards, pos - 1, start);
		quickSort(cards, end, pos + 1);
	}
}

const Card** Stone::bestVariation(const Card** possibleCards, const size_t pcn, const Card** incompleteCombination, const size_t icn, const size_t desiredSize, CombinationType combinationToBeat, const size_t sumToBeat){
	quickSort(possibleCards, pcn-1);
	const Card** combi = new const Card*[desiredSize];
	for (size_t i = 0; i < desiredSize; ++i) {
		if (i < icn)
			combi[i] = incompleteCombination[i];
	}
	const Card** resultCombi = recursiveVariation(possibleCards, pcn, combi, icn, desiredSize, combinationToBeat, sumToBeat);
	return resultCombi;
	

	return possibleCards;
	//Version amelioree incomplete
	/*
	if (desiredSize < icn) { throw BoardException("bestVariation Error : desired size is less than the incomplete combination size !"); }
	if (desiredSize == icn) { return incompleteCombination; }
	if (pcn < desiredSize - icn) { return nullptr; }


	list<Color> commonColors(Colors);
	list<Number> commonNumbers(Numbers);
	array<list<const Card*>, 9> cardNumberTable = array<list<const Card*>, 9>();

	for (int i = 0; i < icn; i++) {
		//Search for common colors among the incomplete combination for eventual flush
		list<Color> commonColorsCpy(commonColors);
		for (auto& pc : commonColorsCpy) {
			if (!incompleteCombination[i]->canBeUsedAs(pc)) {
				commonColors.remove(pc);
			}
		}

		//Search for common number among the incomplete combination for eventual straight or three-of-a-kind
		list<Number> commonNumbersCpy(commonNumbers);
		for (auto& pn : commonNumbersCpy) {
			if (!incompleteCombination[i]->canBeUsedAs(pn)) {
				commonNumbers.remove(pn);
			}
			else {
				cardNumberTable[toInt(pn) - 1].push_front(incompleteCombination[i]);
			}
		}
	}


	bool sameColor = commonColors.size() > 1;

	//searching for straight
	//WIP
	list<const Card**> combs = possibleIncompleteStraigh(cardNumberTable, desiredSize, icn);
	const Card** bestStraightCombination = combs.front();
	return bestStraightCombination;

	//searching for three-of-a-kind
	bool sameNumber = commonNumbers.size() > 1;
	if (sameNumber) {
		//three-of-a-kind is possible
		for (auto& cn : commonNumbers) {
			const Card** bestToek = new const Card * [desiredSize];
			size_t combinationSize = icn;
			for (size_t i = 0; i < icn; ++i) {
				bestToek[i] = incompleteCombination[i];
			}

			size_t i = 0;
			while (combinationSize < desiredSize && i < pcn) {
				if (possibleCards[i]->canBeUsedAs(cn)) {
					bestToek[combinationSize++] = possibleCards[i];
				}
				++i;
			}
			if (combinationSize == desiredSize) {cout<<"TOEK !"<<endl; return bestToek; }
		}

	}

	//searching flush
	if (sameColor) {
		//flush is possible
		for(auto& cc: commonColors){
			const Card** bestFlush = new const Card * [desiredSize];
			size_t combinationSize = icn;
			for (size_t i = 0; i < icn; ++i) {
				bestFlush[i] = incompleteCombination[i];
			}
			size_t i = 0;
			while (i < pcn) {
				if (possibleCards[i]->canBeUsedAs(cc)) {
					size_t j = icn;
					while (j < desiredSize) {
						cout << j <<"/"<< combinationSize << endl;
						if (j == combinationSize) {
							cout <<"fresh card !" << endl;
							bestFlush[combinationSize++] = possibleCards[i];
							break;
						}
						else {
							const Card* temp = bestFlush[j];
							if (toInt(temp->higherPossibleNumber()) < toInt(possibleCards[i]->higherPossibleNumber())) {
								bestFlush[j] = possibleCards[i];
								const Card* temp2;
								for (size_t k = j + 1; k < desiredSize; ++k) {
									cout << "moving from "<<k-1<<" to "<<k << endl;
									temp2 = bestFlush[k];
									bestFlush[k] = temp;
									temp = temp2;
									if (k == combinationSize) {++combinationSize; break;}
								}
								break;
							}
						}
						++j;
					}
				}
				++i;
			}
			if (combinationSize == desiredSize) { cout << "flush !" << endl; return bestFlush; }
		}
	}

	//searching for sum
	const Card** bestSum = new const Card * [desiredSize];
	size_t combinationSize = icn;
	for (size_t i = 0; i < icn; ++i) {
		bestSum[i] = incompleteCombination[i];
	}
	size_t i = 0;
	while (i < pcn) {
		size_t j = icn;
		while (j < desiredSize) {
			cout << j << "/" << combinationSize << endl;
			if (j == combinationSize) {
				cout << "fresh card !" << endl;
				bestSum[combinationSize++] = possibleCards[i];
				break;
			}
			else {
				const Card* temp = bestSum[j];
				if (toInt(temp->higherPossibleNumber()) < toInt(possibleCards[i]->higherPossibleNumber())) {
					bestSum[j] = possibleCards[i];
					const Card* temp2;
					for (size_t k = j + 1; k < desiredSize; ++k) {
						cout << "moving from " << k - 1 << " to " << k << endl;
						temp2 = bestSum[k];
						bestSum[k] = temp;
						temp = temp2;
						if (k == combinationSize) { ++combinationSize; break; }
					}
					break;
				}
			}
			++j;
		}
		++i;
	}
	if (combinationSize == desiredSize) { return bestSum; }
	return nullptr;
	*/
}

const Side Stone::evaluateWinningSide(const Card** AvailableCards, const size_t availableCardsCount) const { //evaluate the combinations to determine a winning side (can be none)
	//in order to compare sides, at least one side must be complete
	if (size_p1 == max_size && size_p2 == max_size) { //both sides are complete
		Side winningSide = compareCombination(combination_p1, combination_p1, max_size);
		if (winningSide != Side::none) return winningSide;
		return firstCompleted;
	}
	//one side is complete and the other is not
	if (size_p1 == max_size && size_p2 != max_size) {
		//if a better combination than side 1's can't be determined, s1 can win the border
		int sum_p1;
		const CombinationType combiType_p1 = evaluateCombination(combination_p1, max_size, &sum_p1);
		const Card** bestVar = bestVariation(AvailableCards, availableCardsCount, combination_p2, size_p2, max_size, combiType_p1, sum_p1);
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
		const CombinationType combiType_p1 = evaluateCombination(combination_p2, max_size, &sum_p2);
		const Card** bestVar = bestVariation(AvailableCards, availableCardsCount, combination_p1, size_p1, max_size, combiType_p1, sum_p2); //conversion int to size_t !!!
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
	if (n < 0 || n > 9) throw ShottenTottenException("evaluateStoneWinningSide : incorrect stone number");
	const Side& revendication = borders[n].getRevendication();
	if (revendication != Side::none)
		return revendication;
	return borders[n].evaluateWinningSide(AvailableCards, availableCardsCount);
}


/*
const CombinationType Stone::evaluateCombination(const Clan* c[],size_t n) { //evaluation of a full card combination
  bool flush = true;
  bool toak = true;

  for (size_t i = 1; i < n; i++) {
	if (toInt(c[i - 1]->getNumber()) != toInt(c[i]->getNumber())) {
	  toak = false;
	  break;
	}
  }
  if (toak)
	return CombinationType::three_of_a_kind;

  for (size_t i = 1; i < n; i++) {
	if (c[i]->getColor() != c[i - 1]->getColor()) {
	  flush = false;
	  break;
	}
  }
  int min = toInt(c[0]->getNumber());
  int max = toInt(c[0]->getNumber());
  for (size_t i = 1; i < n; i++) {
	if (toInt(c[i]->getNumber()) < min)
	  min = toInt(c[i]->getNumber());
	if (toInt(c[i]->getNumber()) > max)
	  max = toInt(c[i]->getNumber());
  }
  if (min == max + n) {
	if (flush)
	  return CombinationType::straight_flush;
	return CombinationType::straight;
  }
  if (flush)
	return CombinationType::flush;
  return CombinationType::sum;
}


const size_t Stone::combinationSumFromCompleteCombination(const Clan* c[], size_t n) {
	size_t sum = 0;
	for (size_t i = 0; i < n; i++) {
		sum += toInt(c[i]->getNumber());
	}
	return sum;
}



const Side Stone::compareCombinationSum(const Clan *c1[], const Clan *c2[], size_t n) {
  if (Stone::combinationSumFromCompleteCombination(c1, n) > Stone::combinationSumFromCompleteCombination(c2, n))
	return Side::s1;
  if (Stone::combinationSumFromCompleteCombination(c1, n) < Stone::combinationSumFromCompleteCombination(c2, n))
	return Side::s2;
  return Side::none;
}

const Side Stone::compareCombination(const Clan *c1[], const Clan *c2[], size_t n){
  Side side=Stone::compareCombinationType(c1,c2);
  if (side!=Side::none) return side;
  side=Stone::compareCombinationSum(c1, c2, n);
  if (side!=Side::none) return side;
  return getFirstCompletedSide();
}

void Board::addCard(const Card &card, const Side side, const unsigned int n) {
  if (n >= stone_nb) {
	throw BoardException("Board add Card : unexistant border");
  }
  borders[n].addCard(card, side);
}

const Card &Board::removeCard(const Card &card, const Side side,
							  const unsigned int n) {
  if (n >= stone_nb) {
	throw BoardException("Board add Card : unexistant border");
  }
  return borders[n].removeCard(card, side);
}




*/
/*
if (size_p1==max_size && size_p2==max_size) return compareCombination(combination_p1, combination_p2);
if (size_p1!=max_size && size_p2!=max_size) return Side::none;

if (size_p1==max_size) {
  size_t pcn=deck.getCardCount()+hand2.getSize();
  //creer tableau des cartes (possibleCards[pcn]) dans le deck et dans la hand
  const Card*** combinaisons=combinationVariation(possibleCards, pcn, combination_p2,
  size_p2, max_size);
  Side side=Side::s1;
  int i=0;
  while(combinaisons[i]!=nullptr && side==Side::s1){
	side=compareCombination(combination_p1, combinaisons[i]);
	i++;
	if (side==Side::s2) side=Side::none;
  }
  return side;
};

if (size_p2==max_size) {
  size_t pcn=deck.getCardCount()+hand1.getSize();
  //creer tableau des cartes (possibleCards[pcn]) dans le deck et dans la hand
  const Card*** combinaisons=combinationVariation(possibleCards, pcn, combination_p1,
  size_p1, max_size);;
  Side side=Side::s2;
  int i=0;
  while(combinaisons[i]!=nullptr && side==s2){
	side=compareCombination(combinaisons[i], combination_p2);
	i++;
	if (side==Side::s1) side=Side::none;
  }
  return side;
};

*/
/*

  for (i = 0; i<taille_max; i++){
	compléter combinaison avec carte[i];
	terminer de compléter la combinaison avec un sous fonction
	évaluer la combinaison
  }

	sous fonction :
	  for (i = 0; i<taille_max; i++){
	  compléter combinaison avec carte[i];
	  terminer de compléter la combinaison avec un sous fonction
	}*/

  /*
	void NonComplete(int n, int n_current combinaison c1, cartes_dispo, int
  n_dispo) {
	  //condition arret
	  if (n_current == 0) {
		  //on recupere la meilleure combinaison
		  if evaluation_combi(c) > evaluation_combi(WIN)
			  WIN = c;
	  }

	  pioche_cur = pioche + main_joueur;
	  for (size_t i = 0; i < n_dispo; i++) {
		  //compléter la carte n° n-n_current avec une carte de cartes dispo[i]
		  cartes_dispo = cartes_dispo - carte_choisie;
		  NonComplete(n, n_current - 1, combinaison c1, cartes_dispo, n_dispo -
  1);
	  }
  }
  */
  /*
const Card *** Stone::combinationVariationFromIncompleteCombination(const Card ** possibleCards,
										   const size_t pcn,
										   const Card **incompleteCombination,
										   const size_t icn,
										   const size_t desiredSize,
										   size_t &nbOfCombinationFound) const {
  for (size_t i = icn; i < desiredSize; ++i) {
	for (size_t pn = 0; pn < pcn; ++pn) {
	  // A finir
	}
  }
};
*/

