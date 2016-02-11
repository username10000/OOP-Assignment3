#ifndef GAME_H
#define GAME_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <GameObject.h>

// Game
class Game {
	private:
		sf::RenderWindow window;
		sf::VideoMode screen;
		sf::ContextSettings settings;
		sf::Font font;
		int keys[512] = { 0 };
		int stop;
	public:
		Game();
		~Game();
		void events();
		int getStop();
		void update();
		void render();
};


#endif