from deck_ import Card

def print_piles(piles):
    for i, pile in enumerate(piles, 1):
        print(f"\npile {i}: ", end =" " )
        for card in pile:
            if card.face_up:
                card.print_card()
            else: print("##", end =" ")
    print("\n")


def print_deck(deck):
    list_ = []
    for card in deck:
        list_.append(card.card_info())
    for i in range(0, len(list_), 3):
        print(f"{list_[i]}, {list_[i+1]}, {list_[i+2]}")


def print_played(played):
    for card in played:
        card.print_card()
    print("\n")

def print_foundationPiles(foundationPiles):
    for pile in foundationPiles:
        try:
            pile[-1].print_card()
        except IndexError:
            print("None" , end = " ")
        print(end= "    ")
    print("\n")



def print_board(foundationPiles, piles, position, deck):
    print_foundationPiles(foundationPiles)
    print_piles(piles)

    if position[0] != -1:
        print(f"Card:fghj ", end=""), deck[position[0]].print_card()



    

