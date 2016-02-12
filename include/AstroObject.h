#ifndef ASTROOBJECT_H
#define ASTROOBJECT_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <GameObject.h>

// AstroObject
class AstroObject : public GameObject {
	private:
		float radius;
		float mass;
		sf::Color colour;
	public:
		AstroObject(float x, float y, float _radius, sf::Color _colour);
		AstroObject();
		virtual void update() = 0;
		virtual void render(sf::RenderWindow &window) = 0;
		//virtual void getShape();
		sf::Color getColour();
		float getRadius();
};

#endif