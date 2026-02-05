#include "Card.h"
Card* Card::activeCard = nullptr;

Card::Card(sf::Vector2f cardPos, sf::Texture& front, sf::Texture& back, int value, int suit)
	: _faceDownTexture(back), _faceUpTexture(front), _cardSprite(_faceDownTexture),  _value(value), _suit(suit)
{
	this->_cardSprite.setPosition(cardPos);
	this->_cardSprite.setScale(sf::Vector2f(0.25f, 0.25f));
}

Card::Card(sf::Texture& front, sf::Texture& back, int value, int suit):
	_faceDownTexture(back), _faceUpTexture(front), _cardSprite(_faceDownTexture), _value(value), _suit(suit)
{
	this->_cardSprite.setScale(sf::Vector2f(0.25f, 0.25f));
}



const bool& Card::isFaceUp() const
{
	return this->_faceUp;
}

void Card::flipCard()
{
	this->_faceUp = !this->_faceUp;
	if (this->_faceUp)
		this->_cardSprite.setTexture(this->_faceUpTexture, true);
	else
		this->_cardSprite.setTexture(this->_faceDownTexture, true);
}

void Card::update(const sf::RenderWindow& window, sf::Vector2f& defaultPos)
{
	this->_cardSprite.setPosition(defaultPos);
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (activeCard == nullptr && !this->_locked  && this->inClick(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		Card::activeCard = this;

	if (Card::activeCard == this)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			this->_cardSprite.setPosition(sf::Vector2f(mousePos.x - this->_cardSprite.getGlobalBounds().size.x / 2.f, mousePos.y - this->_cardSprite.getGlobalBounds().size.y / 2.f));
		else
			Card::activeCard = nullptr;
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

void Card::setCardPos(sf::Vector2f cardPos)
{
	this->_cardSprite.setPosition(cardPos);
}

const sf::Sprite& Card::getSprite() const
{
	return this->_cardSprite;
}

const int& Card::getValue() const
{
	return this->_value;
}

const int& Card::getSuit() const
{
	return this->_suit;
}

Card& Card::getCard()
{
	return *this;
}

Card& Card::operator=(const Card& other)
{
	if (this == &other)
		return *this;

	this->_faceUp = other._faceUp;
	this->_value  = other._value;
	this->_suit   = other._suit;


	this->_faceUpTexture  = other._faceUpTexture;
	this->_faceDownTexture = other._faceDownTexture;

	this->_cardSprite = other._cardSprite;

	return *this;
}

string suitToString(int suit)
{
	switch (suit)
	{
	case 1: return "hearts";
	case 2: return "clubs";	
	case 3: return "diamonds";
	case 4: return "spades";
	}
	return "unknown";
}
