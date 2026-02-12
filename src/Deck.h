#pragma once
#include <ranges>
#include <algorithm>
#include <random>

#include "card.h"
#include "OtherCards.h"

enum Difcllty {DRAW_ONE = 1, DRAW_THREE = 3};

class Deck
{
private:
	int _drawAmount;
	std::vector<Card> _stock;
	std::vector<Card> _waste;

public:


	void update();
	void render(sf::RenderTarget& target);

	void nextCard();
	void resetStock();

	void addNewCard(Card newCard);

	void shuffleDeck();

	//set
	void setDrawAmount(int drawAmount);

	//get
	std::vector<Card>& getStock();
	std::vector<Card>& getWaste();

};