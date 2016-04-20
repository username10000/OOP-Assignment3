#ifndef FUEL_H
#define FUEL_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <Functions.h>
#include <UI.h>

// Fuel
class Fuel : public UI {
	private:
		sf::VideoMode screen;
		sf::Font font;
		sf::RectangleShape outerRect, innerRect;
		sf::Text text;
		sf::Color colours[3];
		sf::Mouse mouse;
		float offset;
	public:
		Fuel(sf::VideoMode _screen, sf::Font _font);
		bool getHovered();
		std::string getDescription();
		void update(float percentage);
		void render(sf::RenderWindow &window);
};

#endif