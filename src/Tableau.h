#pragma once
#include "Card.h"
#include "OtherCards.h"

class Tableau
{
private:
	std::vector<std::vector<Card>> _piles;
	
public:
	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

	void updateFromPos(int pileI, int startI);


	std::vector<Card>& operator[](int index);
	sf::FloatRect _pileRect[7]{};

	Tableau();
};

