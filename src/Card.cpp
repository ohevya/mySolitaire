#include "Card.h"

Card::Card(sf::Vector2f mousePosView, sf::Texture& front, sf::Texture& back, int value, int suit)
	: _faceDownTexture(back), _faceUpTexture(front), _cardSprite(_faceDownTexture), _faceUp(false),  _value(value), _suit(suit)
{
	this->_cardSprite.setPosition(sf::Vector2f(mousePosView.x - this->_cardSprite.getGlobalBounds().size.x / 2.f , mousePosView.y - this->_cardSprite.getGlobalBounds().size.y / 2.f));
}

Card::Card(sf::Texture& front, sf::Texture& back, int value, int suit):
	_faceDownTexture(back), _faceUpTexture(front), _cardSprite(_faceDownTexture), _faceUp(false), _value(value), _suit(suit)
{
}

const bool& Card::isFaceUp() const
{
	return this->_faceUp;
}

void Card::flipCard()
{
	this->_faceUp = !this->_faceUp;
	if (this->_faceUp)
	{
		this->_cardSprite.setTexture(this->_faceUpTexture, true);
		this->_cardSprite.setScale(sf::Vector2f(0.15f, 0.15f));
	}
	else
	{
		this->_cardSprite.setTexture(this->_faceDownTexture, true);
		this->_cardSprite.setScale(sf::Vector2f(1, 1));
	}
}

void Card::update(const sf::RenderWindow& window)
{
	sf::Vector2f mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (this->inClick(mousePosView))
	{
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		//{
		//	this->flipCard();
		//}
		 if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			this->_cardSprite.setPosition(sf::Vector2f(mousePosView.x - this->_cardSprite.getGlobalBounds().size.x / 2.f, mousePosView.y - this->_cardSprite.getGlobalBounds().size.y / 2.f));
	}

}

void Card::render(sf::RenderTarget& target)
{
	target.draw(this->_cardSprite);
}

bool Card::inClick(sf::Vector2f& mousePos)
{
	if (this->_cardSprite.getGlobalBounds().contains(mousePos))
		return true;
	return false;
}

void Card::setFaceUpVar(bool value)
{
	this->_faceUp = value;
}
