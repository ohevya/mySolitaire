from self_dis import Display
from deck_ import create_deck, pile_set_up

deck = create_deck()
position = [-1]
piles = pile_set_up(deck)
foundationPiles = [[],[],[],[]]

if __name__ == '__main__':
    Display(foundationPiles, piles, position, deck)