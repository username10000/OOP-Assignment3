#include <Ship.h>

Ship::Ship(double x, double y, float screenX, float screenY) : GameObject(x, y) {
	texture.loadFromFile("E3.png");
	sprite.setTexture(texture);
	//setScreenPosition(screenX, screenY);
	sprite.setPosition(screenX - 20, screenY - 20);
	sprite.setOrigin(20, 20);
	//sprite.setScale(sf::Vector2f(10.0f, 10.0f));
	
	velocity.x = velocity.y = 0;
	rotation = angle = 0;
	force = acceleration = 0;
	direction.x = direction.y = 0;
	mass = 40 * 9.3;
	speed = 0.5;
}

Ship::Ship() : Ship(0, 0, 0, 0) {

}

void Ship::addVelocity() {
	velocity.x += sin(angle * PI / 180) * speed;
	velocity.y += -cos(angle * PI / 180) * speed;
}

void Ship::addVelocity(float x, float y) {
	velocity.x += x;
	velocity.y += y;
}

void Ship::subVelocity() {
	velocity.x -= sin(angle * PI / 180) * speed;
	velocity.y -= -cos(angle * PI / 180) * speed;
}

sf::Vector2f Ship::getVelocity() {
	return velocity;
}

void Ship::addRotation(float x) {
	rotation += x;
}

void Ship::resetRotation() {
	rotation = 0;
}

void Ship::setSpeed(float s) {
	speed = s;
}

float Ship::getMass() {
	return mass;
}

float Ship::getForce() {
	return force;
}

void Ship::setForce(float f) {
	force = f;
}

void Ship::addForce(float f) {
	force += f;
}

sf::Vector2f Ship::getDirection() {
	return direction;
}

void Ship::setDirection(float x, float y) {
	direction.x = x;
	direction.y = y;

	/*
	if (direction.x > 1)
		direction.x = 1;
	if (direction.x < -1)
		direction.x = -1;
	if (direction.y > 1)
		direction.y = 1;
	if (direction.y < -1)
		direction.y = -1;
	*/
}

void Ship::update() {
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);
	
	sprite.rotate(rotation);
	angle += rotation;

	if (angle >= 360)
		angle -= 360;
	if (angle <= -360)
		angle += 360;

	
	// Force
	float acceleration = getForce() / getMass();
	sf::Vector2f direction = getDirection();
	//setAcceleration(acceleration);
	addVelocity(direction.x * acceleration, direction.y * acceleration);
	sf::Vector2f velocity = getVelocity();
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);
	
}

void Ship::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	sprite.setScale(1 / ppm, 1 / ppm);
	window.draw(sprite);
}