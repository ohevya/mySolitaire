#include "Card.h"

Card* Card::activeCard = nullptr;

Card::Card(sf::Vector2f cardPos, std::shared_ptr<sf::Texture> front, std::shared_ptr<sf::Texture> back, int value, int suit)
	: _faceUpTexture(front)
	, _faceDownTexture(back)
	, _value(value)
	, _suit(suit)
	,_cardSprite(*this->_faceDownTexture)
{
	// initialize sprite with back texture if available
	if (this->_faceDownTexture)
		this->_cardSprite.setTexture(*this->_faceDownTexture, true);

	this->_cardSprite.setPosition(cardPos);
	this->_cardSprite.setScale(sf::Vector2f(0.25f, 0.25f));
}

Card::Card(std::shared_ptr<sf::Texture> front, std::shared_ptr<sf::Texture> back, int value, int suit)
	: _faceUpTexture(front)
	, _faceDownTexture(back)
	, _value(value)
	, _suit(suit)
	, _cardSprite(*this->_faceDownTexture)
{
	// default to face-down texture if available
	if (this->_faceDownTexture)
		this->_cardSprite.setTexture(*this->_faceDownTexture, true);

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
	{
		if (this->_faceUpTexture)
			this->_cardSprite.setTexture(*this->_faceUpTexture, true);
	}
	else
	{
		if (this->_faceDownTexture)
			this->_cardSprite.setTexture(*this->_faceDownTexture, true);
	}
}

void Card::update(const sf::Vector2f& defaultPos)
{
	this->_cardSprite.setPosition(defaultPos);
}

void Card::render(sf::RenderTarget& target)
{
	target.draw(this->_cardSprite);
}

bool Card::inClick(sf::Vector2f& mousePos)
{
	return this->_cardSprite.getGlobalBounds().contains(mousePos);
}

void Card::setFaceUpVar(bool value)
{
	this->_faceUp = value;
}

void Card::setCardPos(sf::Vector2f cardPos)
{
	this->_cardSprite.setPosition(cardPos);
}

sf::Sprite& Card::getSprite()
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

	// copy shared ownership of textures
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
