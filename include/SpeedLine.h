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
		float slope;
		float yintercept;
		float speed;
		bool up, down;
		bool isAlive;
	public:
		SpeedLine(sf::VideoMode screen, float angle, float speed);
		bool getIsAlive();
		void update();
		void render(sf::RenderWindow &window);
};

#endif