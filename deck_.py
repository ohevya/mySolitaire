import random

class Card:
    def __init__(self, value, suit, face_up=True, connected=False):
        self.value = value
        self.suit = suit
        self.cardStr = lambda : f"{self.value}_of_{self.suit}"
        self.face_up = face_up
        self.connected = connected


Picture_cards = {
    1 : 'A', 11 : 'J', 12 : 'Q', 13 : 'K',
    'A' : 1, 'J' : 11, 'Q' : 12,'K' : 13
}

def valueSwitch(value):
    if value in Picture_cards:
        return Picture_cards[value]
    return value




def generate_cards(values, suits):
    cards = []
    for suit in suits:
        for value in values:
            cards.append(Card(valueSwitch(value), suit))
    return cards


def shuffle_deck(deck):
    for card in deck:
        card.face_up = random.choice((True,False))
    random.shuffle(deck)


def foundationSetup():
    return [[Card(0, '♣')],[Card(0, '♦')],[Card(0, '♠')],[Card(0, '♥')]]

def create_deck():
    values = set(range(1,14))
    suits = ("♣", "♦", "♠", "♥")

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
