#include <iostream>
#include "head/Game.h"
#include "head/Card.h"
#include "head/Board.h"

int main() {
	const Card** cards = new const Card*[10];

	cards[0] = new Clan(Color::blue, Number::nine);
	cards[1] = new Clan(Color::blue, Number::seven);
	cards[2] = new Clan(Color::blue, Number::eight);


	const Card*  icomb[] {new Clan(Color::blue,Number::one),new Clan(Color::blue,Number::two) };

	const Card** bestVar = Stone::bestVariation(cards, 3, icomb, 2, 4);


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