#pragma once
#include "Deck.h"
#include "Foundation.h"

class Game
{
private:
	Deck _deck;
	Foundation _foundationArr[4]{
		  Foundation(sf::Vector2f(700.f,100.f)),
		  Foundation(sf::Vector2f(850.f, 100.f)),
		  Foundation(sf::Vector2f(1000.f, 100.f)),
		  Foundation(sf::Vector2f(150.f, 100.f))
	};



	std::deque<sf::Texture> _textureList;

	void _generateCards();
	sf::Texture& loadtoTextureListFromFlie(int value, int suit);
	sf::Texture& loadtoTextureListFromFlie(string FileName);
public:
	Game(int drawAmount);

	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

	void mouseRelesed(sf::Vector2f mousePos);

	void moveFromWasteToFoundtion(int i);
};
