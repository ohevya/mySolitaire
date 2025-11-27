from PIL import Image, ImageTk


class Card:
    def __init__(self, value, suit, face_up=True, connected=False):
        self.value = value
        self.suit = suit
        self.color = "red" if suit in ("hearts", "diamonds") else "black"

        self.cardStr = lambda: f"{self.value}{suitSwitch(self.suit)}"
        self.cardPngPath = f"images/{self.value}_of_{self.suit}.png"

        self.face_up = face_up
        self.connected = connected

        # Preload both images
        self._front_image = None
        self._back_image = None

    def card_Back(self):
        return "images/card_back.png"

    def get_front(self):
        if self._front_image is None:
            self._front_image = resizeImage(self.cardPngPath)
        return self._front_image

    def get_back(self):
        if self._back_image is None:
            self._back_image = resizeImage(self.card_Back())
        return self._back_image

    def get_image(self):
        return self.get_front() if self.face_up else self.get_back()





Picture_cards = {
    1 : 'ace', 11 : 'jack', 12 : 'queen', 13 : 'king',
    'ace' : 1, 'jack' : 11, 'queen' : 12,'king' : 13
}

def valueSwitch(value):
    if value in Picture_cards:
        return Picture_cards[value]
    return value


def suitSwitch(value):
    suits = {
    "hearts" : '♥', "diamonds" : '♦' , "clubs" : '♣', "spades" : '♠'
    }
    if value in suits:
        return suits[value]
    return value

def resizeImage(path):

    card = Image.open(path)
    card = card.resize((80,120))
    #global img

    img = ImageTk.PhotoImage(card)
    return img