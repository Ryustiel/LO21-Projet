#include "../head/Card.h"
#include "../exception/ShottenTottenException.h"
#include "../head/Controller.h"
#include "../head/Supervisor.h"
#include "../head/UserInterface.h"

string toString(const Color& color) {
	switch (color)
	{
	case Color::red: return "red";
	case Color::blue: return "blue";
	case Color::green: return "green";
	case Color::brown: return "brown";
	case Color::purple: return "purple";
	case Color::yellow: return "yellow";
	default: throw ShottenTottenException("Color toString cast error : color unknown.");
	}
}

string toString(const Number& number) {
	switch (number)
	{
	case Number::one: return "1";
	case Number::two: return "2";
	case Number::three: return "3";
	case Number::four: return "4";
	case Number::five: return "5";
	case Number::six: return "6";
	case Number::seven: return "7";
	case Number::eight: return "8";
	case Number::nine: return "9";
	default: throw ShottenTottenException("Number toString cast error : number unknown.");
	}
};

int toInt(const Number& number) {
	switch (number)
	{
	case Number::one: return 1;
	case Number::two: return 2;
	case Number::three: return 3;
	case Number::four: return 4;
	case Number::five: return 5;
	case Number::six: return 6;
	case Number::seven: return 7;
	case Number::eight: return 8;
	case Number::nine: return 9;
	default: throw ShottenTottenException("Number toInt cast error : number unknown.");
	}
};

ostream& operator<<(ostream& os, const Color& color) { return os << toString(color); }
ostream& operator<<(ostream& os, const Number& number) { return os << toString(number); }

std::initializer_list<Color> Colors = { Color::red, Color::green, Color::blue, Color::brown, Color::purple, Color::yellow };
std::initializer_list<Number> Numbers = { Number::one, Number::two, Number::three, Number::four, Number::five, Number::six, Number::seven, Number::eight, Number::nine };


void PlacableCard::activate() const{
	Controller* c = Supervisor::getInstance().getController();
	int stoneNum = c->selectPlayableStone();
	if (stoneNum < 0) return;
	Stone& s = c->getBoard().getStone(stoneNum);
	s.addCard(*this,c->getCurSide());
};

void Tactical::activate() const {
	TacticController* c = dynamic_cast <TacticController*>(Supervisor::getInstance().getController());
	if (c != nullptr) {
		c->incrementTacticalPlayed(c->getCurSide());
	}
	else {
		throw ShottenTottenException("Tactical::activate error: no tactic controller !");
	}

};

void Chief::activate() const {
	Elite::activate();
	TacticController* c = dynamic_cast <TacticController*>(Supervisor::getInstance().getController());
	if (c != nullptr) {
		c->incrementChiefCardPlayed(c->getCurSide());
	}
	else {
		throw ShottenTottenException("Tactical::activate error: no tactic controller !");
	}
}

void Elite::activate() const {
	Tactical::activate();
	PlacableCard::activate();
}

void CombatMode::activate() const {
	Tactical::activate();
	TacticController* c = dynamic_cast <TacticController*>(Supervisor::getInstance().getController());
	int stoneNb = c->selectStoneForCombatMode();
	Stone& s = c->getBoard().getStone(stoneNb);
	s.setCombatMode(this);
}


void Ruses::activate() const {
	Tactical::activate();
	Controller* c = Supervisor::getInstance().getController();
	const TacticController* tc = dynamic_cast<const TacticController*>(c);
	if (tc == nullptr) {
		throw ShottenTottenException("Tactical::activate error: no tactic controller !");
	}
	else {
		tc->getDiscard().addCard(*this);
	}
}

void Banshee::activate() const {
	Ruses::activate();
	Controller* c = Supervisor::getInstance().getController();
	const TacticController* tc = dynamic_cast<const TacticController*>(c);
	if (tc == nullptr) {
		throw ShottenTottenException("Banshee::activate error: no tactic controller !");
	}
	else {
		Side opponent_side = c->getCurSide() == Side::s2 ? Side::s1 : Side::s2;
		
		int cardNb;
		int stoneNb;
		c->selectStoneAndCard(opponent_side, cardNb, stoneNb);
		if (cardNb < 0 || stoneNb < 0) {
			cout << "This Card can't be used yet !" << endl;
			return;
		}
		Stone& s = c->getBoard().getStone(stoneNb);


		const PlacableCard& selected_card = *s.getCard(opponent_side, cardNb);
		s.removeCard(selected_card, opponent_side);
		tc->getDiscard().addCard(selected_card);
	}
}

void Strategist::activate() const {
	Ruses::activate();
	Controller* c = Supervisor::getInstance().getController();
	const TacticController* tc = dynamic_cast<const TacticController*>(c);
	if (tc == nullptr) throw ShottenTottenException("Strategist::activate error: no tactic controller !");

	//select stone then card to move
	int cardNb;
	int stoneNb;
	c->selectStoneAndCard(c->getCurSide(), cardNb, stoneNb);
	if (cardNb < 0 || stoneNb < 0) {
		cout << "This Card can't be used yet !" << endl;
		return;
	}
	Stone& s = c->getBoard().getStone(stoneNb);

	//removing selected card from its stone
	const PlacableCard& selected_card = *s.getCard(c->getCurSide(),cardNb);
	s.removeCard(selected_card, c->getCurSide());

	bool choice = UserInterface::getInstance()->uiSelectPlayOrDiscard();
	if (choice) {
		//putting it on the right stone -> playable card activation
		selected_card.PlacableCard::activate();
	}
	else {
		//putting card in discard
		tc->getDiscard().addCard(selected_card);
	}
}

void Traiter::activate() const {
	Ruses::activate();
	Controller* c = Supervisor::getInstance().getController();
	const TacticController* tc = dynamic_cast<const TacticController*>(c);
	if (tc == nullptr) {
		throw ShottenTottenException("Traiter::activate error: no tactic controller !");
	}
	Side opponent_side = c->getCurSide() == Side::s2 ? Side::s1 : Side::s2;

	int cardNb;
	int stoneNb;
	c->selectStoneAndCard(opponent_side, cardNb, stoneNb);
	if (cardNb < 0 || stoneNb < 0) {
		cout << "This Card can't be used yet !" << endl;
		return;
	}
		
	Stone& s = c->getBoard().getStone(stoneNb);


	const PlacableCard& selected_card = *s.getCard(opponent_side,cardNb);
	s.removeCard(selected_card, opponent_side);
	selected_card.PlacableCard::activate();
}

void Recruiter::activate() const {
	Ruses::activate();
	TacticController* c = dynamic_cast<TacticController*>(Supervisor::getInstance().getController());
	if (!c) { throw ShottenTottenException("Recruiter::activate error: no tactic controller !"); }
	for (unsigned int i = 0; i < 2; ++i) {
		cout << "Choose a card to discard !" << endl;
		int cardNb = c->selectHandCard(false);
		if (cardNb < 0) return;
		const Card* selectedCard = c->getCurrentPlayerHand().getCard(cardNb);
		c->getCurrentPlayerHand().withdraw(*selectedCard);
		Deck* d;
		if (dynamic_cast<const Tactical*>(selectedCard)) {
			d = &c->getTacticDeck();
		}
		else {
			d = &c->getClanDeck();
		}
		d->addCard(*selectedCard);
	}

	for (unsigned int i = 0; i < 3; ++i) {
		cout << "Choose a Deck to draw !" << endl;
		Deck* d = c->selectDeck();
		if (!d) {
			cout << "All decks are empty :( !" << endl;
			break;
		}
		c->getCurrentPlayerHand().add(d->draw());
	}
}