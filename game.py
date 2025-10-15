from deck_ import *
from game import *
from disply import *
from piles import *



def turn_deck_over(deck):
    deck.reverse()
    for card in deck:
        card.face_up = not card.face_up
    print("Deck flipped!\n")

def flip(position, deck):

    if position[0] == len(deck) - 1:
        position[0] = -1
        turn_deck_over(deck)
    elif position[0] + 3 >= len(deck):
        position[0] = len(deck) - 1
    else:
        position[0] += 3

def play(position, deck, played):

    if position[0] != -1 and deck[position[0]].face_up == True:
        played.append(deck[position[0]])
        deck.pop(position[0])
        position[0] -= 1
        print("playing card..\n")
    else:
        print("can't play this card.\n")

def loop():

    played = []
    deck = create_deck()
    position = [-1]
    piles = pile_set_up(deck)
    foundationPiles = [[],[],[],[]]

    answer_key = {
        'q' : lambda: quit(),
        'p' : lambda: print_deck(deck),

        '0' : lambda: play(position, deck, played),
        '1' : lambda: flip(position, deck),
        '2' : lambda: print_played(played),
    }


    while True:
        answer = input("\n 0: play\n 1: flip\n 2: print played\n p: print deck\n q: Quit\n :")
        if answer in answer_key:
            answer_key[answer]()
        print_board(foundationPiles, piles, position, deck)