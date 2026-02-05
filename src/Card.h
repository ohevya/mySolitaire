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
	bool _faceUp = false;
	int _value;
	int _suit;

	sf::Texture& _faceUpTexture;
	sf::Texture& _faceDownTexture;

	sf::Sprite _cardSprite;


public:
	static Card* activeCard;
	bool _locked = false;

	Card(sf::Vector2f mousePosView, sf::Texture& front, sf::Texture& back, int value, int suit);
	Card(sf::Texture& front, sf::Texture& back, int value, int suit);

	/*Card(const Card& other);*/

	const bool& isFaceUp() const;
	void flipCard();

	void update(const sf::RenderWindow& window, sf::Vector2f& defultPos);

	void render(sf::RenderTarget& target);

	bool inClick(sf::Vector2f&  mousePos);

	//set
	void setFaceUpVar(bool value);
	void setCardPos(sf::Vector2f cardPos);
	//get
	const sf::Sprite& getSprite() const;
	const int& getValue() const;
	const int& getSuit() const;
	Card& getCard();

	//opreter
	Card& operator=(const Card& other);

};


