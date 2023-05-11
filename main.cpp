#include <iostream>
#include "head/Game.h"
#include "head/Card.h"
#include "head/Board.h"

int main() {
	const Card** cards = new const Card*[10];

	cards[0] = new Clan(Color::blue, Number::six);
	cards[1] = new Clan(Color::blue, Number::seven);
	cards[4] = new Elite("Chief2", Colors, Numbers);
	cards[2] = new Clan(Color::blue, Number::eight);
	cards[3] = new Clan(Color::blue, Number::nine);



	const Card*  icomb[] {new Clan(Color::blue,Number::one),new Clan(Color::blue,Number::two) };

	const Card** bestVar = Stone::bestVariation(cards, 5, icomb, 2, 4);


	if (bestVar != nullptr) {
		for (int i = 0; i < 4; i++) {
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

}



// salut salut