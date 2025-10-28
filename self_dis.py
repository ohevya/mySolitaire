import tkinter as tk
import ttkbootstrap as ttk
from tkinter import Canvas, PhotoImage
import game


class Display(ttk.Window):
    def __init__(self, foundationPiles, piles, position, deck):
        super().__init__()
        ttk.Style("solar")
        self.title("solitaire display")
        self.geometry("800x1000")

        ttk.Label(self, text="Solitaire Game Display", font=("Arial", 24)).pack()

        self.foundation, self.self = foundationPiles, self


        self.foundationPiles = FoundationPiles(foundationPiles, self)
        self.pilesW = Piles(piles, self)
        self.hand = Hand(piles, position, deck, self)
        self.options = Play_Options(self, position, deck, piles)

        self.mainloop()

class FoundationPiles(ttk.Frame):
    def __init__(self, foundationPiles, parent):
        super().__init__(parent)

        self.self = self

        self.piles = [ttk.Label(self) for _ in range(4)]
        self.update_foundations(foundationPiles)
        
    
    def update_foundations(self, foundationPiles):
        for i in range(4):
            if len(foundationPiles[i]) == 1:
                self.piles[i].configure(text= "empty")
            else:
                self.piles[i].configure(text= foundationPiles[i][-1].cardStr())
            self.piles[i].pack(side="left", padx=10, pady=5)
        self.pack()


class Piles(ttk.Frame):
    def __init__(self, piles, parent):
        super().__init__(parent)

        self.piles_data, self.self = piles, self


        self.text_piles = [tk.Text(self) for _ in range(7)]
        self.update_piles()

        self.pack()

    def update_piles(self):
        for i, pile in enumerate(self.text_piles):
            pile.delete("1.0", "end")
            pile.insert("1.0", f"Pile {i+1}:\n")
            for card in self.piles_data[i]:
                if card.face_up:
                    pile.insert("end", f"{card.cardStr()}\n")
                else:
                    pile.insert("end", "##\n") 
            pile.configure(width=5, height=20)
            pile.pack(side="left", padx=5, pady=5)     



class Hand(ttk.Frame):
    def __init__(self, piles, position, deck, parent):
        super().__init__(parent)

        self.piles, self.position, self.deck, self.parent, self.self = piles, position, deck, parent, self
        

        ttk.Button(self, text= "play", command= lambda: self.play_press()).pack(side="left", padx= 5)

        self.card_label = ttk.Label(self, text= "none")
        self.card_label.pack(side="left", padx= 5)

        ttk.Button(self, text= "flip", command= lambda: self.flip_press()).pack(side="left", padx= 5)


        self.pack()
        
    def update_card(self, extra= None):
        if self.deck[self.position[0]].face_up:
            card = f"{self.deck[self.position[0]].cardStr()}\n"
        else:
            card = "##\n"

        if True in game.can_play(self.position, self.deck, self.piles, self.parent.self.foundation):
            card += " can play"
        else:
            card += " can't play"

        if extra:
            card = extra

        self.card_label["text"] = f"{card}"

    def flip_press(self):
        extra = game.flip(self.position, self.deck)
        self.update_card(extra)

    def play_press(self):
        foundationPiles = self.parent.foundation
        playable = game.can_play(self.position, self.deck, self.piles, foundationPiles)
        if len(playable) == 4:
            i = playable.index(True)
            game.play(self.position, self.deck, foundationPiles, i)
            self.parent.foundationPiles.self.update_foundations(foundationPiles)
            self.parent.hand.self.update_card()

        elif True in playable:
            for i, b in enumerate(self.parent.options.self.buttons):
                if playable[i]:
                    b.pack(side= "left" , padx = 5 , pady= 10)
            self.parent.options.pack()


class Play_Options(ttk.Frame):
    def __init__(self , parent, position, deck, piles):
        super().__init__(parent)

        self.position, self.deck, self.piles, self.parent, self.self = position, deck, piles, parent, self
        
        self.buttons = [ttk.Button(self, text= f"piles {i + 1}", command= lambda i=i: self.button_press(i)) for i in range(7)]
    def button_press(self, i):
        game.play(self.position, self.deck, self.piles, i)
        for b in  self.buttons:
            b.pack_forget()
        self.parent.options.pack_forget()
        self.parent.hand.self.update_card()
        self.parent.pilesW.self.update_piles()
