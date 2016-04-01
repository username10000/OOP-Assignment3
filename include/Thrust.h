#ifndef THRUST_H
#define THRUST_H

// Dependencies
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Functions.h>

// Thrust
class Thrust {
	private:
		sf::VideoMode screen;
		sf::Font font;
		sf::RectangleShape rect;
		sf::Text name;
		sf::Text left, right;
		sf::CircleShape indicator;
		sf::VertexArray lines;
		float thrustLevel;
		float offset;
	public:
		Thrust(sf::VideoMode _screen, sf::Font _font);
		void update(float percentage);
		void render(sf::RenderWindow &window);
};

#endif