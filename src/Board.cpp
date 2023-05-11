#include "../head/Board.h"

void Stone::addCard(const Card &card, const Side side) {
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

const Card &Stone::removeCard(const Card &card, const Side side) {
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

void Stone::changeMaxSize(const size_t size) {
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


const Side Stone::compareCombination(const Card* c1[], const Card* c2[], size_t n) {
	//à completer
	return Side::none;
}
list<const Card**> Stone::combinationVariationFromIncompleteCombination(const Card** possibleCards, const size_t pcn, const Card** incompleteCombination, const size_t icn, const size_t desiredSize, size_t& nbOfComninationFound) {
	nbOfComninationFound = 0;
	list<const Card**> variations;
	
	const Card** possibleCardsLeft = possibleCards; 
	const size_t pcnl = pcn;

	for (int i = 0; i < pcn; i++) {



	}

	
	return variations;
}

const Card** Stone::bestVariation(const Card** possibleCards, const size_t pcn, const Card** incompleteCombination, const size_t icn, const size_t desiredSize){
	if (desiredSize < icn) { throw BoardException("bestVariation Error : desired size is less than the incomplete combination size !"); }
	if (desiredSize == icn) { return incompleteCombination; }
	if (pcn < desiredSize - icn) { return nullptr; }


	list<Color> commonColors(Colors);
	list<Number> commonNumbers(Numbers);
	Number min;
	Number max;

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
		for (auto& pc : commonNumbersCpy) {
			if (!incompleteCombination[i]->canBeUsedAs(pc)) {
				commonNumbers.remove(pc);
			}
		}
	}


	bool sameColor = commonColors.size() > 1;

	//searching for straight
	//WIP
	const Card** bestStraightCombination = nullptr;
	if (icn > 1 && commonNumbers.size()>= desiredSize) {
		size_t spread = toInt(commonNumbers.back()) - toInt(commonNumbers.front());
		if (spread < 0) throw ShottenTottenException("Numbers Error : Number aren't put in order");
		if (spread < desiredSize) {
			//straight is possible
		}
	}

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
}

const Side Stone::isWon(const Card** AvailableCards, const size_t availableCardsCount) const {
	const Card** p1BestVar;
	const Card** p2BestVar;
	const Card** p1WorseVar;
	const Card** p2WorseVar;

	p1BestVar = Stone::bestVariation(AvailableCards, availableCardsCount, combination_p1, size_p1, max_size);
	p2BestVar = Stone::bestVariation(AvailableCards, availableCardsCount, combination_p1, size_p1, max_size);


	return Side::none;
}

const Side Board::isStoneWon(const unsigned int n,const Card** AvailableCards,const size_t availableCardsCount) const {
	const Side& revendication = borders[n].getRevendication();
	if (revendication != Side::none)
		return revendication;
	return borders[n].isWon(AvailableCards, availableCardsCount);
}


/*
const CombinationType Stone::combinationTypeFromCompleteCombination(const Clan* c[],size_t n) { //evaluation of a full card combination
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

const Side Stone::compareCombinationType(const CombinationType &s1,
									  const CombinationType &s2) {
  if (s1 == s2)
	return Side::none;
  if (s1 > s2) {
	return Side::s1;
  } else {
	return Side::s2;
  }
}

const size_t Stone::combinationSumFromCompleteCombination(const Clan *c[], size_t n) {
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
  if (n >= border_nb) {
	throw BoardException("Board add Card : unexistant border");
  }
  borders[n].addCard(card, side);
}

const Card &Board::removeCard(const Card &card, const Side side,
							  const unsigned int n) {
  if (n >= border_nb) {
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
	for (size_t pc = 0; pc < pcn; ++pc) {
	  // A finir
	}
  }
};
*/

