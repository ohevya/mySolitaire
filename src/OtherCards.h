#pragma once
#include "Card.h"


class OtherCards
{
private:
    static Card* _empty;
    static Card* _flipped;

public:
    static void setTemps(Card* empty, Card* flipped);
    static Card& getEmpty();
    static Card& getFlipped();

    ~OtherCards();
};
