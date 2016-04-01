#ifndef FUEL_H
#define FUEL_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <Functions.h>

// Fuel
class Fuel {
	private:
		sf::VideoMode screen;
		sf::Font font;
		sf::RectangleShape outerRect, innerRect;
		sf::Text text;
		sf::Color colours[3];
		float offset;
	public:
		Fuel(sf::VideoMode _screen, sf::Font _font);
		void update(float percentage);
		void render(sf::RenderWindow &window);
};

#endif