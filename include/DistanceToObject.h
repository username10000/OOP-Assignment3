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
		sf::Text targetText;
		sf::Vertex line[2];
		sf::Vertex targetLine[2];
		sf::Vertex splitLine[2];
		float size;
		float offset;
		float angle;
		float distance;
		float targetAngle;
		float targetDistance;
	public:
		DistanceToObject(sf::VideoMode _screen, sf::Font _font);
		void setTargetDistance(float d);
		void setTargetAngle(float a);
		void update(float _angle, float _distance);
		void render(sf::RenderWindow &window);
};

#endif