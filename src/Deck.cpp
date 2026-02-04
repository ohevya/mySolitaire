#include "Deck.h"

void Deck::_generateCards()
{
	sf::Texture back;

	if (!back.loadFromFile("../images/card_back.png"))
		std::cout << "Texture did  not load" << "\n";
	for (int value{ 1 }; value < 14; value++)
	{
		string cardPath = "../images/" + std::to_string(value) + "_";
		for (int suit{ 1 }; suit <= 4; suit++)
		{
			cardPath += suitToString(suit) + ".png";

			sf::Texture front;

			if (!front.loadFromFile(cardPath))
				std::cout << "Texture did  not load" << cardPath <<"\n";
			else
				this->_stock.push_back(new Card(front, back, value, suit));
		}
	}
}

void Deck::shuffleDeck()
{
	std::random_device rd;
	std::mt19937 rng(rd());

	std::bernoulli_distribution flip(0.5);
	for (Card* card : this->_stock)
	{
		card->setFaceUpVar(flip(rng));

	}
	std::ranges::shuffle(this->_stock, rng);
}

Deck::Deck(int& drawAmount):
	_drawAmount(drawAmount)
{
	this->_generateCards();
	this->shuffleDeck();

}

void Deck::update(const sf::RenderWindow& window)
{
	this->_stock.back()->setCardPos(this->_stockPos);
	this->_stock.back()->setCardPos(this->_wastePos);
}

void Deck::render(sf::RenderTarget& target)
{
	this->_stock.back()->render(target);
	this->_waste.back()->render(target);
}

void Deck::nextCard()
{
	if (this->_stock.empty())
		resetStock();
	else
	{
		for (int i{}; i < this->_drawAmount && !this->_stock.empty(); i++)
		{
			this->_stock.back()->flipCard();
			this->_waste.push_back(this->_stock.back());
			this->_stock.pop_back();
		}
	}
}

void Deck::resetStock()
{
	this->_stock.swap(this->_waste);
}
