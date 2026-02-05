#include "Game.h"

Game::Game(int drawAmount)
{
	this->_generateCards();
	this->_deck.shuffleDeck();
	this->_deck.setDrawAmount(drawAmount);
}

void Game::update(const sf::RenderWindow& window)
{
	this->_deck.update(window);

	for (auto& fundation : this->_foundationArr)
		fundation.update(window);

}

void Game::render(sf::RenderTarget& target)
{
	this->_deck.render(target);

	for (auto& fundation : this->_foundationArr)
		fundation.render(target);
}

void Game::mouseRelesed(sf::Vector2f mousePos)
{
	if (this->_deck.getEmpty().getSprite().getGlobalBounds().contains(mousePos))// || this->_waste.back()->getSprite().getGlobalBounds().contains(mousePos))
	{
		this->_deck.nextCard();
		return ;
	}

	for (int i{}; i < 4; i++)
	{
		if (this->_foundationArr[i].getcardSprite().getGlobalBounds().contains(mousePos))
		{
			this->moveFromWasteToFoundtion(i);
			break;
		}
	}
	
}

void Game::moveFromWasteToFoundtion(int i)
{
	auto& waste = this->_deck.getWaste();
	if (waste.empty())
		return;

	Card& WCard = waste.back();
	Card& FCard = this->_foundationArr[i].getcard();

	if (FCard.getSuit()  == WCard.getSuit() && FCard.getValue() - 1 == WCard.getValue())
	{
		FCard = WCard;

		this->_deck.getWaste().pop_back();
	}
}


void Game::_generateCards()
{
	sf::Texture& back = this->loadtoTextureListFromFlie("card_back.png");

	for (int suit{ 1 }; suit <= 4; suit++)
	{
		sf::Texture& front = this->loadtoTextureListFromFlie(1 , suit);
		this->_foundationArr[suit - 1].addNewCard(Card(front, back, 1, suit));
		this->_foundationArr[suit - 1].getcard().flipCard();
		this->_foundationArr[suit - 1].getcard()._locked = true;

		for (int value{ 2 }; value <= 13; value++)
		{
				sf::Texture& front = this->loadtoTextureListFromFlie(value, suit);
				this->_deck.addNewCard(Card(front, back, value, suit));

		} 
	}
	//first
	sf::Texture& empty = this->loadtoTextureListFromFlie("empty.png");
	this->_deck.addNewCardToTemps(Card(_deck.getWastePos(), empty, empty, 0, 0));
	//last
	sf::Texture& flip = this->loadtoTextureListFromFlie("deck_flipped.png");
	this->_deck.addNewCardToTemps(Card(_deck.getStockPos(), flip, flip, 0, 0));

}

sf::Texture& Game::loadtoTextureListFromFlie(int value, int suit)
{
	this->_textureList.push_back(sf::Texture());

	string texturePath = "../images/" + std::to_string(value) + "_of_" + suitToString(suit) + ".png";

	if (!this->_textureList.back().loadFromFile(texturePath))
		std::cerr << "not found path " << texturePath << "\n";

	return this->_textureList.back();
}

sf::Texture& Game::loadtoTextureListFromFlie(string fileName)
{
	this->_textureList.push_back(sf::Texture());

	string texturePath = "../images/" + fileName;

	if (!this->_textureList.back().loadFromFile(texturePath))
		std::cerr << "not found path " << texturePath << "\n";

	return this->_textureList.back();
}