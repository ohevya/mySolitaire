#pragma once
#include "Card.h"

class Foundation
{
private:
	std::vector<Card> _foundation;
	
	sf::Vector2f _pos;
public:
	Foundation(sf::Vector2f pos);

	void addNewCard(Card newCard);
	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

	Card& getCard();
};
