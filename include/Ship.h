#ifndef SHIP_H
#define SHIP_H
#define PI 3.14159

// Dependencies
#include <iostream>
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <cmath>

// Ship
class Ship : public GameObject {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2<double> velocity;
		sf::Vector2<double> direction;
		float force;
		float acceleration;
		float mass;
		float rotation;
		float angle;
		float speed;
	public:
		Ship(double x, double y, float screenX, float screenY);
		Ship();
		void addVelocity();
		void addVelocity(double x, double y);
		void subVelocity();
		sf::Vector2<double> getVelocity();
		void addRotation(float x);
		void resetRotation();
		void setSpeed(float s);
		float getMass();
		float getForce();
		void setForce(double f);
		void addForce(double f);
		sf::Vector2<double> getDirection();
		void setDirection(double x, double y);
		void update();
		void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
};

#endif