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
    position[0] += 1


def can_play(position, deck, piles, foundationPiles):
    if position[0] == -1 or not deck[position[0]].face_up:
        return [False]
    foundation = [canPlayOnFoundation(position, deck, foundationPiles[i]) for i in range(4)]
    if True in foundation:
        return foundation
    return [canPlayOnPile(position, deck, piles[i]) for i in range(7)]


def canPlayOnPile(position, deck, pile):
    cardToPlay = deck[position[0]]
    if pile[-1].color != cardToPlay.color and cardToPlay.value == pile[-1].value - 1:
        return True
    else:
        return False
    
            
def canPlayOnFoundation(position, deck, foundationPile):
    cardToPlay = deck[position[0]]
    if foundationPile:
        if cardToPlay.value - 1 == foundationPile[-1].value and cardToPlay.suit == foundationPile[-1].suit:
            return True
        return False


def play(position, deck, piles, i):
    cardToPlay = deck[position[0]]
    cardToPlay.connected = True
    deck.pop(position[0])
    position[0] -= 1
    piles[i].append(cardToPlay)

