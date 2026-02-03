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

Deck::Deck(int& difcllty):
	_difcllty(difcllty)
{
	this->_generateCards();
	this->shuffleDeck();

}
