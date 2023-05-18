#pragma once
#include <iostream>
#include "../exception/ShottenTottenException.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"

class BoardException : public ShottenTottenException {
  using ShottenTottenException::ShottenTottenException;
};

enum class Side { none, j1, j2 };
enum class Combination {
  sum,
  straight,
  flush,
  three_of_a_kind,
  straight_flush
};

class Border {
private:
  size_t max_size;
  size_t size_j1;
  size_t size_j2;
  const Card **combination_j1;
  const Card **combination_j2;
  Side revendication;
  Side firstCompleted;

public:
  Border()
      : max_size(3), size_j1(0), size_j2(0),
        combination_j1(new const Card *[max_size]),
        combination_j2(new const Card *[max_size]), revendication(Side::none),
        firstCompleted(Side::none) {}
  ~Border() {
    delete[] combination_j1;
    delete[] combination_j2;
  }
  const Side getRevendication() const { return revendication; }
  void addCard(const Card &card, const Side side);
  const Card &removeCard(const Card &card, const Side side);
  void changeMaxSize(const size_t size);
  const Side isBorderWon(const unsigned int n, Deck &deck, Hand &hand_j1,
                         Hand &hand_j2) const;
  const Side isWon(Deck &deck, Hand &hand1, Hand &hand2) const;
  static const Side compareCombination(const Combination &j1,
                                       const Combination &j2);
  static const Side compareCombinationSum(const Clan *c1[], const Clan *c2[],
                                          size_t n);
  static const Combination combinationFullEval(const Clan *c[], size_t n);
  static const size_t sum(const Clan *c[], size_t n);
  const Card ***combinationVariation(const Card **possibleCards,
                                     const size_t pcn,
                                     const Card **incompleteCombination,
                                     const size_t icn, const size_t desiredSize,
                                     size_t &nbOfComninationFound) const;
  const Side getFirstCompleted() { return firstCompleted; }
  const Side compareSide(const Clan *c1[], const Clan *c2[], size_t n);
};

class Board {
private:
  Border *borders;
  size_t border_nb;

  // indique si les checks précédents ont déterminé que la partie était gagnée
  bool won = false; 

public:
  Board(size_t size = 9) : border_nb(size), borders(new Border[size]) {}
  ~Board() { delete[] borders; }
  void addCard(const Card &card, const Side side, const unsigned int n);
  const Card &removeCard(const Card &card, const Side side,
                         const unsigned int n);
  const Side isBorderWon(const unsigned int n) const;

  // méthodes nécessaires à la gestion de la variable "won"
  void setWon() { won = true; }
  bool isWon() { return won; }

  // méthode d'initialisation générique, appelée au début de chaque manche
  void init() { std::cout << "\nInitializing board"; won = false;}
};