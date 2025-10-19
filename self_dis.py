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
        self.options = Play_Options(self, position, deck, piles)

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
                    pile.insert("end", f"{card.card_info()[:-1]}\n")
                else:
                    pile.insert("end", "##\n") 
            pile.configure(width=5, height=20)
            pile.pack(side="left", padx=5, pady=5)     



class Hand(ttk.Frame):
    def __init__(self, position, deck, parent):
        super().__init__(parent)

        self.position, self.deck, self.parent, self.self = position, deck, parent, self
        

        ttk.Button(self, text= "play", command= lambda: self.play_press()).pack(side="left", padx= 5)

        self.card_label = ttk.Label(self, text= "none")
        self.card_label.pack(side="left", padx= 5)

        ttk.Button(self, text= "flip", command= lambda: self.flip_press()).pack(side="left", padx= 5)


        self.pack()
        
    def update_card(self, extra= None):

        if self.position[0] != -1 and game.can_play(self.position, self.deck):
            card = f"{self.deck[self.position[0]].card_info()[:-1]}\n can play"
        elif extra:
            card = extra
        else:
            card = "##\n can't play"

        self.card_label["text"] = f"{card}"

    def flip_press(self):
        extra = game.flip(self.position, self.deck)
        self.update_card(extra)

    def play_press(self):
        if game.can_play(self.position, self.deck):
            self.parent.options.pack()


class Play_Options(ttk.Frame):
    def __init__(self , parent, position, deck, piles):
        super().__init__(parent)

        self.position, self.deck, self.piles, self.parent = position, deck, piles, parent
        
        self.buttons = [ttk.Button(self, text= f"piles {i + 1}", command= lambda i=i: self.button_press(i)) for i in range(7)]
        for b in self.buttons:
            b.pack(side= "left" , padx = 5 , pady= 10)
    def button_press(self, i):
        game.play(self.position, self.deck, self.piles, i)
        self.parent.options.pack_forget()
        self.parent.hand.self.update_card()
        self.parent.pilesW.self.update_piles()
