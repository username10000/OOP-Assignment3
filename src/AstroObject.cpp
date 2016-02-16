#include <AstroObject.h>

AstroObject::AstroObject(long long x, long long y, float _radius, sf::Color _colour) : GameObject(x, y) {
	radius = _radius;
	colour = _colour;
	mass = (float)(_radius * 9.3);
	force = acceleration = velocity.x = velocity.y = 0;
	circle.setRadius(_radius);
	circle.setPointCount(100);
	circle.setFillColor(colour);
	direction.x = 1;
	direction.y = 1;
	G = 1;
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

float AstroObject::getG() {
	return G;
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

sf::Vector2f AstroObject::getDirection() {
	return direction;
}

void AstroObject::setDirection(float x, float y) {
	direction.x = x;
	direction.y = y;
}

void AstroObject::render(sf::RenderWindow &window, sf::Vector2<long long> view, sf::VideoMode screen, float ppm) {
	circle.setPosition((screen.width / 2) + (getX() - view.x) / ppm - getRadius() / ppm, (screen.height / 2) + (getY() - view.y) / ppm - getRadius() / ppm);
	circle.setRadius(getRadius() / ppm);
	window.draw(circle);
}