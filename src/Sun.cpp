#include <Sun.h>

Sun::Sun(long long x, long long y, float _radius, sf::Color _colour) : AstroObject(x, y, _radius, _colour) {
	circle.setRadius(_radius);
	circle.setPointCount(100);
	circle.setFillColor(_colour);
}

Sun::Sun() : Sun(0, 0, 100, sf::Color(255, 255, 0)) {
}

void Sun::update() {

	//circle.setPosition(x - getRadius(), y - getRadius());
}

void Sun::render(sf::RenderWindow &window, sf::Vector2<long long> view, sf::VideoMode screen) {
	circle.setPosition((screen.width / 2) + (getX() - view.x) - getRadius(), (screen.height / 2) + (getY() - view.y) - getRadius());
	window.draw(circle);
}