#pragma once
#include "Card.h"
#include "..\exception\ShottenTottenException.h"

class DiscardException : public ShottenTottenException {
	using ShottenTottenException::ShottenTottenException;
};


class Discard{
private:
	const Card** cards;
	size_t size;
	size_t max_size;
public:
	Discard(): cards(nullptr),size(0),max_size(0) {}
	~Discard();
	void addCard(const Card& c);
	void withdrawCard(const Card& c);
	size_t getSize() const { return size; }
	size_t getMaxSize() const { return max_size; }
	const Card** getCards() const { return cards; }
	class DiscardIterator {
	private:
		friend Discard;
		const Card* begin;
		const Card* cur;
		size_t size;
		DiscardIterator(const Card* begin, size_t size): begin(begin),cur(begin),size(size) {}
	public:
		void next() {
			if (cur == begin + size) throw DiscardException("DiscardIterator next error : iterator ended !");
			cur++; 
		}
		bool isDone() { return cur == begin + size; }
		const Card& operator*() const { return *cur; }
	};
	DiscardIterator begin() { return DiscardIterator(cards[0], size); }
};