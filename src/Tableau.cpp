#include "Tableau.h"

void Tableau::update()
{
	float x = TableauX;
	float y = TableauHeight;

	

	for ( auto& pile : this->_piles)
	{
		if (pile.empty())
		{ }
		else
		{
			for (auto& card : pile)
			{
				card.update( sf::Vector2f(x, y));
				y += CardHeightOffset;
			}

			if (!pile.back().isFaceUp())
				pile.back().flipCard();
			y = TableauHeight;
		}
		x += CardXoffset;
	}
}

void Tableau::render(sf::RenderTarget& target)
{
	float x = TableauX;

	for (auto& pile : this->_piles)
	{
		if (pile.empty())
		{
			OtherCards::getEmpty().setCardPos(sf::Vector2f(x, TableauHeight));
			OtherCards::getEmpty().render(target);
		}
		else
			for (auto& card : pile)
			{
				card.render(target);
			}
		x += CardXoffset;
	}
}

void Tableau::updateFromPos(int pileI, int startI)
{
	auto& pile = this->_piles[pileI];

	if (startI >= pile.size()) return;
	sf::Vector2f pos = pile[startI].getSprite().getPosition();
	
	for (int i {startI + 1}; i < pile.size(); i++)
	{
		pos.y += CardHeightOffset;
		pile[i].getSprite().setPosition(pos);
	}
}

std::vector<Card>& Tableau::operator[](int index)
{
	return this->_piles[index];
}

Tableau::Tableau()
{
	this->_piles.resize(TableauSize);

	float x = TableauX;
	float y = TableauHeight;

	for (int i{}; i < 7; i++)
	{
		this->_pileRect[i] = { {x, y}, {125.f, 181.5f}};
		x += CardXoffset;
	}

}
