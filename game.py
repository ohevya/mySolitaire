from deck_ import Card, valueSwitch



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

def can_play(position, deck, piles):
    if position[0] == -1 or not deck[position[0]].face_up:
        return [False]
    return [canPlayOnPile(position, deck, piles[i]) for i in range(7)]


def canPlayOnPile(position, deck, pile):
    cardToPlay = deck[position[0]]
    if pile[-1].color == cardToPlay.color or valueSwitch(cardToPlay.value) != valueSwitch(pile[-1].value) - 1:
        return False
    else:
        return True
    
            



def play(position, deck, piles, i):
    cardToPlay = deck[position[0]]
    deck.pop(position[0])
    position[0] -= 1
    piles[i].append(cardToPlay)
