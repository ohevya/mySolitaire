#pragma once
#include <vector>
#include <ranges>

#pragma once
#include <algorithm>
#include <random>

#include "card.h"

enum Difcllty {DRAW_ONE = 1, DRAW_THREE = 3};

class Deck
{
private:
	int _drawAmount;
	sf::Vector2f _stockPos = sf::Vector2f(300.f, 300.f);
	sf::Vector2f _wastePos = sf::Vector2f(500.f, 500.f);
	std::vector<Card*> _stock;
	std::vector<Card*> _waste;



	void _generateCards();
	void shuffleDeck();
public:
	Deck(int drawAmount);
	~Deck();

	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

	void nextCard();
	void resetStock();

};