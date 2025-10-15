from deck_ import Card

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