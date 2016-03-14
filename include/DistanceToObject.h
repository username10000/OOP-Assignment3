#ifndef DISTANCETOOBJECT_H
#define DISTANCETOOBJECT_H

// Dependencies
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

// Distance To Planet
class DistanceToObject {
	private:
		sf::VideoMode screen;
		sf::CircleShape circle;
		sf::CircleShape innerCircle;
		sf::Font font;
		sf::Text distanceText;
		sf::Vertex line[2];
		float size;
		float offset;
		float angle;
		float distance;
	public:
		DistanceToObject(sf::VideoMode _screen, sf::Font _font);
		void update(float _angle, float _distance);
		void render(sf::RenderWindow &window);
};

#endif