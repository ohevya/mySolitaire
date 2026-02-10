#include "Tableau.h"

void Tableau::update(const sf::RenderWindow& window)
{
	float x{500};
	float y{300};

	

	for ( auto& pile : this->_piles)
	{
		for (auto& card : pile)
		{
			card.update(window, sf::Vector2f( x, y ));
			y += 35;
		}
		y = 300;
		x += 150;
	}
}

void Tableau::render(sf::RenderTarget& target)
{
	for (auto& pile : this->_piles)
	{
		for (auto& card : pile)
		{
			card.render(target);
		}
	}
}

void Tableau::updateFromPos(int pileI, int startI)
{
	auto& pile = this->_piles[pileI];

	if (startI >= pile.size()) return;
	sf::Vector2f pos = pile[startI].getSprite().getPosition();
	
	for (int i {startI + 1}; i < pile.size(); i++)
	{
		pos.y += 35;
		pile[i].getSprite().setPosition(pos);
	}
}

std::vector<Card>& Tableau::operator[](int index)
{
	return this->_piles[index];
}

Tableau::Tableau()
{
	this->_piles.resize(7);
}
