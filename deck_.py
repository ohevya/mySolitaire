import random

class Card:
    def __init__(self, value, suit, face_up=True, connected=False):
        self.value = value
        self.suit = suit
        self.color = "red" if suit in ("hearts", "diamonds") else "black"
        self.cardStr = lambda : f"{self.value}{suitSwitch(self.suit)}"
        self.cardPng = lambda : f"images/{self.value}_of_{self.suit}.png"
        self.face_up = face_up
        self.connected = connected
    def card_Back(self):
        return "images/card_back.png"


Picture_cards = {
    1 : 'ace', 11 : 'jack', 12 : 'queen', 13 : 'king',
    'ace' : 1, 'jack' : 11, 'queen' : 12,'king' : 13
}

def valueSwitch(value):
    if value in Picture_cards:
        return Picture_cards[value]
    return value

def suitSwitch(value):
    suits = {
    "hearts" : '♥', "diamonds" : '♦' , "clubs" : '♣', "spades" : '♠'
    }
    if value in suits:
        return suits[value]
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
