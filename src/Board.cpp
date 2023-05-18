#include "../head/Board.h"

void Border::addCard(const Card &card, const Side side) {
  const Card **combination;
  size_t *size;
  switch (side) {
  case Side::j1:
    combination = combination_j1;
    size = &size_j1;
    break;
  case Side::j2:
    combination = combination_j2;
    size = &size_j2;
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

const Card &Border::removeCard(const Card &card, const Side side) {
  const Card **combination;
  size_t *size;
  switch (side) {
  case Side::j1:
    combination = combination_j1;
    size = &size_j1;
    break;
  case Side::j2:
    combination = combination_j2;
    size = &size_j2;
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

void Border::changeMaxSize(const size_t size) {
  if (size == max_size) {
    return;
  }
  const Card **new_combination_j1 = new const Card *[size];
  const Card **new_combination_j2 = new const Card *[size];
  for (int i = 0; i < size_j1; i++) {
    new_combination_j1[i] = combination_j1[i];
  }
  for (int i = 0; i <= size_j2; i++) {
    new_combination_j2[i] = combination_j2[i];
  }
  delete[] combination_j1;
  delete[] combination_j2;
  combination_j1 = new_combination_j1;
  combination_j2 = new_combination_j2;
}


const Combination Border::combinaisonFullEval(const Clan* c[],size_t n) { //evaluation of a full card combination
  bool flush = true;
  bool toak = true;

  for (size_t i = 1; i < n; i++) {
    if (toInt(c[i - 1]->getNumber()) != toInt(c[i]->getNumber())) {
      toak = false;
      break;
    }
  }
  if (toak)
    return Combination::three_of_a_kind;

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
      return Combination::straight_flush;
    return Combination::straight;
  }
  if (flush)
    return Combination::flush;
  return Combination::sum;
}

const Side Border::compareCombination(const Combination &j1,
                                      const Combination &j2) {
  if (j1 == j2)
    return Side::none;
  if (j1 > j2) {
    return Side::j1;
  } else {
    return Side::j2;
  }
}

const size_t Border::sum(const Clan *c[], size_t n) {
  size_t sum = 0;
  for (size_t i = 0; i < n; i++) {
    sum += toInt(c[i]->getNumber());
  }
  return sum;
}

const Side Border::compareCombinationSum(const Clan *c1[], const Clan *c2[], size_t n) {
  if (Border::sum(c1, n) > Border::sum(c2, n))
    return Side::j1;
  if (Border::sum(c1, n) < Border::sum(c2, n))
    return Side::j2;
  return Side::none;
}

const Side Board::compareSide(const Clan *c1[], const Clan *c2[], size_t n){
  Side side=Border::compareCombination(c1,c2);
  if (side!=Side::none) return side;
  side=Border::compareCombinationSum(c1, c2, n);
  if (side!=Side::none) return side;
  return getFirstCompleted();
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



const Side Board::isBorderWon(const unsigned int n, Deck &deck, Hand &hand_j1, Hand &hand_j2) const {
  if (borders[n].getRevendication() != Side::none)
    return borders[n].getRevendication();
  return borders[n].isWon(deck, hand_j1, hand_j_2);
}

const Side Border::isWon(Deck &deck, Hand &hand1, Hand &hand2) const {
 
  if (size_j1==max_size && size_j2==max_size) return compareSide(combination_j1, combination_j2);
  if (size_j1!=max_size && size_j2!=max_size) return Side::none;
  
  if (size_j1==max_size) {
    size_t pcn=deck.getCardCount()+hand2.getSize();
    //creer tableau des cartes (possibleCards[pcn]) dans le deck et dans la hand
    const Card*** combinaisons=combinationVariation(possibleCards, pcn, combination_j2,       
    size_j2, max_size);
    Side side=Side::j1;
    int i=0;
    while(combinaisons[i]!=nullptr && side==Side::j1){
      side=compareSide(combination_j1, combinaisons[i]);
      i++;
      if (side==Side::j2) side=Side::none;
    }
    return side;
  };
  
  if (size_j2==max_size) {
    size_t pcn=deck.getCardCount()+hand1.getSize();
    //creer tableau des cartes (possibleCards[pcn]) dans le deck et dans la hand
    const Card*** combinaisons=combinationVariation(possibleCards, pcn, combination_j1,       
    size_j1, max_size);;
    Side side=Side::j2;
    int i=0;
    while(combinaisons[i]!=nullptr && side==j2){
      side=compareSide(combinaisons[i], combination_j2);
      i++;
      if (side==Side::j1) side=Side::none;
    }
    return side;
  };
  
  
}
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
const Card *** Border::combinationVariation(const Card ** possibleCards,
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
