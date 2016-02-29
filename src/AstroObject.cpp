#include <AstroObject.h>

AstroObject::AstroObject(double x, double y, float _radius, sf::Color _colour) : GameObject(x, y) {
	radius = _radius;
	colour = _colour;
	mass = (float)(_radius * 9.3);
	force = velocity.x = velocity.y = 0;
	acceleration = 0;
	circle.setRadius(_radius);
	circle.setPointCount(50);
	circle.setFillColor(colour);
	direction.x = 1;
	direction.y = 1;
	G = 0.667;
	strcpy(name, "");
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

double AstroObject::getMass() {
	return mass;
}

double AstroObject::getForce() {
	return force;
}

sf::Vector2<double> AstroObject::getVelocity() {
	return velocity;
}

double AstroObject::getG() {
	return G;
}

void AstroObject::setForce(double _force) {
	force = _force;
}

void AstroObject::setAcceleration(float _acceleration) {
	acceleration = _acceleration;
}

void AstroObject::addVelocity(double x, double y) {
	velocity.x += x;
	velocity.y += y;
}

sf::Vector2<double> AstroObject::getDirection() {
	return direction;
}

void AstroObject::setDirection(double x, double y) {
	direction.x = x;
	direction.y = y;
}

void AstroObject::setName(char n[]) {
	strncpy_s(name, n, 30);
}

void AstroObject::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	circle.setPosition((float)((screen.width / 2) + (getX() - view.x) / ppm - getRadius() / ppm), (float)((screen.height / 2) + (getY() - view.y) / ppm - getRadius() / ppm));
	circle.setRadius(getRadius() / ppm);
	window.draw(circle);
}