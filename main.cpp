#include <iostream>
#include <string>

//#include "src/Controller.cpp"
//#include "src/Player.cpp"
#include "head/Game.h"
#include "head/Card.h"
#include "head/Board.h"
#include "head/Controller.h"
#include "head/UserInterface.h"
#include "head/Utility.h"

int main() {

	/*
	Supervisor::getInstance().setController(Version::legacy, "Ori", "Kyo", 1, 1);
	cout << Supervisor::getInstance().getController()->getCurrentPlayerHand()->selectCard();
	*/

	UserInterfaceCmd::setInstance();

	UserInterface::getInstance()->quickLaunch(0,0,Version::tactic);

	/*bool blist[5] = {true, true, false, false, true};
	int result = Utility::randChoice(blist, 5);

	std::cout << result;*/


	/*
	Supervisor::getInstance().setController(Version::legacy, "Ori", "Kyo", 0, 0);

	//check
	for (unsigned int i = 0; i < Supervisor::getInstance().getController()->getClanDeck().getCardCount(); i++) {
		cout << "Card " << i << " : "<< Supervisor::getInstance().getController()->getClanDeck().getCard(i)->getName() << endl;
	}

	Supervisor::getInstance().getController()->claimStone(Side::s1,0);

	//UserInterfaceCmd::getInstance().launchUserInterfaceCmd();
	*/

	/*
	Board* b = new Board();

	b->getStone(0).setRevendication(Side::s1);
	b->getStone(1).setRevendication(Side::none);
	b->getStone(2).setRevendication(Side::s2);
	b->getStone(3).setRevendication(Side::s1);
	b->getStone(4).setRevendication(Side::s1);
	b->getStone(5).setRevendication(Side::none);
	b->getStone(6).setRevendication(Side::s2);
	b->getStone(7).setRevendication(Side::s2);
	b->getStone(8).setRevendication(Side::s2);

	b->evaluateGameWinner();

	Elite* e = new Elite("Chief2", Colors, Numbers);
	Clan* c1 = new Clan(Color::red, Number::nine);
	Clan* c2 = new Clan(Color::red, Number::eight);
	Clan* c3 = new Clan(Color::red, Number::seven);
	Clan* c4 = new Clan(Color::blue, Number::two);
	Clan* c5 = new Clan(Color::blue, Number::one);
	Clan* c6 = new Clan(Color::blue, Number::three);
	Clan* c7 = new Clan(Color::purple, Number::seven);
	Clan* c8 = new Clan(Color::yellow, Number::seven);
	*/

	/*
	Board* b = new Board();
	b->addCard(*c3, Side::s1, 0);
	b->addCard(*c7, Side::s1, 0);
	b->addCard(*c8, Side::s1, 0);
	b->addCard(*c1, Side::s2, 0);
	//b->addCard(*c5, Side::s2, 0);
	//b->addCard(*e, Side::s2, 0);

	std::cout << "\n\ndone";

	if (b->getStone(0).getFirstCompleted() != Side::s1) cout << "Incorrect first completed side" << endl;

	const Card** cards = new const Card * [10];
	cards = new const Card * [10];

	cards[0] = new Clan(Color::blue, Number::one);
	cards[1] = new Clan(Color::purple, Number::one);
	cards[2] = new Clan(Color::yellow, Number::nine);
	cards[3] = new Clan(Color::blue, Number::nine);
	//cards[1] = new Elite("Chief2", Colors, Numbers);

	Side s = b->evaluateStoneWinningSide(0, cards, 4);

	cout << "(main.cpp) : evaluateStoneWinningSide returns : ";
	if (s == Side::s1) cout << "s1";
	else if (s == Side::s2) cout << "s2";
	else cout << "none";
	cout << endl;
	*/


	// SCRIPT DE JEU
	// pour comprendre l'enchainement des evenements
	// et faire des tests !

	//Supervisor::getInstance();
	//Supervisor::getInstance().eventFirstStart(); // => qtDisplayMainMenu()

	// => réponse qui suit le message qtDisplayMainMenu()
	// => elle contient les paramètres de la partie et la version choisie.
	//Supervisor::getInstance().eventStartGame(Version::legacy, "player name 1", "player name 2", 3, 2);

	// ctr->eventChoiceDraw(); // <= interface : menu Jouer son Tour
	// => ctr.qtDisplayPlayerTurn()
	// ctr->eventCardPicked("Carte carte_choisie"); // interface : menu Card Picker
	// => ctr.qtDisplayStonePicker();
	// carteSelectionnee.activate();
	// ctr->qtDisplayPlayerTurn(); // interface : menu Stone Picker
	// ctr->eventChoiceEndTurn(); // interface : menu Jouer son Tour
	// => ctr.startTurn() => ctr.checkRound(); => ctr.qtDisplayVictoryMenu();
	// ctr->qtDisplayVersionMenu();

	return 0;
}
