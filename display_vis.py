
import tkinter as tk
import ttkbootstrap as ttk
from deck_ import Card


def piles_dis(piles, frame):
    piles_windows = [tk.Text(master=frame) for _ in range(7)]
    

    for i in range(7):
        piles_windows[i].insert("1.0", f"Pile {i+1}:\n")
        for card in piles[i]:
            if card.face_up:
                piles_windows[i].insert("end", f"{card.card_info()[:-1]}\n")
            else:
                piles_windows[i].insert("end", "##\n")
    return piles_windows


def foundationPiles_dis(foundationPiles, frame):
    piles_win = [ttk.Label(master=frame) for _ in range(4)]
    for i in range(4):
        try:
            piles_win[i].configure("text", foundationPiles[i][-1].card_info()[:-1])
        except IndexError:
            piles_win[i]["text"] = "None"
    return piles_win

def board_dis(foundationPiles, piles, frame1, frame2, window, deck, position):

    if position[0] != -1:
        strVar.set(deck[position[0]].card_info())

    return foundationPiles_dis(foundationPiles, frame1), piles_dis(piles, frame2)






# main loop

def main_loop(foundationPiles, piles, position, deck):


    window = ttk.Window(themename="vapor")
    window.title("solitaire display")
    window.geometry("800x1000")

    label = ttk.Label(master=window, text="Solitaire Game Display", font=("Arial", 24))

    frame1 = ttk.Frame(master=window)
    frame2 = ttk.Frame(master=window)


    strVar = tk.StringVar(value= "Hand")
    
    hand = ttk.Label(master= window, textvariable= strVar)

    foundationPiles_pack, piles_pack = board_dis(foundationPiles, piles, frame1, frame2, window, deck, position)

    label.pack()

    for pile in foundationPiles_pack:
        pile.pack(side="left", padx=10, pady=5)
    frame1.pack()

    for pile in piles_pack: 
        pile.configure(width=5, height=20)
        pile.pack(side="left", padx=5, pady=5)
    frame2.pack()
    
    hand.pack()

   

    window.mainloop()
