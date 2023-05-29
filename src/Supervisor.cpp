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

void Supervisor::setController(const Version& v, const string& name_player1, const string& name_player2, unsigned int IA_player1, unsigned int IA_player2, UserInterface* ui) {
	if (controller == nullptr) {
		switch (v) {
		case Version::legacy :
			controller = new Controller(v, name_player1, name_player2, IA_player1, IA_player2,ui);
			break;
		case Version::tactic :
			controller = new TacticController(v, name_player1, name_player2, IA_player1, IA_player2,ui);
			break;
		default :
			throw ShottenTottenException("Incorrect game version");
		}
	}
}
