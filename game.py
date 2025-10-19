from deck_ import *
from display import *
from piles import *



def turn_deck_over(deck):
    deck.reverse()
    for card in deck:
        card.face_up = not card.face_up
    return "Deck flipped!\n"

def flip(position, deck):
    # need revision
    if position[0] == len(deck) - 1:
        position[0] = -1
        return turn_deck_over(deck)
    elif position[0] + 3 >= len(deck):
        position[0] = len(deck) - 1
    else:
        position[0] += 3


def can_play(position, deck):
    if position[0] != -1 and deck[position[0]].face_up == True:
        return True
    return False



def play(position, deck, piles, i):
    played = deck[position[0]]
    deck.pop(position[0])
    position[0] -= 1
    piles[i].append(played)