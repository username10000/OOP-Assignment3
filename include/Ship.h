#ifndef SHIP_H
#define SHIP_H
#define PI 3.14159

// Dependencies
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <cmath>

// Ship
class Ship : public GameObject {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2f velocity;
		sf::Vector2f direction;
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
		void addVelocity(float x, float y);
		void subVelocity();
		sf::Vector2f getVelocity();
		void addRotation(float x);
		void resetRotation();
		void setSpeed(float s);
		float getMass();
		float getForce();
		void setForce(float f);
		void addForce(float f);
		sf::Vector2f getDirection();
		void setDirection(float x, float y);
		void update();
		void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
};

#endif