#pragma once
#include <vector>
#include <deque>
#pragma once
#include <ranges>
#include <algorithm>
#include <random>

#include "card.h"

enum Difcllty {DRAW_ONE = 1, DRAW_THREE = 3};

class Deck
{
private:
	int _drawAmount;
	sf::Vector2f _stockPos = sf::Vector2f(50.f, 300.f);
	sf::Vector2f _wastePos = sf::Vector2f(250.f, 300.f);
	std::vector<Card*> _stock;
	std::vector<Card*> _waste;
	std::deque<sf::Texture> _textureList;

	Card* _empty;
	Card* _flipCards;



	void _generateCards();
	void shuffleDeck();
public:
	Deck(int drawAmount);
	~Deck();

	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

	void nextCard();
	void resetStock();

	void mouseRelesed(sf::Vector2f mousePos);
};