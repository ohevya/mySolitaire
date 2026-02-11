#include "Tableau.h"

void Tableau::update(const sf::RenderWindow& window)
{
	float x{500};
	float y{300};

	

	for ( auto& pile : this->_piles)
	{
		if (pile.empty())
		{ }
		else
		{
			for (auto& card : pile)
			{
				card.update(window, sf::Vector2f(x, y));
				y += 35;
			}

			if (!pile.back().isFaceUp())
				pile.back().flipCard();
			y = 300;
		}
		x += 150;
	}
}

void Tableau::render(sf::RenderTarget& target)
{
	float x{ 500 };
	float y{ 300 };

	for (auto& pile : this->_piles)
	{
		if (pile.empty())
		{
			OtherCards::getEmpty().setCardPos(sf::Vector2f(x, y));
			OtherCards::getEmpty().render(target);
		}
		else
			for (auto& card : pile)
			{
				card.render(target);
			}
		x += 150;
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

	float x{ 500 };
	float y{ 300 };

	for (int i{}; i < 7; i++)
	{
		this->_pileRect[i] = { {x, y}, {125.f, 181.5f}};
		y = 300;
		x += 150;
	}

}
