#ifndef CONSOLE_H
#define CONSOLE_H

// Dependencies
#include <string>
#include <SFML/Graphics.hpp>

// Console
class Console {
	private:
		sf::Font font;
		sf::RectangleShape inputField;
		sf::Text inputText;
		sf::Vertex line[2];
		sf::Clock lastBlink;
		bool cursor;
	public:
		Console(sf::VideoMode _screen, sf::Font _font);
		void update(std::string input);
		void render(sf::RenderWindow &window);
};

#endif