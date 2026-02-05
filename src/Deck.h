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
	std::vector<Card> _stock;
	std::vector<Card> _waste;

	std::vector<Card> _tempCards;



public:

	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

	void nextCard();
	void resetStock();

	void addNewCard(Card newCard);
	void addNewCardToTemps(Card newCard);

	void shuffleDeck();

	//set
	void setDrawAmount(int drawAmount);

	//get
	std::vector<Card>& getStock();
	std::vector<Card>& getWaste();

	Card& getEmpty();
	Card& getFlipped();

	sf::Vector2f& getStockPos();
	sf::Vector2f& getWastePos();
		
};