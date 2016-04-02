#ifndef COMMONOBJECT_H
#define COMMONOBJECT_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <Functions.h>

// Common Object
class CommonObject : public GameObject {
	private:
		sf::Sprite sprite;
		sf::Vector2<double> dimension;
		sf::Vector2<double> middleObject;
		sf::Color colour;
		float radius;
		float angle;
		float rotAngle;
		float scale;
	public:
		CommonObject(sf::Texture *texture, sf::Color col, float sA, float rA, float r);
		void setScale(float s);
		void setTextureRect(sf::IntRect tR);
		float getAngle();
		bool isTree();
		void update();
		void update(double mX, double mY);
		void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm);
};

#endif