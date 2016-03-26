#ifndef ASTROOBJECT_H
#define ASTROOBJECT_H

// Dependencies
#include <iostream>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <Human.h>
#include <Functions.h>

// AstroObject
class AstroObject : public GameObject {
	private:
		float radius;
		double mass;
		double force;
		float acceleration;
		double G;
		float rotation;
		sf::Vector2<double> velocity;
		sf::Vector2<double> direction;
		sf::Color colour;
		sf::CircleShape circle;
		//sf::Texture texture;
		std::string name;
		bool habitable;
		//std::vector<std::unique_ptr<Human>> locals;
		//sf::Texture humanTexture;
	public:
		AstroObject(double x, double y, float _radius, sf::Color _colour, float _rotation);
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
		std::string getName();
		void setName(std::string);
		void setMass(float m);
		sf::FloatRect getBoundingBox();
		float getRotation();
		bool isHabitable();
		//void setHumanTexture(sf::Texture *hT);
};

#endif