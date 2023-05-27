#include <iostream>
#include <string>
//#include "src/Controller.cpp"
//#include "src/Player.cpp"
#include "head/Game.h"
#include "head/Supervisor.h"

#include "head/Card.h"
#include "head/Board.h"

int main() {
	Game* g = new Game(Version::legacy);
	Board* b = new Board();

	/*b->getStone(0).setRevendication(Side::s1);
	b->getStone(1).setRevendication(Side::none);
	b->getStone(2).setRevendication(Side::s2);
	b->getStone(3).setRevendication(Side::s1);
	b->getStone(4).setRevendication(Side::s1);
	b->getStone(5).setRevendication(Side::none);
	b->getStone(6).setRevendication(Side::s2);
	b->getStone(7).setRevendication(Side::s2);
	b->getStone(8).setRevendication(Side::s2);







	b->evaluateGameWinner();*/

	Supervisor& s = Supervisor::getInstance();
	s.setController(Version::tactic, "lol", "lol2", 0, 1);
	g->getCard(0).activate();

	return 0;
	/*Elite* e = new Elite("Chief2", Colors, Numbers);
	Clan* c1 = new Clan(Color::red, Number::nine);
	Clan* c2 = new Clan(Color::red, Number::eight);
	Clan* c3 = new Clan(Color::red, Number::seven);
	Clan* c4 = new Clan(Color::blue, Number::two);
	Clan* c5 = new Clan(Color::blue, Number::one);
	Clan* c6 = new Clan(Color::blue, Number::three);
	Clan* c7 = new Clan(Color::purple, Number::seven);
	Clan* c8 = new Clan(Color::yellow, Number::seven);

	Board* b = new Board();
	b->addCard(*c3, Side::s1, 0);
	b->addCard(*c7, Side::s1, 0);
	b->addCard(*c8, Side::s1, 0);
	b->addCard(*c1, Side::s2, 0);
	//b->addCard(*c5, Side::s2, 0);
	//b->addCard(*e, Side::s2, 0);

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
	
}