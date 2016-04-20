#ifndef DISTANCETOOBJECT_H
#define DISTANCETOOBJECT_H

// Dependencies
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <Functions.h>
#include <UI.h>

// Distance To Planet
class DistanceToObject : public UI {
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
		sf::Mouse mouse;
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
		float getTargetAngle();
		bool getHovered();
		std::string getDescription();
		void update(float _angle, float _distance, std::string _name, float _shipAngle);
		void render(sf::RenderWindow &window);
};

#endif