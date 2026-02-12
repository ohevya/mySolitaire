#pragma once
#include "Deck.h"
#include "Tableau.h"
#include "Foundation.h"
#include "OtherCards.h"
// #include <memory>
// #include <vector>
// #include <string>


class Game
{
private:
	Deck _deck;
	Foundation _foundationArr[4]{
		  Foundation(FoundationPos[0]),
		  Foundation(FoundationPos[1]),
		  Foundation(FoundationPos[2]),
		  Foundation(FoundationPos[3])
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

	void moveWasteToTableau(int pileI);

	void moveFromPileToFoundation(int foundationI);
	void moveFromPileToPile(int pileI);



	int _startI{0}, _pileI{ -1 };
};
