#include <Human.h>

Human::Human(double x, double y) : GameObject(x, y) {
	texture.loadFromFile("human.png");
	sprite.setTexture(texture);
	sprite.setOrigin(10, 20);

	mass = 0.01;
	velocity.x = velocity.y = 0;
	direction.x = direction.y = 0;
	force = 0;
	angle = 0;
}

sf::Vector2<double> Human::getVelocity() {
	return velocity;
}

sf::Vector2<double> Human::getDirection() {
	return direction;
}

float Human::getMass() {
	return mass;
}

float Human::getForce() {
	return force;
}

void Human::addVelocity(double x, double y) {
	velocity.x += x;
	velocity.y += y;
}

void Human::setDirection(double x, double y) {
	direction.x = x;
	direction.y = y;
}

void Human::setForce(float f) {
	force = f;
}

void Human::resetVelocity() {
	velocity.x = velocity.y = 0;
}

void Human::setAngle(float a) {
	angle = a;
}

void Human::update() {
	// Apply Force
	float acceleration = getForce() / getMass();
	sf::Vector2<double> direction = getDirection();
	addVelocity(direction.x * acceleration, direction.y * acceleration);
	sf::Vector2<double> velocity = getVelocity();
	setOldX(getX());
	setOldY(getY());
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);
}

void Human::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	sprite.setRotation(angle);
	sprite.setScale((double)0.07 / ppm, (double)0.07 / ppm);
	sprite.setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
	window.draw(sprite);
}