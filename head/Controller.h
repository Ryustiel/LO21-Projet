#pragma once
#include "../exception/ShottenTottenException.h"
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Version.h"
#include "Board.h"
#include "Version.h"
#include "Player.h"

//using design pattern Singleton
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
public:
	Controller(const Controller& j) = delete;
	Controller& operator=(const Controller& j) = delete;
protected:
	Controller(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2)
		: version(v), clanGame(Game(v)), clanDeck(new Deck(Game(v))), board(Board()), player1(new Player(name_player1, id_player1)), player2(new Player(name_player2, id_player2)) {
		if (v != Version::legacy) throw ShottenTottenException("Controller constructor : version isn't legacy");
	}
	~Controller() {
		delete clanDeck;
		delete player1;
		delete player2;
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
public :
	TacticController(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2)
		: Controller(Version::legacy, name_player1, name_player2, id_player1, id_player2), tacticGame(Game(v)), tacticDeck(new Deck(Game(v))) {
		if (v != Version::tactic) throw ShottenTottenException("Controller constructor : version isn't tactic");
	}
	Deck& getTacticDeck();
};
