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