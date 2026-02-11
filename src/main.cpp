#include "Game.h"


int main(){
	sf::RenderWindow window(sf::VideoMode({ 1920u, 1000u }), "Demo");
	Game game(DRAW_ONE);
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (event->is<sf::Event::MouseButtonReleased>())
				game.mouseReleased(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				
		}

		game.update(window);

		window.clear(sf::Color(24, 120, 48));

		game.render(window);

		window.display();
	}

	return 0;
}