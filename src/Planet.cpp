#include <Planet.h>

Planet::Planet(long long x, long long y, float _radius, sf::Color _colour) : AstroObject(x, y, _radius, _colour) {
	circle.setRadius(_radius);
	circle.setPointCount(100);
	circle.setFillColor(_colour);
}

Planet::Planet() : Planet(0, 0, 100, sf::Color(255, 255, 0)) {
}

void Planet::update() {
	float acceleration = getForce() / getMass();
	sf::Vector2f velocity = getVelocity();
	setAcceleration(acceleration);
	addVelocity(acceleration, acceleration);
	setX(getX() + 1);
	setY(getY() + 1);
	//std::cout << velocity.x << " " << velocity.y << std::endl;
}

/*
void Planet::render(sf::RenderWindow &window, sf::Vector2<long long> view, sf::VideoMode screen) {
	circle.setPosition((screen.width / 2) + (getX() - view.x) - getRadius(), (screen.height / 2) + (getY() - view.y) - getRadius());
	window.draw(circle);
}
*/