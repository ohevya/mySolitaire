import tkinter as tk
import ttkbootstrap as ttk
from PIL import Image, ImageTk
import game


class Display(ttk.Window):
    def __init__(self, foundationPiles, piles, position, deck):
        super().__init__()
        ttk.Style("solar")
        self.title("solitaire display")
        self.geometry("800x1000")

        ttk.Label(self, text="Solitaire Game Display", font=("Arial", 24)).pack()

        self.self, self.foundationPiles = self, foundationPiles


        self.foundationPilesW = FoundationPiles(foundationPiles, self)
        self.foundationPilesW.pack()
        self.pilesW = Piles(piles, self)
        self.hand = Hand(piles, position, deck, self)
        self.options = Play_Options(self, position, deck, piles)

        self.mainloop()

class FoundationPiles(ttk.Frame):
    def __init__(self, foundationPiles, parent):
        super().__init__(parent)

        self.piles = [ttk.Label(self) for _ in range(4)]
        self.update_foundations(foundationPiles)
        
    
    def update_foundations(self, foundationPiles):
        global fou
        fou = [None] * 4

        for i in range(4):
            if len(foundationPiles[i]) == 1:
                fou[i] = resizeImage("images/empty.png")
            else:
                fou[i] = resizeImage(foundationPiles[i][-1].cardPng())
            self.piles[i].configure(image= fou[i])
            self.piles[i].grid(row=0, column= i)


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

        self.piles, self.position, self.deck, self.parent = piles, position, deck, parent
        

        ttk.Button(self, text= "play", command= lambda: self.play_press()).pack(side="left", padx= 5)

        self.card_label = ttk.Label(self, text= "none", compound="top")
        self.card_label.pack(side="left", padx= 5)

        ttk.Button(self, text= "flip", command= lambda: self.flip_press()).pack(side="left", padx= 5)


        self.pack()
        
    def update_card(self, extra= None):
        global card

        if extra:
            card_status = extra
            card = resizeImage("images/deck_flipped.png")
        else:
            if self.deck[self.position[0]].face_up:
                card = resizeImage(self.deck[self.position[0]].cardPng())
            else:
                card = resizeImage("images/card_back.png")

            if True in game.can_play(self.position, self.deck, self.piles, self.parent.foundationPiles):
                card_status = "can play"
            else:
                card_status = "can't play"

        self.card_label.configure(text=card_status, image= card)

    def flip_press(self):
        extra = game.flip(self.position, self.deck)
        self.update_card(extra)

    def play_press(self):
        foundationPiles = self.parent.foundationPiles
        playable = game.can_play(self.position, self.deck, self.piles, foundationPiles)
        if len(playable) == 4:
            i = playable.index(True)
            game.play(self.position, self.deck, foundationPiles, i)
            self.parent.foundationPilesW.update_foundations(foundationPiles)
            self.parent.hand.update_card()

        elif True in playable:
            for i, b in enumerate(self.parent.options.buttons):
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
        self.parent.hand.update_card()
        self.parent.pilesW.update_piles()

def resizeImage(path):
    card = Image.open(path)
    card = card.resize((80,120))

    global img
    img = ImageTk.PhotoImage(card)
    return img
