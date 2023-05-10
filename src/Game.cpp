#include "../head/Game.h"
#include "../exception/ShottenTottenException.h"


using namespace std;

Game::Game(const Version& version) {
	if (version == Version::legacy) {
  		unsigned int i = 0;
  		for (auto c : Colors) {
  			for (auto n : Numbers) {
  				cards[i] = new Clan(c, n);
  				i++;
  			}
  		}
	card_count = i;
	} else if (version == Version::expert) {
		cards[0] = new Elite("Chief1", Colors, Numbers);
		cards[1] = new Elite("Chief2", Colors, Numbers);
		cards[2] = new Elite("Spy",Colors, {Number::seven});
		cards[3] = new Elite("Shield-Bearer", Colors,{Number::one,Number::two,Number::three});
		cards[4] = new CombatMode("Blind-Man’s Bluff");
		cards[5] = new CombatMode("Mud Fight");
		cards[6] = new Ruses("Recruiter");
		cards[7] = new Ruses("Strategist");
		cards[8] = new Ruses("Banshee");
		cards[9] = new Ruses("Traiter");
		card_count =  10;
	} else {
		throw ShottenTottenException("Version Game error : version not known");
	}
}

Game::~Game() {
	for (unsigned int i = 0; i < card_count; i++) {
		delete cards[i];
	}
	delete[] cards;
}

const Card& Game::getCard(unsigned int i) const {
	if (i > card_count) throw ShottenTottenException("getCard error : incorrect number");
	return *cards[i];
}
