#pragma once
#include "../exception/ShottenTottenException.h"
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"
#include "Board.h"
#include "Hand.h"


//using design pattern Singleton
class Controller{
private:
	static Controller* instance;
	Deck* clan_deck;
	Deck* tactical_deck;
	Board* board;
	Hand* hand_j1;
	Hand* hand_j2;
public:
	Deck& getClanDeck();
	Deck& getTacticalDeck();
	Board& getBoard();
	Hand& getHand1();
	Hand& getHand2();
	Controller() = default;
	~Controller() = default;
	struct Handler {
		Controller* instance = nullptr;
		~Handler() { delete instance; }
	};
	static Handler handler;
	Controller(const Controller& j) = delete;
	Controller& operator=(const Controller& j) = delete;
	static const Controller& getInstance();
	void freeInstance();
};

class TacticController : public Controller {
private :
	const Version version = Version::tactic;
	Deck* tacticDeck = nullptr;
	Game tacticGame;
	friend class Supervisor;
public :
	TacticController(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2)
		: Controller(Version::legacy, name_player1, name_player2, id_player1, id_player2), tacticGame(Game(v)), tacticDeck(new Deck(Game(v))) {
		if (v != Version::tactic) throw ShottenTottenException("Controller constructor : version isn't tactic");
	}
	Deck& getTacticDeck();
};
