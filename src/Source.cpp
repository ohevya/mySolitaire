#include "OtherCards.h"


Card* OtherCards::_empty = nullptr;
Card* OtherCards::_flipped = nullptr;

void OtherCards::setTemps(Card* empty, Card* flipped)
{
    _empty = empty;
    _flipped = flipped;
}

Card& OtherCards::getEmpty()
{
    return *_empty;
}

Card& OtherCards::getFlipped()
{
    return *_flipped;
}

OtherCards::~OtherCards()
{
    delete _empty;
    delete _flipped;
}