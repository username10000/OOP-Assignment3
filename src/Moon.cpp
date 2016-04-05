#include <Moon.h>

Moon::Moon(double x, double y, float _radius, sf::Color _colour, float _rotation) : Planet(x, y, _radius, _colour, _rotation) {
	setMass(getRadius() * 9.3 / 5);
}