#pragma once
#include "../exception/ShottenTottenException.h"
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"
#include "Board.h"
#include "Hand.h"
#include "Player.h"
#include <iostream>
#include <string>



class Controller{
private:
	const Version version = Version::legacy;
	Deck* clanDeck = nullptr;
	Board board;
	Game clanGame;
	Player* player1;
	Player* player2;
	bool turn = 0;
	friend class Supervisor;

	// scores de manche stockés ici car impactent directement
	// la fin de boucle de manche et de partie
	unsigned int remainingRounds;
    unsigned int totalRounds;
	unsigned int maxScore;

	unsigned int playerCardPick;

	void newRound(); // événement de début de manche
	void checkRound(); // verifie si la manche est gagnée
	void eventStartTurn(); // lance un nouveau tour de joueur

public:
	Controller(const Controller& c) = delete;
	Controller& operator=(const Controller& c) = delete;

	Deck& getClanDeck() const { return *clanDeck; }
	Game getClanGame() { return clanGame; }
	Board& getBoard() { return board; }
	Player& getPlayer1() const  { return *player1; }
	Player& getPlayer2() const  { return *player2; }
	bool getRound() const { return round; }
	bool getStop() const  { return stop; }
	int getRemainingRounds() const { return remainingRounds; }
	int getTotalRounds() { return totalRounds; }


	// setting players AI
	void setPlayer1(Player* player) { player1 = player; }
    void setPlayer2(Player* player) { player2 = player; }

	// initialise la partie, lancé via l'interface
	// tous les paramètres de partie présents sur l'interface doivent lui être passés
	// on pourrait aussi gérer certains paramètres via le Superviseur.
	void runGame(unsigned int nbturns, unsigned int winthreshold); // (int nbTurns, int typeia, ...)

	// CardIterator getPlayerHand() {}
	void getPickableCards() { std::cout << "\ngetPickableCards();"; } // récupère la liste des cartes jouables
	void getUnclaimedStones() { std::cout << "\ngetUnclaimedStones();"; }
	void getPlayableStones() { // utilise la carte sélectionnée pour regarder si la stone est okay
		Card* card = nullptr;
		// if (turn) {card = player1->getPick();} else {card = player2->getPick();}
		board.getPlayableStones(card); // actualy getting a return value
		getUnclaimedStones();
		std::cout << "\ngetPlayableStones();";
		}

	void qtGameOver() {
		std::cout << "\n================================ qtGameOver";
	}
	void qtDisplayPlayerTurn() {
		std::cout << "\n================================ qtDisplayPlayerTurn";
		getPickableCards(); // actually getting a return value
		std::cout << "\nenvoie à qt la liste des cartes jouables pour ce joueur";
		std::cout << "\ndemande a QT d'afficher le menu pour selectionner des cartes, piocher, ou revandiquer une borne";
	}
	void qtDisplayStonePicker() { // contient la liste des Stones éligibles
		std::cout << "\n================================ qtDisplayStonePicker";
		std::cout << "\nenvoie à qt la liste des bornes sélectionnables pour ce joueur";
		std::cout << "\ndemande a QT d'afficher le menu pour selectionner des bornes";
	}
	void eventCardPicked(string c) {
		std::cout << "\n================================ eventCardPicked";
		playerCardPick = 0; // enregistre le choix du joueur
		getUnclaimedStones(); // actually getting a return value => passed on to qtDisplayStonePicker()
		qtDisplayStonePicker();
	}
	void eventStonePicked() {
		std::cout << "\n================================ eventStonePicked";
		std::cout << "\nactive l'effet de la carte, les modifications sur l'etat du jeu";
		// vérifie si la carte requiert plus de bornes à sélectionner (effets actifs)
		// active l'effet de la carte et récupère un message
		// enregistre le tout dans 
	}
	void qtDisplayAlert() {
		std::cout << "\n================================ qtDisplayAlert";
		std::cout << "\naffiche un message sur le plateau de jeu";
	}
	void eventChoiceDraw() {
		std::cout << "\n================================ choiceDraw";
		std::cout << "\n\n\n\n\n TARGETTT !!!!";
		const Card& c = clanDeck->draw();
		// updating player's hand

		std::cout << "\nNEW CARD : " << c.getName();

		const Card& c2 = clanDeck->draw();
		std::cout << "\nNEW CARD : " << c2.getName();

		std::cout << "\nWon't print because game shut down.";

		//player1->getHand()->add(c);

		Hand& hand = *player1->getHand();
		for (const Card& card : hand) {
			// Do something with card
			std::cout << "\nCARD : " << card.getName();
		}

		qtDisplayPlayerTurn();
	}
	void eventChoiceEndTurn() {
		std::cout << "\n================================ choiceEndTurn";
		eventStartTurn();
	}
	void eventChoiceClaim() {
		std::cout << "\n================================ choiceClaim";
		getUnclaimedStones();
		qtDisplayStonePicker();
	}
protected:
	Controller(const Version& v, const string& p1name, const string& p2name, unsigned int AI_player1, unsigned int AI_player2)
		: version(v), 
		clanGame(Game(v)), 
		clanDeck(new Deck(Game(v))), 
		board(Board()), 
		player1(new Player(p1name)), 
		player2(new Player(p2name)) 
	{
		if (v != Version::legacy) throw ShottenTottenException("Controller constructor : version isn't legacy");

		std::cout << "\n\nDRAWING CARDS FOR THE DECK";
		//player1->getHand()->drawCards(clanDeck, 6);
	}
	~Controller() {
		delete clanDeck;
	}
};

class TacticController : public Controller {
private :
	const Version version = Version::tactic;
	Deck* tacticDeck = nullptr;
	Game tacticGame;
	friend class Supervisor;
public :
	TacticController(const Version& v, const string& name_player1, const string& name_player2, unsigned int AI_player1, unsigned int AI_player2)
		: Controller(Version::legacy, name_player1, name_player2, AI_player1, AI_player2), tacticGame(Game(v)) {
		tacticDeck = new Deck(tacticGame);
		if (v != Version::tactic) throw ShottenTottenException("Controller constructor : version isn't tactic");
	}
	~TacticController() {
		delete tacticDeck;
	}
	Deck& getTacticDeck() const { return *tacticDeck; }
	Game& getTacticGame() { return tacticGame; }
};
