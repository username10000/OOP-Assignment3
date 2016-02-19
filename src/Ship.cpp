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
	speed = 0.1;
}

Ship::Ship() : Ship(0, 0, 0, 0) {

}

void Ship::addVelocity() {
	velocity.x += sin(angle * PI / 180) * speed;
	velocity.y += -cos(angle * PI / 180) * speed;
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

void Ship::update() {
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);
	
	sprite.rotate(rotation);
	angle += rotation;

	if (angle >= 360)
		angle -= 360;
	if (angle <= -360)
		angle += 360;
}

void Ship::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	sprite.setScale(1 / ppm, 1 / ppm);
	window.draw(sprite);
}