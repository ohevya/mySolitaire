#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory>
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

	std::shared_ptr<sf::Texture> _faceUpTexture;
	std::shared_ptr<sf::Texture> _faceDownTexture;

	sf::Sprite _cardSprite;

public:
	static Card* activeCard;
	bool _locked = false;

	Card(sf::Vector2f mousePosView, std::shared_ptr<sf::Texture> front, std::shared_ptr<sf::Texture> back, int value, int suit);
	Card(std::shared_ptr<sf::Texture> front, std::shared_ptr<sf::Texture> back, int value, int suit);

	const bool& isFaceUp() const;
	void flipCard();

	void update(const sf::RenderWindow& window, sf::Vector2f& defaultPos);

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

	//operator
	Card& operator=(const Card& other);

};


