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
	Side current_side = Side::s1;
	friend class Supervisor;

	// scores de manche stockés ici car impactent directement
	// la fin de boucle de manche et de partie
	int remainingRounds;
    int totalRounds;
	int maxScore;
	Deck* clanDeck = nullptr;
	Board board;
	Game clanGame;
	Player* player1;
	Player* player2;
	size_t handSize;
	unsigned int playerCardPick;
	unsigned int playerStonePick;

	void newRound(); // événement de début de manche
	void checkRound(); // verifie si la manche est gagnée
	void eventStartTurn(); // lance un nouveau tour de joueur

public:
	Controller(const Controller& c) = delete;
	Controller& operator=(const Controller& c) = delete;
	
	//GETTERS
	Player* getCurPlayer() const {
		if (current_side == Side::s1) return player1;
		return player2;
	}
	Side getCurSide() { return current_side; }
	Version getVersion() const { return version; }
	Deck& getClanDeck() const { return *clanDeck; }
	Game getClanGame() { return clanGame; }
	Board& getBoard() { return board; }
	Player& getPlayer1() const  { return *player1; }
	Player& getPlayer2() const  { return *player2; }
	int getRemainingRounds() const { return remainingRounds; }
	int getTotalRounds() { return totalRounds; }

	Player* getWinner() const {
		if (player1->getScore() > player2->getScore()) return player1;
		if (player2->getScore() > player1->getScore()) return player2;
		return nullptr;
	}

	//SETTERS
	void setTotalRounds(int n) { totalRounds = n; }
	void setRemainingRounds(int n) { remainingRounds = n; }

	void setPlayersHand() {
		//player1->setHand();
	}

	// setting players AI
	// la manière de générer les instances des classes IA
	// peut être très différente, il faudra qu'on en discute
	//void setPlayer1(Player* player) { player1 = player; }
    //void setPlayer2(Player* player) { player2 = player; }

	virtual void claimStone(Side s, unsigned int n);
	// initialise la partie, lancé via l'interface
	// tous les paramètres de partie présents sur l'interface doivent lui être passés
	// on pourrait aussi gérer certains paramètres via le Superviseur.
	void runGame(int nbturns, int winthreshold); // (int nbTurns, int typeia, ...)

	// récupère la liste des cartes jouables
	bool* getPickableCards() {
		std::cout << "\ngetPickableCards();";
		bool pickable_cards[6] = { 0, 1, 0, 1, 1, 0 };
		return pickable_cards;;
	}
	void getUnclaimedStones() {std::cout << "\ngetUnclaimedStones();";}
	bool* getPlayableStones() { // utilise la carte sélectionnée pour regarder si la stone est okay
		Card* card = nullptr;
		// if (turn) {card = player1->getPick();} else {card = player2->getPick();}
		//board.getPlayableStones(card); // actualy getting a return value
		getUnclaimedStones();
		std::cout << "\ngetPlayableStones();";
		bool* pickable_stones = new bool[board.getStoneNb()];

		//FOR THE TESTS : 
		for (size_t i = 0; i < board.getStoneNb(); i++) {
			pickable_stones[i] = rand() % 2;
		}
		return pickable_stones;
	}

	void qtGameOver() {
		std::cout << "\n================================ qtGameOver";
	}
	void qtDisplayPlayerTurn() {
		std::cout << "\n================================ qtDisplayPlayerTurn";
		getCurrentPlayerHand();
		getPickableCards(); // TO DO : then updates accessible variables""
		// UserInterface::getInstance().UISelectCard(); <= JAMAIS ETRE LANCE
	}
	void qtDisplayStonePicker() { // contient la liste des Stones éligibles
		std::cout << "\n================================ qtDisplayStonePicker";
		std::cout << "\nenvoie à qt la liste des bornes sélectionnables pour ce joueur";
		std::cout << "\ndemande a QT d'afficher le menu pour selectionner des bornes";
	}
	void eventCardPicked(int n) {
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
		// const Card c = clanDeck->draw();
		// updating player's hand
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

	virtual const Card** getCurrentPlayerHand() {
		const Card* fakeHand[6];
		for (int i = 0; i < 6; i++) {
			fakeHand[i] = &clanDeck->draw();
		}
		return fakeHand;
	}

	virtual void playTurn(Side s);

protected:
	Controller(const Version& v, const string& name_player1, const string& name_player2, unsigned int AI_player1, unsigned int AI_player2, size_t handSize = 6)
		: version(v), clanGame(Game(v)), handSize(handSize) {
		if (v != Version::legacy) throw ShottenTottenException("Controller constructor : version isn't legacy");
		if (AI_player1 == 0) { //human player
			player1 = new Player(name_player1, Side::s1);
		}
		else if (AI_player1 == 1) { //IA random player
			player1 = new PlayerAIRandom(name_player1, Side::s1);
		}
		else { //incorrect number
			throw ShottenTottenException("Controller constructor : inadequate player (1) specifier");
		}
		if (AI_player2 == 0) { //human player
			player2 = new Player(name_player2, Side::s2);
		}
		else if (AI_player2 == 1) { //IA random player
			player2 = new PlayerAIRandom(name_player2, Side::s2);
		}
		else { //incorrect number
			throw ShottenTottenException("Controller constructor : inadequate player (2) specifier");
		}
	}

	virtual void initForNewRound();
	virtual ~Controller() {
		delete clanDeck;
	}
};

class TacticController : public Controller {
private :
	const Version version = Version::tactic;
	Deck* tacticDeck = nullptr;
	Game tacticGame;
	size_t handSize = 7;
	friend class Supervisor;
	void initForNewRound() final;
public :
	TacticController(const Version& v, const string& name_player1, const string& name_player2, unsigned int AI_player1, unsigned int AI_player2)
		: Controller(Version::legacy, name_player1, name_player2, AI_player1, AI_player2, handSize = 7), tacticGame(Game(v)) {
		tacticDeck = new Deck(tacticGame);
		if (v != Version::tactic) throw ShottenTottenException("Controller constructor : version isn't tactic");
	}
	~TacticController() {
		delete tacticDeck;
	}
	Deck& getTacticDeck() const { return *tacticDeck; }
	Game& getTacticGame() { return tacticGame; }

	void claimStone(Side s, unsigned int n) final;

};
