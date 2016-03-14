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
		double mass;
		double force;
		float acceleration;
		double G;
		sf::Vector2<double> velocity;
		sf::Vector2<double> direction;
		sf::Color colour;
		sf::CircleShape circle;
		char name[31];
	public:
		AstroObject(double x, double y, float _radius, sf::Color _colour);
		AstroObject();
		virtual void update() = 0;
		virtual void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
		sf::Color getColour();
		float getRadius();
		double getMass();
		double getForce();
		double getG();
		sf::Vector2<double> getVelocity();
		void setForce(double _force);
		void setAcceleration(float _acceleration);
		void addVelocity(double x, double y);
		sf::Vector2<double> getDirection();
		void setDirection(double x, double y);
		void setName(char n[]);
		void setMass(float m);
		sf::FloatRect getBoundingBox();
};

#endif