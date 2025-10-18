import tkinter as tk
import ttkbootstrap as ttk
import game

class Display(ttk.Window):
    def __init__(self, foundationPiles, piles, position, deck):
        super().__init__()
        self.title("solitaire display")
        self.geometry("800x1000")

        ttk.Label(self, text="Solitaire Game Display", font=("Arial", 24)).pack()


        self.foundationPiles = FoundationPiles(foundationPiles, self)
        self.pilesW = Piles(piles, self)
        self.hand = Hand(position, deck, self)
        # self.played = Played(played, self)

        self.mainloop()

class FoundationPiles(ttk.Frame):
    def __init__(self, foundationPiles, parent):
        super().__init__(parent)

        piles = [ttk.Label(self) for _ in range(4)]

        for i in range(4):
            try:
                piles[i].configure("text", foundationPiles[i][-1].card_info()[:-1])
            except IndexError:
                piles[i]["text"] = "None"
            piles[i].pack(side="left", padx=10, pady=5)
        self.pack()

class Piles(ttk.Frame):
    def __init__(self, piles, parent):
        super().__init__(parent)

        pilesW = [tk.Text(self) for _ in range(7)]

        for i in range(7):
            pilesW[i].insert("1.0", f"Pile {i+1}:\n")
            for card in piles[i]:
                if card.face_up:
                    pilesW[i].insert("end", f"{card.card_info()[:-1]}\n")
                else:
                    pilesW[i].insert("end", "##\n")
            pilesW[i].configure(width=5, height=20)
            pilesW[i].pack(side="left", padx=5, pady=5)
        self.pack()


class Hand(ttk.Frame):
    def __init__(self, position, deck, parent):
        super().__init__(parent)

        ttk.Button(self, text= "play", command= lambda: self.play_press(position, deck, played)).pack(side="left")

        self.card_label = ttk.Label(self, text= "start")
        self.card_label.pack(side="left")

        ttk.Button(self, text= "flip", command= lambda: self.flip_press(position, deck)).pack(side="left")

        self.pack()
    def update_card(self, position, deck):

        if position[0] != -1:
            card = deck[position[0]].card_info()
        else:
            card = "none"

        self.card_label["text"] = card

    def play_press(self, position, deck, played):

        game.play(position, deck, played)
        self.update_card(position, deck)
        
    def flip_press(self, position, deck):
        game.flip(position, deck)
        self.update_card(position, deck)


# class Played(tk.Text):
#     def __init__(self, played, parent):
#         super.__init__(parent)
#         self.played.text()

played = []