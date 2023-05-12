#include <iostream>
#include "head/Game.h"
#include "head/Card.h"
#include "head/Board.h"

int main() {
	
	const Card** cards = new const Card * [10];

	cards[0] = new Clan(Color::blue, Number::two);
	cards[1] = new Clan(Color::purple, Number::nine);
	cards[2] = new Clan(Color::yellow, Number::nine);
	cards[3] = new Clan(Color::blue, Number::nine);
	//cards[1] = new Elite("Chief2", Colors, Numbers);


	const Card*  icomb[] { new Elite("Chief2", Colors, Numbers),new Clan(Color::blue, Number::two) };

	const Card** bestVar = Stone::bestVariation(cards, 2, icomb, 2, 3,CombinationType::three_of_a_kind,5);
	//cout << bestVar[1] << endl;

	cout << endl;
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