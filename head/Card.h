#pragma once
#include "../exception/ShottenTottenException.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;


enum class Color { red, green, blue, purple, yellow, brown };
enum class Number { one, two, three, four, five, six, seven, eight, nine };

string toString(const Color& color);
string toString(const Number& number);
int toInt(const Number& number);

ostream& operator<<(const ostream& os, const Color& color);
ostream& operator<<(const ostream& os, const Color& number);

extern std::initializer_list<Color> Colors;
extern std::initializer_list<Number> Numbers;

class Card {
private:
	const string name;
public:
	Card(const string n) : name(n){}
	const string& getName() const { return name; }

	virtual void activate() const=0;

	virtual const bool canBeUsedAs(const Color& c) const=0;
	virtual const bool canBeUsedAs(const Number& n) const=0;
	virtual const bool canBeUsedAs(const Color& c, const Number& n) const { return canBeUsedAs(c) && canBeUsedAs(n); };
	virtual const Number higherPossibleNumber() const=0;
	virtual const list<Number> possibleNumber() const = 0;

};

const size_t clanCardsNumber = 54;
const size_t tacticalCardsNumber = 10;

class Clan : public Card {
private:
	const Color color;
	const Number number;
public:
	Clan(const Color& c, const Number nb): Card(toString(c) + " " + toString(nb)), color(c), number(nb) { }
	void activate() const { return; };
	const Color& getColor() const { return color; }
	const Number& getNumber() const { return number; }

	virtual const bool canBeUsedAs(const Color& c) const {return c == color;}
	virtual const bool canBeUsedAs(const Number& n) const {return n == number;}
	virtual const Number higherPossibleNumber() const { return getNumber(); };
	virtual const list<Number> possibleNumber() const { list<Number> tmp = list<Number>(); tmp.push_front(number); return tmp; };
};

class Tactical : public Card {
public:
	Tactical(const string n) : Card(n){}
	void activate() const { return; };
	virtual const bool canBeUsedAs(const Color& c) const { throw ShottenTottenException("canBeUsedAs Error : This card doesnt have a Color value !"); }
	virtual const bool canBeUsedAs(const Number& n) const { throw ShottenTottenException("canBeUsedAs Error : This card doesnt have a Number value !"); }
	virtual const Number higherPossibleNumber() const { throw ShottenTottenException("higherPossibleNumber Error : This card doesnt have a Number value !"); };
	virtual const list<Number> possibleNumber() const { throw ShottenTottenException("possibleNumber Error : This card doesnt have a Number value !"); };
};

class Elite : public Tactical {
private:
	const list<Color> allowedColors;
	const list<Number> allowedNumbers;
public:
	Elite(const string n, list<Color> allowedColors, list<Number> allowedNumbers) : Tactical(n), allowedColors(allowedColors), allowedNumbers(allowedNumbers) {}
	virtual const bool canBeUsedAs(const Color& c) const {
		bool colorFinded = false;
		for (auto& color : allowedColors) {
			if (color == c) {
				colorFinded = true;
				break;
			}
		}
		return colorFinded;
	}
	virtual const bool canBeUsedAs(const Number& n) const {
		bool numberFinded = false;
		for (auto& number : allowedNumbers) {
			if (number == n) {
				numberFinded = true;
				break;
			}
		}
		return numberFinded;
	}
	virtual const Number higherPossibleNumber()const {
		Number highest = allowedNumbers.front();
		for (list<Number>::const_iterator i = allowedNumbers.begin(); i != allowedNumbers.end(); ++i) {
			if (toInt(*i) > toInt(highest)) {
				highest = *i;
			}
		}
		return highest;
	}
	virtual const list<Number> possibleNumber() const {
		return allowedNumbers;
	};
};

class CombatMode : public Tactical {
public:
	CombatMode(const string n) : Tactical(n) {}
};

class Ruses : public Tactical {
public:
	Ruses(const string n) : Tactical(n) {}
};

