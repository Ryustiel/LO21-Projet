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
	Player* player1;
	Player* player2;
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
	static Controller& getInstance() { return *instance; }

	// setting players AI
	// la manière de générer les instances des classes IA
	// peut être très différente, il faudra qu'on en discute
	void setPlayer1(Player* player) { player1 = player; }
    void setPlayer2(Player* player) { player2 = player; }

	// initialise la partie, lancé via l'interface
	// tous les paramètres de partie présents sur l'interface doivent lui être passés
	// on pourrait aussi gérer certains paramètres via le Superviseur.
	void newGame(int nbTurns); // (int nbTurns, int typeia, ...)


	//Demande à l'utilisateur une Stone sur laquelle placer une carte clan A CHANGER !!!!!!
	Stone& askStoneChoice() const {
		// a changer 
		return board.getStone(0);
	}
	// A CHANGER !!!!!!
	Side getSide() const { return Side::s1; }
protected:
	static Controller* instance;
	Controller(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2)
		: version(v), clanGame(Game(v)), clanDeck(new Deck(Game(v))), board(Board()), player1(new Player(name_player1, id_player1)), player2(new Player(name_player2, id_player2)) {
		if (v != Version::legacy) throw ShottenTottenException("Controller constructor : version isn't legacy"); if (instance != nullptr) delete instance; instance = this;
	}
	~Controller() {
		delete clanDeck;
		delete player1;
		delete player2;
		instance = nullptr;
	}
	Deck& getClanDeck();
  	Board& getBoard();
};

class TacticController : public Controller {
private :
	const Version version = Version::tactic;
	Deck* tacticDeck = nullptr;
	Game tacticGame;
	friend class Supervisor;
	static TacticController* tacticInstance;
public :
	TacticController(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2)
		: Controller(Version::legacy, name_player1, name_player2, id_player1, id_player2), tacticGame(Game(v)), tacticDeck(new Deck(Game(v))) {
		if (v != Version::tactic) throw ShottenTottenException("Controller constructor : version isn't tactic"); if (tacticInstance != nullptr) delete tacticInstance; tacticInstance = this;
	}
	~TacticController() {
		delete tacticDeck;
		tacticInstance = nullptr;
	}
	Deck& getTacticDeck();
	TacticController& getInstance() { return *tacticInstance; }
};
