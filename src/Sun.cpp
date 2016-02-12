#include <Sun.h>

Sun::Sun(float x, float y, float _radius, sf::Color _colour) : AstroObject(x, y, _radius, _colour) {
	//sf::CircleShape circle(50);
	circle.setRadius(_radius);
	circle.setPosition(x - _radius, y - _radius);
	circle.setPointCount(50);
	circle.setFillColor(_colour);
}

Sun::Sun() : Sun(0, 0, 100, sf::Color(255, 255, 0)) {
}

void Sun::update() {

}

void Sun::render(sf::RenderWindow &window) {
	window.draw(circle);
}