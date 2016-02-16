#ifndef ASTROOBJECT_H
#define ASTROOBJECT_H

// Dependencies
#include <iostream>
#include <SFML/Graphics.hpp>
#include <GameObject.h>

// AstroObject
class AstroObject : public GameObject {
	private:
		float radius;
		float mass;
		float force;
		float acceleration;
		float G;
		sf::Vector2f velocity;
		sf::Vector2f direction;
		sf::Color colour;
		sf::CircleShape circle;
	public:
		AstroObject(double x, double y, float _radius, sf::Color _colour);
		AstroObject();
		virtual void update() = 0;
		virtual void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
		sf::Color getColour();
		float getRadius();
		float getMass();
		float getForce();
		float getG();
		sf::Vector2f getVelocity();
		void setForce(float _force);
		void setAcceleration(float _acceleration);
		void addVelocity(float x, float y);
		sf::Vector2f getDirection();
		void setDirection(float x, float y);
};

#endif