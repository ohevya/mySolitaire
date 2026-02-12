#pragma once
#include "Card.h"
#include "OtherCards.h"

class Tableau
{
private:
	std::vector<std::vector<Card>> _piles;
	
public:
	void update();
	void render(sf::RenderTarget& target);

	void updateFromPos(int pileI, int startI);


	std::vector<Card>& operator[](int index);
	sf::FloatRect _pileRect[TableauSize] {};

	Tableau();
};

