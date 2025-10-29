import tkinter as tk

import ttkbootstrap as ttk

from PIL import Image, ImageTk
import game



class Display(ttk.Window):

    def __init__(self, foundationPiles, piles, position, deck):
        super().__init__()

        ttk.Style("solitarie")

        self.title("solitaire display")

        self.geometry("800x1000")


        ttk.Label(self, text="Solitaire Game Display", font=("Arial", 24)).pack()


        self.foundationPiles = foundationPiles



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

        self.fou = [None] * 4


        for i in range(4):

            if len(foundationPiles[i]) == 1:

                self.fou[i] = resizeImage("images/empty.png")

            else:

                self.fou[i] = resizeImage(foundationPiles[i][-1].cardPng())

            self.piles[i].configure(image= self.fou[i])

            self.piles[i].grid(row=0, column= i, padx= 20)



class Piles(ttk.Frame):

    def __init__(self, piles, parent):
        super().__init__(parent)

        self.piles_data = piles


        self.frame_piles = [ttk.Frame(self) for _ in range(7)]
        self.update_piles()


        self.pack(pady=(30,0))

    def update_piles(self):
        self.piles_I = []
        
        for i, frame in enumerate(self.frame_piles):

            for w in frame.winfo_children():
                w.destroy()
            
            frame.configure(width=100, height=400)
            frame.pack_propagate(False)


            ttk.Label(frame ,text = f"Pile {i+1}:").pack()

            for j, card in enumerate(self.piles_data[i]):

                if card.face_up:
                    img = resizeImage(card.cardPng())
                else:
                    img = resizeImage("images/card_back.png")
                self.piles_I.append(img)
                

                tk.Button(frame, image= img, width= 80, height= 120).place(x=0, y= j*20)
            frame.pack(side= "left", padx= 10) 




class Hand(ttk.Frame):

    def __init__(self, piles, position, deck, parent):
        super().__init__(parent)

        self.piles, self.position, self.deck, self.parent = piles, position, deck, parent
        
        self.cardImg = resizeImage("images/empty.png")
        self.deckImg = resizeImage(self.deck[self.position[0] + 1].cardPng())

        self.card_label = ttk.Button(self, text= "play", image= self.cardImg, compound="top", command= lambda: self.play_press())
        self.card_label.grid(row=1, column=1000, padx= 500)


        self.deck_label = ttk.Button(self,text="flip", image= self.deckImg, compound="top", command= lambda: self.flip_press())
        self.deck_label.grid(row=0, column= 0)



        self.pack()
        

    def update_card(self, extra= None):

        if extra:
            card_status = extra
            self.cardImg = resizeImage("images/deck_flipped.png")
        else:
            if self.deck[self.position[0]].face_up:

                self.cardImg = resizeImage(self.deck[self.position[0]].cardPng())
            else:
                self.cardImg = resizeImage("images/card_back.png")

            if True in game.can_play(self.position, self.deck, self.piles, self.parent.foundationPiles):
                card_status = "can play"
            else:
                card_status = "can't play"

        if self.position[0] + 1 == len(self.deck):
            self.deckImg = resizeImage("images/deck_flipped.png")
        elif self.deck[self.position[0] + 1].face_up:
            self.deckImg = resizeImage(self.deck[self.position[0] + 1].cardPng())
        else:
            self.deckImg = resizeImage("images/card_back.png")

        self.card_label.configure(text=card_status, image= self.cardImg)
        self.deck_label.configure(image= self.deckImg)


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


        self.position, self.deck, self.piles, self.parent = position, deck, piles, parent
        

        self.buttons = [ttk.Button(self, text= f"piles {i + 1}", bootstyle= "info", command= lambda i=i: self.button_press(i)) for i in range(7)]

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
    #global img

    img = ImageTk.PhotoImage(card)
    return img

