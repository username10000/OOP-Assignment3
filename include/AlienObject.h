#ifndef ALIENOBJECT_H
#define ALIENOBJECT_H

// Dependencies
#include <Planet.h>

// Alien Object
class AlienObject : public Planet {
	public:
		AlienObject(double x, double y, float _radius, sf::Color _colour, float _rotation);
		AlienObject();
};

#endif