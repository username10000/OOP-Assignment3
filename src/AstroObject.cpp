#include <AstroObject.h>

AstroObject::AstroObject(double x, double y, float _radius, sf::Color _colour, float _rotation) : GameObject(x, y) {
	//texture.loadFromFile("grass2.png");
	//texture.setRepeated(true);
	radius = _radius;
	colour = _colour;
	mass = (float)(_radius * 9.3);
	force = velocity.x = velocity.y = 0;
	acceleration = 0;
	circle.setRadius(_radius);
	circle.setOrigin(_radius, _radius);
	circle.setPointCount(200);
	//circle.setTexture(&texture);
	circle.setFillColor(colour);
	direction.x = 1;
	direction.y = 1;
	G = 0.667;
	name = "OBJECT";
	rotation = _rotation;
	//strcpy(name, "");
}

AstroObject::AstroObject() : AstroObject(0, 0, 100, sf::Color(255, 255, 0), 0.01) {
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

std::string AstroObject::getName() {
	return name;
}

void AstroObject::setName(std::string n) {
	name = n;
}

void AstroObject::setMass(float m) {
	mass = m;
}

sf::FloatRect AstroObject::getBoundingBox() {
	return circle.getGlobalBounds();
}

float AstroObject::getRotation() {
	return rotation;
}

void AstroObject::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	circle.setRadius(getRadius() / (double)ppm);
	circle.setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.rotate(rotation);
	//std::cout << sqrt(pow(circle.getPosition().x + circle.getRadius() - screen.width / 2, 2) + pow(circle.getPosition().y + circle.getRadius() - screen.height / 2, 2)) << std::endl;
	//std::cout << circle.getPosition().x << " " << circle.getPosition().y << std::endl;
	//circle.setScale(getRadius() / ppm, getRadius() / ppm);
	window.draw(circle);
}