#include "Deck.h"


void Deck::shuffleDeck()
{
	std::random_device rd;
	std::mt19937 rng(rd());

	std::bernoulli_distribution flip(0.5);
	for (Card& card : this->_stock)
	{
		if (flip(rng))
		{
			card.flipCard();
		}
		

	}
	std::ranges::shuffle(this->_stock, rng);
}

void Deck::setDrawAmount(int drawAmount)
{
	this->_drawAmount = drawAmount;
}


std::vector<Card>& Deck::getStock()
{
	return this->_stock;
}

std::vector<Card>& Deck::getWaste()
{
	return this->_waste;
}
sf::Vector2f& Deck::getStockPos()
{
	return this->_stockPos;
}

sf::Vector2f& Deck::getWastePos()
{
	return this->_wastePos;
}




//Deck::~Deck()
//{
//	for (auto& card : this->_stock)
//		delete card;
//	for (auto& card : this->_waste)
//		delete card;
//	delete _empty;
//	delete _flipCards;
//}

void Deck::update(const sf::RenderWindow& window)
{	
	if (this->_stock.empty())
		OtherCards::getEmpty().setCardPos(this->_stockPos);
	else
		this->_stock.back().update(window, this->_stockPos);

	if (this->_waste.empty())
	{ }
	else
		this->_waste.back().update(window, this->_wastePos);
	
}

void Deck::render(sf::RenderTarget& target)
{
	if (this->_stock.empty())
		OtherCards::getFlipped().render(target);
	else
		this->_stock.back().render(target);

	if (this->_waste.empty())
	{
		OtherCards::getEmpty().setCardPos(this->_wastePos);
		OtherCards::getEmpty().render(target);
	}
	else
		this->_waste.back().render(target);
}

void Deck::nextCard()
{
	Card::activeCard = nullptr;
	if (this->_stock.empty())
		resetStock();
	else
	{
		for (int i{}; i < this->_drawAmount && !this->_stock.empty(); i++)
		{
			this->_stock.back().flipCard();
			this->_waste.push_back(this->_stock.back());
			this->_stock.pop_back();
		}
	}
}

void Deck::resetStock()
{
	this->_stock.swap(this->_waste);
}


void Deck::addNewCard(Card newCard) { this->_stock.push_back(newCard); }

