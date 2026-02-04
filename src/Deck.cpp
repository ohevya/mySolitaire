#include "Deck.h"

void Deck::_generateCards()
{
	this->_textureList.push_back(sf::Texture());
	sf::Texture& back = this->_textureList.back();

	if (!back.loadFromFile("../images/card_back.png"))
		std::cout << "Texture did  not load" << "\n";

	for (int value{ 1 }; value <= 13; value++)
	{
		for (int suit{ 1 }; suit <= 4; suit++)
		{
			this->_textureList.push_back(sf::Texture());
			sf::Texture& front = this->_textureList.back();

			string cardPath = "../images/" + std::to_string(value) + "_of_" + suitToString(suit) + ".png";


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
		if (flip(rng))
		{
			card->flipCard();
		}
		

	}
	std::ranges::shuffle(this->_stock, rng);
}

Deck::Deck(int drawAmount):
	_drawAmount(drawAmount)
{
	this->_generateCards();

	this->_textureList.push_back(sf::Texture());
	sf::Texture& empty = this->_textureList.back();

	if (empty.loadFromFile("../images/empty.png"))
		this->_empty = new Card(this->_wastePos, empty, empty,0, 0);

	this->_textureList.push_back(sf::Texture());
	sf::Texture& flip = this->_textureList.back();

	if (flip.loadFromFile("../images/deck_flipped.png"))
		this->_flipCards = new Card(this->_stockPos, flip, flip, 0, 0);


	this->shuffleDeck();

}

Deck::~Deck()
{
	for (auto& card : this->_stock)
		delete card;
	for (auto& card : this->_waste)
		delete card;
	delete _empty;
	delete _flipCards;
}

void Deck::update(const sf::RenderWindow& window)
{	
	if (this->_stock.empty())
		this->_flipCards->update(window, this->_stockPos);
	else
		this->_stock.back()->update(window, this->_stockPos);

	if (this->_waste.empty())
		this->_empty->update(window, this->_wastePos);
	else
		this->_waste.back()->update(window, this->_wastePos);
	
}

void Deck::render(sf::RenderTarget& target)
{
	if (this->_stock.empty())
		this->_empty->render(target);
	else
		this->_stock.back()->render(target);

	if (this->_waste.empty())
		this->_empty->render(target);
	else
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

void Deck::mouseRelesed(sf::Vector2f mousePos)
{
	if (this->_empty->getSprite().getGlobalBounds().contains(mousePos))// || this->_waste.back()->getSprite().getGlobalBounds().contains(mousePos))
	{
		this->nextCard();
	}
}
