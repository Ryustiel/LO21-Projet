#pragma once
#include "../exception/ShottenTottenException.h"
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"
#include "Board.h"
#include "Hand.h"
#include "Player.h"
#include "Discard.h"
#include <iostream>
#include <string>



class UserInterface;


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
	Board* board;
	Game clanGame;
	Player* player1;
	Player* player2;
	size_t handSize;
	unsigned int playerCardPick;
	unsigned int playerStonePick;

	void newRound(); // événement de début de manche
	void checkRound(); // verifie si la manche est gagnée
	
	virtual void newTurn(); // lance un nouveau tour de joueur

public:
	Controller(const Controller& c) = delete;
	Controller& operator=(const Controller& c) = delete;

	// INTERNAL GETTERS

	Player* getCurrentPlayer() const {
		if (current_side == Side::s1) return player1;
		return player2;
	}
	Hand& getCurrentPlayerHand() const { return *getCurrentPlayer()->getHand(); }
	Side getCurSide() const { return current_side; }
	Version getVersion() const { return version; }
	Deck& getClanDeck() const { return *clanDeck; }
	Game getClanGame() const { return clanGame; } // accès en lecture seule
	Board& getBoard() { return *board; } //accès écriture
	Player& getPlayer1() const  { return *player1; }
	Player& getPlayer2() const  { return *player2; }
	int getRemainingRounds() const { return remainingRounds; }
	int getTotalRounds() const { return totalRounds; }
	Player* getWinner() const {
		if (player1->getScore() > player2->getScore()) return player1;
		if (player2->getScore() > player1->getScore()) return player2;
		return nullptr;
	}

	// INTERFACE RELATED GETTERS

	// getCurrentPlayerHandIterator() -> HandIterator

	// getBoardContent() -> BoardIterator

	bool canPlayCard() { // returns True if at least one card is playable
		size_t size;
		bool* playable = getPickableCards(&size);
		bool at_least_one = false;
		for (size_t i = 0; i < size; i++) {
			if (playable[i]) { 
				at_least_one = true;
				break;
			}
		}
		return at_least_one;
	}

	virtual bool* getPickableCards(size_t * size) const { // modifier ça pour avoir une size TO DO
		Hand& curHand = getCurrentPlayerHand();
		const size_t hs = curHand.getSize();
		bool* pickable = new bool[hs];
		for (size_t i = 0; i < hs; ++i) {
			pickable[i] = true;
		}
		*size = hs; // sauvegarde une valeur pour exporter 
		return pickable;
	} // récupère la liste des cartes jouables

	bool* getUnclaimedStones() const {
		const size_t sn = board->getStoneNb();
		bool* unclaimed = new bool[sn];
		for (size_t i = 0; i < sn; ++i) {
			unclaimed[i] = board->getStone(i).getRevendication() == Side::none;
		}
		return unclaimed;
	}

	bool* getPlayableStones() { // utilise la carte sélectionnée pour regarder si la stone est okay
		const size_t sn = board->getStoneNb();

		bool* playable = getUnclaimedStones();
		for (size_t i = 0; i < sn; ++i) {
			playable[i] = playable[i] && board->getStone(i).getSideSize(current_side) != board->getStone(i).getMaxSize();
		}
		return playable;
	}

	virtual unsigned int getDeckCount() const { return 1; }

	// SETTERS

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


	virtual bool getAvailableCards(const PlacableCard**& cards, size_t& foundedSize);
	void claimStone(unsigned int n);

	// initialise la partie, lancé via l'interface
	// tous les paramètres de partie présents sur l'interface doivent lui être passés
	// on pourrait aussi gérer certains paramètres via le Superviseur.
	void runGame(int nbturns, int winthreshold); // (int nbTurns, int typeia, ...)
	void turnPlayCard();
	virtual void turnDrawCard();
	void turnClaimStone();

	void qtGameOver() {
		std::cout << "\n================================ qtGameOver";
	}
	void eventCardPicked(int n) {
		std::cout << "\n================================ eventCardPicked";
		playerCardPick = 0; // enregistre le choix du joueur
		getUnclaimedStones(); // actually getting a return value => passed on to qtDisplayStonePicker()
	}
	void eventStonePicked() {
		std::cout << "\n================================ eventStonePicked";
		std::cout << "\nactive l'effet de la carte, les modifications sur l'etat du jeu";
		// vérifie si la carte requiert plus de bornes à sélectionner (effets actifs)
		// active l'effet de la carte et récupère un message
		// enregistre le tout dans 
	}
	void eventChoiceDraw() {
		std::cout << "\n================================ choiceDraw";
		// const Card c = clanDeck->draw();
		// updating player's hand
	}
	void eventChoiceEndTurn() {
		std::cout << "\n================================ choiceEndTurn";
		//eventStartTurn();
	}
	void eventChoiceClaim() {
		std::cout << "\n================================ choiceClaim";
		getUnclaimedStones();
	}

	virtual void playTurn(Side s);
	Stone& askStoneChoice() { return board->getStone(0); }

protected:
	Controller(const Version& v, const string& name_player1, const string& name_player2, unsigned int AI_player1, unsigned int AI_player2, size_t handSize = 6)
		: version(v), clanGame(Game(Version::legacy)), handSize(handSize) {
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
	virtual ~Controller() {
		delete clanDeck;
		delete player1;
		delete player2;
	}
	virtual void initForNewRound();
};

class TacticController : public Controller {
private :
	friend class Supervisor;
	const Version version = Version::tactic;
	Deck* tacticDeck = nullptr;
	Discard* discard = nullptr;
	Game tacticGame;
	size_t handSize = 7;
	unsigned int p1TacticalCardPlayed = 0;
	unsigned int p2TacticalCardPlayed = 0;
	void initForNewRound() final;
public :
	TacticController(const Version& v, const string& name_player1, const string& name_player2, unsigned int AI_player1, unsigned int AI_player2)
		: Controller(Version::tactic, name_player1, name_player2, AI_player1, AI_player2, handSize = 7), tacticGame(Game(Version::tactic)) {
		tacticDeck = new Deck(tacticGame);
		if (v != Version::tactic) throw ShottenTottenException("Controller constructor : version isn't tactic");
	}
	~TacticController() {
		delete tacticDeck;
	}

	unsigned int getDeckCount() const override { return 2; }
	Deck& getTacticDeck() const { return *tacticDeck; }
	Game& getTacticGame() { return tacticGame; }
	Discard& getDiscard() const { return *discard; }

	virtual bool* getPickableCards(size_t * size) final { // renvoie une liste de booléens qui indiquent les cartes jouables pour ce tour
		if (playerCanPlayTacticalCard()) {
			return Controller::getPickableCards(size); // seules les cartes tactiques comptent : le joueur peut jouer normalement son tour
		}
		else { // réimplémente la fonctionnalité de getPickableCards() en excluant les cartes tactiques
			Hand& curHand = getCurrentPlayerHand();
			const size_t hs = curHand.getSize();
			bool* pickable = new bool[hs];
			for (size_t i = 0; i < hs; ++i) {
				pickable[i] = !dynamic_cast<const Tactical*>(curHand.getCard(i));
			}

			*size = hs;

			return pickable;
		}
	}
	bool* getPlayableStonesCombatMode() {
		const size_t sn = getBoard().getStoneNb();
		bool* playable = getUnclaimedStones();
		for (size_t i = 0; i < sn; ++i) { //unclaimed + uncomplete + no combat mode card
			Stone& s = getBoard().getStone(i);
			playable[i] = playable[i] && s.getCombatMode() == nullptr;
		}
		return playable;
	}
	bool getAvailableCards(const PlacableCard**& cards, size_t& foundedSize) final;

	void incrementTacticalPlayed(Side s);
	bool playerCanPlayTacticalCard();
};
