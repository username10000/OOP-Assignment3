#include <VelocityVector.h>

VelocityVector::VelocityVector(sf::VideoMode _screen) {
	screen = _screen;

	size = screen.height / 10;
	offset = 10;
	
	rectangle.setPosition(screen.width - size - offset, screen.height - size - offset);
	rectangle.setSize(sf::Vector2f(size, size));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color::White);
	
	line[0] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset, screen.height - size / 2 - offset));
	line[1] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset, screen.height - size / 2 - offset));
}

void VelocityVector::update(sf::Vector2f velocity) {
	float x, y;
	line[1] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset + velocity.x, screen.height - size / 2 - offset + velocity.y));
}

void VelocityVector::render(sf::RenderWindow &window) {
	window.draw(rectangle);
	window.draw(line, 2, sf::Lines);
}