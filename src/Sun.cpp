#include <Sun.h>

Sun::Sun(double x, double y, float _radius, sf::Color _colour, float _rotation) : AstroObject(x, y, _radius, _colour, _rotation) {
	setMass(_radius * 9.3 * 30);
	setHabitable(false);
	//circle.setRadius(_radius);
	//circle.setPointCount(100);
	//circle.setFillColor(_colour);
}

Sun::Sun() : Sun(0, 0, 100, sf::Color(255, 255, 0), 0) {
}

void Sun::update() {

	//circle.setPosition(x - getRadius(), y - getRadius());
}

//void Sun::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen) {
	//circle.setPosition((screen.width / 2) + (getX() - view.x) - getRadius(), (screen.height / 2) + (getY() - view.y) - getRadius());
	//window.draw(circle);
//}