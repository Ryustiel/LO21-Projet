#pragma once
#include "../exception/ShottenTottenException.h"
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"
#include "Board.h"
#include "Hand.h"
#include "Player.h"



class Controller{
private:
	const Version version = Version::legacy;
	Deck* clanDeck = nullptr;
	Board board;
	Game clanGame;
	Player* player1 = nullptr;
	Player* player2 = nullptr;
	bool round = 0;
	friend class Supervisor;

	// permet un arrêt prématuré de la partie,
	// en réponse à des événements spécifiques comme "quitter"
	// j'utilise une variable plutôt qu'un listener à cause
	// des boucles de jeu "while" dont on doit sortir de manière asynchrone
	// asynchrone à cause de l'interface Qt
	bool stop = false;

	// scores de manche stockés ici car impactent directement
	// la fin de boucle de manche et de partie
	int remainingRounds;
    int totalRounds;

	// VARIABLE TEMPORAIRE pour faire gagner chaque manche
	// automatiquement après 3 tours
	int TEMP_victory_counter;

	void handleNewRound(); // événement de début de manche
	// la méthode de boucle est séparée pour un code plus propre
	// et éventuellement des événements d'initialisation différents, 
	// pour différents modes de jeu
    void runRoundLoop(); // boucle de manche, lancé par handleNewRound
    void runChecks(); // running card checks on the board

public:
	Controller(const Controller& c) = delete;
	Controller& operator=(const Controller& c) = delete;

	//GETTERS
	Version getVersion() const { return version; }
	Deck& getClanDeck() const { return *clanDeck; }
	Game getClanGame() { return clanGame; }
	Board& getBoard() { return board; }
	Player& getPlayer1() const  { return *player1; }
	Player& getPlayer2() const  { return *player2; }
	bool getRound() const { return round; }
	bool getStop() const  { return stop; }
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

	void newRoundInit();

protected:
	Controller(const Version& v, const string& name_player1, const string& name_player2, unsigned int isIA1, unsigned int isIA2)
		: version(v), clanGame(Game(v)) {
		if (v != Version::legacy) throw ShottenTottenException("Controller constructor : version isn't legacy");
		clanDeck = new Deck(clanGame);
		if (isIA1 == 0) { //human player
			player1 = new Player(name_player1);
		} else if (isIA1 == 1) { //IA random player
			player1 = new PlayerAIRandom(name_player1);
		}
		else { //incorrect number
			throw ShottenTottenException("Controller constructor : inadequate player (1) specifier");
		}
		if (isIA2 == 0) { //human player
			player2 = new Player(name_player2);
		}
		else if (isIA2 == 1) { //IA random player
			player2 = new PlayerAIRandom(name_player2);
		}
		else { //incorrect number
			throw ShottenTottenException("Controller constructor : inadequate player (2) specifier");
		}
	}
	~Controller() {
		delete clanDeck;
		delete player1;
		delete player2;
	}
};

class TacticController : public Controller {
private :
	const Version version = Version::tactic;
	Deck* tacticDeck = nullptr;
	Game tacticGame;
	friend class Supervisor;
public :
	TacticController(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2)
		: Controller(Version::legacy, name_player1, name_player2, id_player1, id_player2), tacticGame(Game(v)) {
		tacticDeck = new Deck(tacticGame);
		if (v != Version::tactic) throw ShottenTottenException("Controller constructor : version isn't tactic");
	}
	~TacticController() {
		delete tacticDeck;
	}
	Deck& getTacticDeck() const { return *tacticDeck; }
	Game& getTacticGame() { return tacticGame; }
};
