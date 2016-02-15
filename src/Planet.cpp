#include <Planet.h>

Planet::Planet(long long x, long long y, float _radius, sf::Color _colour) : AstroObject(x, y, _radius, _colour) {
	circle.setRadius(_radius);
	circle.setPointCount(100);
	circle.setFillColor(_colour);
	addVelocity(2, 0);
}

Planet::Planet() : Planet(0, 0, 100, sf::Color(255, 255, 0)) {
}

void Planet::update() {
	float acceleration = getForce() / getMass();
	sf::Vector2f velocity = getVelocity();
	sf::Vector2f direction = getDirection();
	setAcceleration(acceleration);
	addVelocity(direction.x * acceleration, direction.y * acceleration);
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);
	std::cout << velocity.x << " " << velocity.y << std::endl;
	//std::cout << getDirection().x << " " << getDirection().y << std::endl;
}

/*
void Planet::render(sf::RenderWindow &window, sf::Vector2<long long> view, sf::VideoMode screen) {
	circle.setPosition((screen.width / 2) + (getX() - view.x) - getRadius(), (screen.height / 2) + (getY() - view.y) - getRadius());
	window.draw(circle);
}
*/