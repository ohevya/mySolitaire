#include "Deck.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1920u, 1000u }), "Demo");
	Deck deck(DRAW_THREE);
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (event->is<sf::Event::MouseButtonReleased>())
				deck.mouseRelesed(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				
		}

		deck.update(window);

		window.clear(sf::Color(24, 120, 48));

		deck.render(window);

		window.display();
	}

	return 0;
}