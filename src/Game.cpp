#include "Game.h"
#include <iostream>

Game::Game(int drawAmount)
{
	this->_generateCards();
	this->_deck.shuffleDeck();
	this->_deck.setDrawAmount(drawAmount);
	this->_BuildTableau();
}

void Game::update(const sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);


	if (!mousePressed)
		Card::activeCard = nullptr;
	else if (Card::activeCard == nullptr)
	{
		if (this->_deck._wasteArea.contains(mousePos))
		{
			if (this->_deck.getWaste().empty())
				Card::activeCard = &OtherCards::getEmpty();
			else
				Card::activeCard = &this->_deck.getWaste().back();
			return;
		}

		if (OtherCards::getFlipped().getCard().inClick(mousePos))
		{
			if (this->_deck.getStock().empty())
				Card::activeCard = &OtherCards::getFlipped();
			else
				Card::activeCard = &this->_deck.getStock().back();
			return;
		}

		for (int i{}; i < 7; i++)
		{
			auto& currTableau = this->_tableau[i];

			if (!currTableau.empty())
				for (int j = std::ssize(currTableau) - 1; j >= 0; j--)
				{
					auto& currCard = currTableau[j];
					if (currCard.inClick(mousePos))
					{
						Card::activeCard  = &currCard;

						this->_startI = j;
						this->_pileI = i;
						
						return;
					}
				}
		}
	}
	else
	{
		sf::Sprite& activeSprite = Card::activeCard->getSprite();
		activeSprite.setPosition(sf::Vector2f(mousePos.x - activeSprite.getGlobalBounds().size.x / 2.f, mousePos.y - activeSprite.getGlobalBounds().size.y / 2.f));

		if (this->_pileI != -1)
			this->_tableau.updateFromPos(this->_pileI, this->_startI);

	}


	if (Card::activeCard == nullptr)
	{
		this->_tableau.update(window);
		this->_deck.update(window);
		for (int i{}; i < 4; i++)
			this->_foundationArr[i];

		this->_startI = 0;
		this->_pileI = -1;
	}
}

void Game::render(sf::RenderTarget& target)
{
	this->_deck.render(target);
	this->_tableau.render(target);

	for (auto& foundation : this->_foundationArr)
		foundation.render(target);
}

void Game::mouseReleased(sf::Vector2f mousePos)
{
	if (this->_deck._wasteArea.contains(mousePos))
	{
		if (this->_deck.getStock().empty())
		{ 
			if (Card::activeCard == &OtherCards::getFlipped())
				this->_deck.nextCard();
		}
		else if (Card::activeCard == &this->_deck.getStock().back())
			this->_deck.nextCard();
		return;
	}

	for (int i{}; i < 7; i++)
	{
		if (i == this->_pileI)
			continue;

		auto& currTableau = this->_tableau[i];

		if (currTableau.empty() && this->_tableau._pileRect[i].contains(mousePos))
		{
			if (this->_pileI != -1)
				this->moveFromPileToPile(i);
			else
				this->moveWasteToTableau(i);
			return;
		}

		for (int j = { 0 }; j < currTableau.size(); j++)
		{
			if (currTableau[j].inClick(mousePos) )
			{
				if (this->_pileI != -1)
					this->moveFromPileToPile(i);
				else
					this->moveWasteToTableau(i);
				return;
			}
		}
	}

	for (int i{}; i < 4; i++)
	{
		if (this->_foundationArr[i].getCard().inClick(mousePos))
		{

			if (this->_pileI != -1)
				this->moveFromPileToFoundation(i);
			else if (this->_deck.getWaste().empty() || !this->_deck.getWaste().back().isFaceUp())
				return;
			else
				this->moveFromWasteToFoundation(i);
			break;
		}
	}

	if (this->_deck.getWaste().empty() || !this->_deck.getWaste().back().isFaceUp())
		return;
	
}

void Game::moveFromWasteToFoundation(int i)
{
	auto& waste = this->_deck.getWaste();
	if (waste.empty())
		return;

	Card WCard = waste.back();
	Card& FCard = this->_foundationArr[i].getCard();

	if (FCard.getSuit() == WCard.getSuit() && FCard.getValue() + 1 == WCard.getValue())
	{
		this->_foundationArr[i].addNewCard(WCard);
		this->_deck.getWaste().pop_back();
	}
}

void Game::moveFromPileToPile(int pileI)
{
	auto& destPile = this->_tableau[pileI];
	auto& sourcePile = this->_tableau[this->_pileI];

	if (!sourcePile[this->_startI].isFaceUp())
		return;

	if (destPile.empty())
	{
		if (sourcePile[this->_startI].getValue() != 13)
			return;
	}
	else if (sourcePile[this->_startI].getValue() + 1 != destPile.back().getValue() || sourcePile[this->_startI].getSuit() % 2 == destPile.back().getSuit() % 2)
			return;

	for (int i{ this->_startI}; i < sourcePile.size(); i++)
	{
		destPile.push_back(sourcePile[i]);
	}
	sourcePile.erase(sourcePile.begin() + this->_startI, sourcePile.end());
}


void Game::moveWasteToTableau(int pileI)
{
	auto& waste = this->_deck.getWaste();
	auto& destPile = this->_tableau[pileI];

	bool canMove{false};

	if (waste.empty())
		return;

	Card& wasteCard = waste.back();

	if (destPile.empty())
		canMove = (wasteCard.getValue() == 13);
	else
	{
		Card& pileCard = destPile.back();
		canMove = ( ( pileCard.getSuit() % 2 != wasteCard.getSuit() % 2) && pileCard.getValue() - 1 == wasteCard.getValue() );
	}

	if (canMove)
	{
		destPile.push_back(std::move(waste.back()));
		this->_deck.getWaste().pop_back();
	}
}

void Game::moveFromPileToFoundation(int foundationI)
{
	if (this->_tableau[this->_pileI].empty())
		return;

	Card PileBackCard = this->_tableau[this->_pileI].back().getCard();
	Card& FoundationCard = this->_foundationArr[foundationI].getCard();

	/*if (Card::activeCard != &PileBackCard)
		return;*/

	if (FoundationCard.getSuit() == PileBackCard.getSuit() && FoundationCard.getValue() + 1 == PileBackCard.getValue())
	{
		this->_foundationArr[foundationI].addNewCard(PileBackCard);
		this->_tableau[this->_pileI].pop_back();
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
	auto empty = this->loadtoTextureListFromFile("empty.png");
	auto flip = this->loadtoTextureListFromFile("deck_flipped.png");


	OtherCards::setTemps(new Card(_deck.getWastePos(), empty, empty, 0, 0), new Card(_deck.getStockPos(), flip, flip, 0, 0));
}

void Game::_BuildTableau()
{
	float x{500};
	float y{300};


	auto& stock = this->_deck.getStock();
	for (int i{}; i < 7; i++)
	{
		auto& currTableau = this->_tableau[i];
		for (int j{}; j <= i; j++)
		{
			currTableau.push_back(stock.back());
			stock.pop_back();
			currTableau.front().getSprite().setPosition(sf::Vector2f(x, y));
			y += 35;
		}
		if (!currTableau.back().isFaceUp())
			currTableau.back().flipCard();

		x += 150;
		y = 300;
	}
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