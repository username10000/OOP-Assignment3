#ifndef SPEEDLINE_H
#define SPEEDLINE_H

// Dependencies
#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>
#include <Functions.h>

// Speed Line
class SpeedLine {
	private:
		sf::Vector2f position;
		sf::Vector2f direction;
		sf::CircleShape circle;
		float angle;
		float slope;
		float yintercept;
		float speed;
	public:
		SpeedLine(sf::VideoMode screen, float angle);
		void update();
		void render(sf::RenderWindow &window);
};

#endif