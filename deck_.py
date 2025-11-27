import random
from Card import *


def generate_cards(values, suits):
    cards = []
    for suit in suits:
        for value in values:
            cards.append(valueSwitch(Card(valueSwitch(value), suit)))
    return cards


def shuffle_deck(deck):
    for card in deck:
        card.face_up = random.choice((True,False))
    random.shuffle(deck)


def foundationSetup():
    return [[Card(0, 'clubs')],[Card(0, 'diamonds')],[Card(0, 'spades')],[Card(0, 'hearts')]]

def create_deck():
    values = set(range(1,14))
    suits = ("clubs", "diamonds", "spades", "hearts")

    deck = generate_cards(values, suits)

    shuffle_deck(deck)

    return deck


def pile_set_up(deck):
    plies = [[],[],[],[],[],[],[]]
    i, j = 0,0

    while i < 7:
        for j in range(i+1):
            plies[i].append(deck[0])
            deck.pop(0)
        plies[i][-1].face_up = True
        i += 1
    return plies
