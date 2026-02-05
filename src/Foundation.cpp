#include "Foundation.h"

Foundation::Foundation(sf::Vector2f pos):
	_pos(pos)
{
}

void Foundation::addNewCard(Card newCard)
{
	newCard._locked = true;
	this->_foundation.push_back(newCard);
}

void Foundation::update(const sf::RenderWindow& window)
{
	this->_foundation.back().update(window, this->_pos);
}

void Foundation::render(sf::RenderTarget& target)
{
	this->_foundation.back().render(target);
}

const sf::Sprite& Foundation::getcardSprite() const
{
	return this->_foundation.back().getSprite();
}

Card& Foundation::getcard()
{
	return this->_foundation.back();
}
