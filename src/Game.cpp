#include "Game.h"
#include <iostream>

Game::Game(int drawAmount)
{
	this->_generateCards();
	this->_deck.shuffleDeck();
	this->_deck.setDrawAmount(drawAmount);
}

void Game::update(const sf::RenderWindow& window)
{
	this->_deck.update(window);

	for (auto& foundation : this->_foundationArr)
		foundation.update(window);
}

void Game::render(sf::RenderTarget& target)
{
	this->_deck.render(target);

	for (auto& foundation : this->_foundationArr)
		foundation.render(target);
}

void Game::mouseReleased(sf::Vector2f mousePos)
{
	if (this->_deck.getEmpty().getCard().inClick(mousePos))
	{
		this->_deck.nextCard();
		return ;
	}

	//face don to move

	if (this->_deck.getWaste().empty() || !this->_deck.getWaste().back().isFaceUp())
		return;

	for (int i{}; i < 4; i++)
	{
		if (this->_foundationArr[i].getCard().inClick(mousePos))
		{
			this->moveFromWasteToFoundation(i);
			break;
		}
	}
	
}

void Game::moveFromWasteToFoundation(int i)
{
	auto& waste = this->_deck.getWaste();
	if (waste.empty())
		return;

	Card WCard = waste.back();
	Card& FCard = this->_foundationArr[i].getCard();

	if (FCard.getSuit()  == WCard.getSuit() && FCard.getValue() + 1 == WCard.getValue())
	{
		this->_foundationArr[i].addNewCard(WCard);
		this->_deck.getWaste().pop_back();
	}
}


void Game::_generateCards()
{
	auto back = this->loadtoTextureListFromFile("card_back.png");

	for (int suit{ 1 }; suit <= 4; suit++)
	{
		auto front = this->loadtoTextureListFromFile(1 , suit);
		this->_foundationArr[suit - 1].addNewCard(Card(front, back, 1, suit));

		for (int value{ 2 }; value <= 13; value++)
		{
			auto frontVal = this->loadtoTextureListFromFile(value, suit);
			this->_deck.addNewCard(Card(frontVal, back, value, suit));
		} 
	}
	// first 
	auto empty = this->loadtoTextureListFromFile("empty.png");
	this->_deck.addNewCardToTemps(Card(_deck.getWastePos(), empty, empty, 0, 0));
	// last 
	auto flip = this->loadtoTextureListFromFile("deck_flipped.png");
	this->_deck.addNewCardToTemps(Card(_deck.getStockPos(), flip, flip, 0, 0));
}

std::shared_ptr<sf::Texture> Game::loadtoTextureListFromFile(int value, int suit)
{
	auto tex = std::make_shared<sf::Texture>();
	std::string texturePath = "../images/" + std::to_string(value) + "_of_" + suitToString(suit) + ".png";

	if (!tex->loadFromFile(texturePath))
		std::cerr << "not found path " << texturePath << "\n";

	this->_textureList.push_back(tex);
	return this->_textureList.back();
}

std::shared_ptr<sf::Texture> Game::loadtoTextureListFromFile(const std::string& fileName)
{
	auto tex = std::make_shared<sf::Texture>();
	std::string texturePath = "../images/" + fileName;

	if (!tex->loadFromFile(texturePath))
		std::cerr << "not found path " << texturePath << "\n";

	this->_textureList.push_back(tex);
	return this->_textureList.back();
}