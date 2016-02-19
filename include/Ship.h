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
		float rotation;
		float angle;
		float speed;
	public:
		Ship(double x, double y, float screenX, float screenY);
		Ship();
		void addVelocity();
		void subVelocity();
		sf::Vector2f getVelocity();
		void addRotation(float x);
		void resetRotation();
		void setSpeed(float s);
		void update();
		void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
};

#endif