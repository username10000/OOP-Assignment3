#include <AstroObject.h>

AstroObject::AstroObject(long long x, long long y, float _radius, sf::Color _colour) : GameObject(x, y) {
	radius = _radius;
	_colour = colour;
	mass = (float)(_radius * 9.3);
}

AstroObject::AstroObject() : AstroObject(0, 0, 100, sf::Color(255, 255, 0)) {
	radius = 100;
	colour = sf::Color(255, 255, 0);
}

sf::Color AstroObject::getColour() {
	return colour;
}

float AstroObject::getRadius() {
	return radius;
}