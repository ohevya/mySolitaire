from self_dis import Display
from piles import pile_set_up
from deck_ import create_deck

deck = create_deck()
position = [-1]
piles = pile_set_up(deck)
foundationPiles = [[],[],[],[]]

if __name__ == '__main__':
    Display(foundationPiles, piles, position, deck)