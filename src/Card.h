#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"

using std::string;
enum Suits { hearts = 1, clubs, diamonds, spades };

string suitToString(int suit);

class Card
{
private:
	bool _faceUp = true;
	int _value;
	int _suit;


	sf::Texture& _faceUpTexture;
	sf::Texture& _faceDownTexture;

	sf::Sprite _cardSprite;

	static Card* activeCard;

public:
	Card(sf::Vector2f mousePosView, sf::Texture& front, sf::Texture& back, int value, int suit);
	Card(sf::Texture& front, sf::Texture& back, int value, int suit);

	const bool& isFaceUp() const;
	void flipCard();

	void update(const sf::RenderWindow& window, sf::Vector2f& defultPos);

	void render(sf::RenderTarget& target);

	bool inClick(sf::Vector2f&  mousePos);

	//set
	void setFaceUpVar(bool value);
	void setCardPos(sf::Vector2f cardPos);
	//get
	sf::Sprite& getSprite();

};


