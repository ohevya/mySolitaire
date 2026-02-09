#include "Tableau.h"

void Tableau::update(const sf::RenderWindow& window)
{
	float x{500};
	float y{300};

	

	for ( auto& pile : this->_piles)
	{
		y = 300;
		for (auto& card : pile)
		{
			sf::Vector2f pos = sf::Vector2f(x, y);
			card.update(window, pos);
			y += 35;
		}
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

std::vector<Card>& Tableau::operator[](int index)
{
	return this->_piles[index];
}

Tableau::Tableau()
{
	this->_piles.resize(7);
}
