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
		sf::Texture shipTexture[3];
		sf::Sprite ship[3];
		sf::Vector2<double> velocity;
		sf::Vector2<double> direction;
		float force;
		float acceleration;
		float mass;
		float rotation;
		float angle;
		float speed;
		//float angleToPlanet;
		bool accelerating;
		//bool landed;
		//int planet;
		int spriteNo;
		sf::Clock lastChange;
	public:
		Ship(double x, double y, float screenX, float screenY);
		Ship();
		void addVelocity();
		void addVelocity(double x, double y);
		void subVelocity();
		void resetVelocity();
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
		bool getAccelerating();
		void setAccelerating(bool a);
		float getRadius();
		sf::FloatRect getBoundingBox();
		//bool getLanded();
		//float getAngleToPlanet();
		//void setAngleToPlanet(float t);
		//void setLanded(bool l);
		//int getPlanet();
		//void setPlanet(int p);
		void update();
		void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
};

#endif