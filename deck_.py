import random

class Card:
    def __init__(self, value, suit, face_up=True):
        self.value = value
        self.suit = suit
        self.face_up = face_up

    def card_info(self):
        face = "D"
        if self.face_up: face = "U"

        return f"{self.value}{self.suit}{face}"
    
    def print_card(self):
        print(f"{self.value}{self.suit}", end=" ")


Picture_cards = {
    1 : 'A', 11 : 'J', 12 : 'Q', 13 : 'K',
    'A' : 1, 'J' : 11, 'Q' : 12,'K' : 13
}



def generate_cards(values, suits):
    cards = []
    for suit in suits:
        for value in values:

            if value in Picture_cards:
                card_value = Picture_cards[value]
            else:
                card_value = value
            cards.append(Card(card_value, suit))
    return cards


def shuffle_deck(deck):
    for card in deck:
        card.face_up = random.choice((True,False))
    random.shuffle(deck)



def create_deck():
    values = set(range(1,14))
    suits = ("♣", "♦", "♠", "♥")

    deck = generate_cards(values, suits)

    shuffle_deck(deck)

    return deck
