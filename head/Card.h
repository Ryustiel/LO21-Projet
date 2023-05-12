#pragma once
#include <string>
#include <iostream>

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
	string name;
public:
	Card(const string n) : name(n){}
	virtual void activate() const=0;
};

const size_t clanCardsNumber = 9 * 6;
const size_t tacticalCardsNumber = 10;

class Clan : public Card {
private:
	Color color;
	Number number;
public:
	Clan(const Color& c, const Number nb): Card(toString(c) + " " + toString(nb)), color(c), number(nb) {}
	void activate() const { return; };
	const Color& getColor() const { return color; }
	const Number& getNumber() const { return number; }
};

class Tactical : public Card {
public:
	Tactical(const string n) : Card(n){}
	void activate() const { return; };
};

class Elite : public Tactical {
public:
	Elite(const string n) : Tactical(n) {}
};

class CombatMode : public Tactical {
public:
	CombatMode(const string n) : Tactical(n) {}
};

class Ruses : public Tactical {
public:
	Ruses(const string n) : Tactical(n) {}
};

