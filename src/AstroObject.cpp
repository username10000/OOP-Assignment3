#include <AstroObject.h>

AstroObject::AstroObject(long long x, long long y, float _radius, sf::Color _colour) : GameObject(x, y) {
	radius = _radius;
	_colour = colour;
	mass = (float)(_radius * 9.3);
	force = acceleration = velocity.x = velocity.y = 0;
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

float AstroObject::getMass() {
	return mass;
}

float AstroObject::getForce() {
	return force;
}

sf::Vector2f AstroObject::getVelocity() {
	return velocity;
}

void AstroObject::setForce(float _force) {
	force = _force;
}

void AstroObject::setAcceleration(float _acceleration) {
	acceleration = _acceleration;
}

void AstroObject::addVelocity(float x, float y) {
	velocity.x += x;
	velocity.y += y;
}