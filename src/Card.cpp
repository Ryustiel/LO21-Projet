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
	int stoneNum = UserInterface::getInstance()->uiSelectStone();
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

void Elite::activate() const {
	Tactical::activate();
	PlacableCard::activate();
}

void CombatMode::activate() const {
	Tactical::activate();
	TacticController* c = dynamic_cast <TacticController*>(Supervisor::getInstance().getController());
	int stoneNb = UserInterfaceCmd::getInstance()->uiSelectStoneCombatMode();
	Stone& s = c->getBoard().getStone(stoneNb);
	s.setCombatMode(this);
}


void Ruses::activate() const {
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
	Controller* c = Supervisor::getInstance().getController();
	const TacticController* tc = dynamic_cast<const TacticController*>(c);
	if (tc == nullptr) {
		throw ShottenTottenException("Tactical::activate error: no tactic controller !");
	}
	else {
		int cardNb = -1;
		int stoneNb = UserInterfaceCmd::getInstance()->uiSelectUnclaimedStone();
		Stone& s = c->getBoard().getStone(stoneNb);
		Side oppenent_side = Side::s1;
		if (c->getCurSide() == Side::s1) oppenent_side = Side::s2;
		cardNb = UserInterfaceCmd::getInstance()->uiSelectCardOnStone(oppenent_side, stoneNb);
		cout << "(Banshee::activate) - cardNb = " << cardNb << endl;

		while (cardNb == -1) {
			UserInterface::getInstance()->uiInvalidChoiceMsg();
			int stoneNb = UserInterface::getInstance()->uiSelectUnclaimedStone();
			Stone& s = c->getBoard().getStone(stoneNb);
			Side oppenent_side = Side::s1;
			if (c->getCurSide() == Side::s1) oppenent_side = Side::s2;
			cardNb = UserInterface::getInstance()->uiSelectCardOnStone(oppenent_side, stoneNb);
		}

		const PlacableCard& selected_card = *s.getCombinationSide(oppenent_side)[cardNb];
		s.removeCard(selected_card, oppenent_side);
		tc->getDiscard().addCard(selected_card);
		tc->getDiscard().addCard(*this);
	}
}