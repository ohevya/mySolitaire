#include "Foundation.h"

Foundation::Foundation(sf::Vector2f pos):
	_pos(pos)
{
}

void Foundation::addNewCard(Card newCard)
{
	newCard._locked = true;
	newCard.setCardPos(this->_pos);
	if (!newCard.isFaceUp())
		newCard.flipCard();
	this->_foundation.push_back(std::move(newCard));
}

void Foundation::update(const sf::RenderWindow& window)
{
	this->_foundation.back().update(window, this->_pos);
}

void Foundation::render(sf::RenderTarget& target)
{
	this->_foundation.back().render(target);
}


Card& Foundation::getCard()
{
	return this->_foundation.back();
}
