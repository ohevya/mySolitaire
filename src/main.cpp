#include <vector>
#include "Card.h"

#define TIME_FLAG 1000


int main()
{

	int keyTime = TIME_FLAG;
	std::vector<Card*> cardVec;
	//Card* card;

	sf::Texture front;
	sf::Texture back;

	sf::RenderWindow window(sf::VideoMode({ 1920u, 1000u }), "Demo");

	if (back.loadFromFile("../images/card_back.png") && front.loadFromFile("../images/1_of_clubs.png"))
		std::cout << "Textures loaded!" << "\n";
	else
		std::cout << "Could not load textures" << "\n";

	//card = new Card(mousePosView, front, back);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (event->is<sf::Event::MouseLeft>())
			{
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

				for (Card* card : cardVec)
					if (card->inClick(mousePos))
					{
						card->flipCard();
						
					}
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) && keyTime >= TIME_FLAG)
		{
			sf::Vector2f mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			cardVec.push_back(new Card(mousePosView, front, back));
			keyTime = 0;
		}

		for(Card* card : cardVec)
			card->update(window);

		if (keyTime < TIME_FLAG)
			keyTime++;


		window.clear();
		for (Card* card : cardVec)
			card->render(window);

		window.display();
	}
	for (Card* card : cardVec)
	delete card;


	return 0;
}