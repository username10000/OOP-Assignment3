#ifndef THRUST_H
#define THRUST_H

// Dependencies
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Functions.h>
#include <UI.h>

// Thrust
class Thrust : public UI {
	private:
		sf::VideoMode screen;
		sf::Font font;
		sf::RectangleShape rect;
		sf::Text name;
		sf::Text left, right;
		sf::CircleShape indicator;
		sf::VertexArray lines;
		sf::Mouse mouse;
		float thrustLevel;
		float offset;
	public:
		Thrust(sf::VideoMode _screen, sf::Font _font);
		bool getHovered();
		std::string getDescription();
		void update(float percentage);
		void render(sf::RenderWindow &window);
};

#endif