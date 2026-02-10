#pragma once
#include "Deck.h"
#include "Tableau.h"
#include "Foundation.h"
// #include <memory>
// #include <vector>
// #include <string>

class Game
{
private:
	Deck _deck;
	Foundation _foundationArr[4]{
		  Foundation(sf::Vector2f(700.f,100.f)),
		  Foundation(sf::Vector2f(850.f, 100.f)),
		  Foundation(sf::Vector2f(1000.f, 100.f)),
		  Foundation(sf::Vector2f(1150.f, 100.f))
	};

	std::vector<std::shared_ptr<sf::Texture>> _textureList;

	Tableau _tableau;

	void _generateCards();
	void _BuildTableau();

	std::shared_ptr<sf::Texture> loadtoTextureListFromFile(int value, int suit);
	std::shared_ptr<sf::Texture> loadtoTextureListFromFile(const std::string& FileName);
public:
	Game(int drawAmount);

	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

	void mouseReleased(sf::Vector2f mousePos);

	void moveFromWasteToFoundation(int i);
	void moveFromPileToPile(int pileI);

	int _startI{0}, _pileI{ -1 };
};
