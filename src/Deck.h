#pragma once
#include <vector>

#pragma once
#include <algorithm>
#include <random>

#include "card.h"

enum Difcllty {DRAW_ONE = 1, DRAW_THREE = 3};

class Deck
{
private:
	int _difcllty;
	std::vector<Card*> _stock;
	std::vector<Card*> _waste;

	void _generateCards();
	void shuffleDeck();
public:
	Deck(int& difcllty);

};