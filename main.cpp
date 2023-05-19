#include <iostream>
#include <string>
//#include "src/Controller.cpp"
#include "src/Player.cpp"
#include "head/Game.h"

#include "head/Card.h"
#include "head/Board.h"
#include "head/Supervisor.h"
#include "head/Controller.h"

int main() {
	Elite* e = new Elite("Chief2", Colors, Numbers);
	Clan* c1 = new Clan(Color::red, Number::nine);
	Clan* c2 = new Clan(Color::red, Number::eight);
	Clan* c3 = new Clan(Color::red, Number::seven);
	Clan* c4 = new Clan(Color::blue, Number::two);
	Clan* c5 = new Clan(Color::blue, Number::one);
	Clan* c6 = new Clan(Color::blue, Number::three);

	Board* b = new Board();
	b->addCard(*c3, Side::s1, 0);
	b->addCard(*c5, Side::s1, 0);
	b->addCard(*c6, Side::s1, 0);
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


	// SCRIPT DE JEU
	// pour comprendre l'enchainement des evenements

	Supervisor::getInstance();
	Supervisor::getInstance().qtStart(); // => qtDisplayMainMenu()
	Supervisor::getInstance().runVersion("Version version_name"); // <= interface : menu Choix de Version
	// => sup.setController(version_name) => sup.getController().qtDisplayVersionMenu()
	Supervisor::getInstance().setController(Version::legacy, "p1", "p2", 1, 2);
	Controller* ctr = Supervisor::getInstance().getController();
	ctr->eventNewGame(2); // <= interface : menu Paramétrage de la Partie
	// => ctr.newRound() => ctr.startTurn() => ctr.qtDisplayPlayerTurn()
	ctr->eventChoiceDraw(); // <= interface : menu Jouer son Tour
	// => ctr.qtDisplayPlayerTurn()
	ctr->eventChoicePlay(); // <= interface : menu Jouer son Tour
	// => ctr.qtDisplayCardPicker();
	ctr->eventCardPicked("Carte carte_choisie"); // interface : menu Card Picker
	// => ctr.qtDisplayStonePicker();
	// carteSelectionnee.activate(); 
	ctr->qtDisplayPlayerTurn(); // interface : menu Stone Picker
	ctr->eventChoiceEndTurn(); // interface : menu Jouer son Tour
	// => ctr.startTurn() => ctr.checkRound(); => ctr.qtDisplayVictoryMenu();
	ctr->qtDisplayVersionMenu();



	return 0;
	
}