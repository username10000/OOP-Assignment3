#ifndef MESSAGE_H
#define MESSAGE_H

// Dependencies
#include <SFML/Graphics.hpp>

// Message
class Message {
	private:
		sf::RectangleShape background;
		sf::Text text;
		sf::Font font;
		bool isVisible;
	public:
		Message(sf::VideoMode _screen, sf::Font _font);
		void show();
		void hide();
		bool getIsVisible();
		void update(std::string string);
		void update(std::string string, sf::Color colour);
		void render(sf::RenderWindow &window);
};

#endif