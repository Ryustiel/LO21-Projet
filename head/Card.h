#pragma once
#include "../exception/ShottenTottenException.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;


enum class Color { red, green, blue, purple, yellow, brown };
enum class Number { one, two, three, four, five, six, seven, eight, nine };

class Controller;

string toString(const Color& color);
string toString(const Number& number);
int toInt(const Number& number);

ostream& operator<<(const ostream& os, const Color& color);
ostream& operator<<(const ostream& os, const Color& number);

extern std::initializer_list<Color> Colors;
extern std::initializer_list<Number> Numbers;

const size_t clanCardsNumber = 54;
const size_t tacticalCardsNumber = 10;

class Card {
protected:
	const string name;
protected:
	Card(const string n) : name(n){}
public:
	virtual ~Card() = default;
	const string& getName() const { return name; }
	virtual void activate() const=0;
	
	// playability methods
	/*
	virtual bool isPlayable(Board& b) { return true; }; // checks if the card is playable on at least one stone
	virtual bool* getPlayableStones(BoardSideIterator it) { // returns the playable stones for that card
		bool TEMP[2] = { true, true };
		return TEMP;
	};
	*/
};

class PlacableCard : public virtual Card {
public:
	PlacableCard(const string n):Card(n){}
	virtual ~PlacableCard() = default;
	virtual bool canBeUsedAs(const Color& c) const = 0;
	virtual bool canBeUsedAs(const Number& n) const = 0;
	virtual Number higherPossibleNumber()const = 0;
	virtual const list<Number> possibleNumber() const = 0;
	bool canBeUsedAs(const Color& c, const Number& n) const { return canBeUsedAs(c) && canBeUsedAs(n); };
	void activate() const override;
};

class Tactical :public virtual Card {
public:
	Tactical(const string n) : Card(n){}
	virtual ~Tactical() = default;
	void activate() const override;
};

class Clan : public PlacableCard {
private:
	const Color color;
	const Number number;
public:
	Clan(const Color& c, const Number nb) : PlacableCard(""), color(c), number(nb), Card(toString(c) + " " + toString(nb)) {}
	~Clan() final = default;
	const Color& getColor() const { return color; }
	const Number& getNumber() const { return number; }

	bool canBeUsedAs(const Color& c) const final { return c == color; }
	bool canBeUsedAs(const Number& n) const final { return n == number; }
	Number higherPossibleNumber() const final { return getNumber(); };
	const list<Number> possibleNumber() const final { list<Number> tmp = list<Number>(); tmp.push_front(number); return tmp; };
};

class Elite : public Tactical, public PlacableCard {
private:
	const list<Color> allowedColors;
	const list<Number> allowedNumbers;
public:
	Elite(const string n, list<Color> allowedColors, list<Number> allowedNumbers) : Tactical(n), PlacableCard(n), allowedColors(allowedColors), allowedNumbers(allowedNumbers), Card(n) {}
	void activate() const final;
	const string& getName() const { return Tactical::name; }
	bool canBeUsedAs(const Color& c) const {
		bool colorFinded = false;
		for (auto& color : allowedColors) {
			if (color == c) {
				colorFinded = true;
				break;
			}
		}
		return colorFinded;
	}
	bool canBeUsedAs(const Number& n) const {
		bool numberFinded = false;
		for (auto& number : allowedNumbers) {
			if (number == n) {
				numberFinded = true;
				break;
			}
		}
		return numberFinded;
	}
	Number higherPossibleNumber()const {
		Number highest = allowedNumbers.front();
		for (list<Number>::const_iterator i = allowedNumbers.begin(); i != allowedNumbers.end(); ++i) {
			if (toInt(*i) > toInt(highest)) {
				highest = *i;
			}
		}
		return highest;
	}
	const list<Number> possibleNumber() const {
		return allowedNumbers;
	};
};

class CombatMode : public Tactical {
public:
	CombatMode(const string n) : Tactical(n), Card(n) {}
	~CombatMode() = default;
	void activate() const override;
};

class BlindManBluff : public CombatMode {
public:
	BlindManBluff(const string n) : CombatMode(n), Card(n) {}
	~BlindManBluff() final = default;
	void activate() const final { CombatMode::activate(); }
};

class Ruses : public Tactical {
public:
	Ruses(const string n) : Tactical(n), Card(n) {}
	~Ruses() = default;
	void activate() const override;
};

class Banshee : public Ruses {
public :
	Banshee(const string n) : Ruses(n), Card(n) {}
	~Banshee() final = default;
	void activate() const final;
};

class Strategist : public Ruses {
public:
	Strategist(const string n) : Ruses(n), Card(n) {}
	~Strategist() final = default;
	void activate() const final;
};

class Traiter : public Ruses {
public:
	Traiter(const string n) : Ruses(n), Card(n) {}
	~Traiter() final = default;
	void activate() const final;
};

class Recruiter : public Ruses {
public:
	Recruiter(const string n) : Ruses(n), Card(n) {}
	~Recruiter() final = default;
	void activate() const final;
};