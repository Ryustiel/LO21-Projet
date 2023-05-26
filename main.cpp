#include <iostream>
#include <string>
//#include "src/Controller.cpp"
//#include "src/Player.cpp"
#include "head/Game.h"
#include "head/Card.h"
#include "head/Board.h"
#include "head/UserInterface.h"

int main() {
	Supervisor::getInstance().setController(Version::legacy, "Ori", "Kyo", 0, 0);

	//check
	for (unsigned int i = 0; i < Supervisor::getInstance().getController()->getClanDeck().getCardCount(); i++) {
		cout << "Card " << i << " : "<< Supervisor::getInstance().getController()->getClanDeck().getCard(i)->getName() << endl;
	}

	Supervisor::getInstance().getController()->revendicateStone(Side::s1,0);

	//UserInterface::getInstance().launchUserInterface();


	return 0;
}