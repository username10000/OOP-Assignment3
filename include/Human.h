#ifndef HUMAN_H
#define HUMAN_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <GameObject.h>

// Human
class Human : public GameObject {
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		sf::Vector2<double> velocity;
		sf::Vector2<double> direction;
		float force;
		float mass;
		float angle;
	public:
		Human(double x, double y);
		sf::Vector2<double> getVelocity();
		sf::Vector2<double> getDirection();
		float getMass();
		float getForce();
		void addVelocity(double x, double y);
		void setDirection(double x, double y);
		void setForce(float f);
		void resetVelocity();
		void setAngle(float a);
		void update();
		void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
};

#endif