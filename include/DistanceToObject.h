#ifndef DISTANCETOOBJECT_H
#define DISTANCETOOBJECT_H

// Dependencies
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>

// Distance To Planet
class DistanceToObject {
	private:
		sf::VideoMode screen;
		sf::CircleShape circle;
		sf::CircleShape innerCircle;
		sf::CircleShape shipDirection;
		sf::Font font;
		sf::Text distanceText;
		sf::Text targetText;
		sf::Text closestName;
		sf::Text targetName;
		sf::Vertex line[2];
		sf::Vertex targetLine[2];
		sf::Vertex splitLine[2];
		float size;
		float offset;
		float angle;
		float shipAngle;
		float distance;
		float targetAngle;
		float targetDistance;
	public:
		DistanceToObject(sf::VideoMode _screen, sf::Font _font);
		void setTargetDistance(float d);
		void setTargetAngle(float a);
		void setTargetName(std::string n);
		void update(float _angle, float _distance, std::string _name, float _shipAngle);
		void render(sf::RenderWindow &window);
};

#endif