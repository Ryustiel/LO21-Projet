#include "..\head\Supervisor.h"
#include "..\exception\ShottenTottenException.h"

Supervisor::Handler Supervisor::handler = Supervisor::Handler();

Supervisor& Supervisor::getInstance() {
	if (handler.instance == nullptr) handler.instance = new Supervisor();
	return *handler.instance;
}

void Supervisor::freeInstance() {
	delete handler.instance;
	handler.instance = nullptr;
}

void Supervisor::setController(const Version& v, const string& name_player1, const string& name_player2, unsigned int id_player1, unsigned int id_player2) {
	if (controller = nullptr) {
		switch (v) {
		case Version::legacy :
			controller = new Controller(v, name_player1, name_player2, id_player1, id_player2);
			break;
		case Version::tactic :
			controller = new TacticController(v, name_player1, name_player2, id_player1, id_player2);
			break;
		default :
			throw ShottenTottenException("Incorrect game version");
		}
	}
}
