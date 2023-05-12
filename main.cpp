#include <iostream>
#include "head/Game.h"
#include "head/Card.h"
#include "head/Board.h"

int main() {
	
	const Card** cards = new const Card * [10];

	cards[0] = new Clan(Color::blue, Number::eight);
	cards[1] = new Clan(Color::purple, Number::seven);
	cards[2] = new Clan(Color::yellow, Number::nine);
	cards[3] = new Clan(Color::blue, Number::nine);
	//cards[1] = new Elite("Chief2", Colors, Numbers);


	const Card*  icomb[] { new Clan(Color::green, Number::nine) };

	const Card** bestVar = Stone::bestVariation(cards, 4, icomb, 1, 3,CombinationType::straight,9+5);
	//cout << bestVar[1] << endl;

	if (bestVar != nullptr) {
		for (int i = 0; i < 3; i++) {
			if (bestVar[i] != nullptr) {
				cout << bestVar[i]->getName() << endl;
			}
			else {
				cout << "nullptr" << endl;
			}

		}
	}
	else {
		cout << "nothing found !";
	}
	return 0;
	
}



// salut salut