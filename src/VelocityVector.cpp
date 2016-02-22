#include <VelocityVector.h>

VelocityVector::VelocityVector(sf::VideoMode _screen) {
	screen = _screen;

	size = screen.height / 5;
	offset = 10;

	speed = 0;
	
	rectangle.setPosition(screen.width - size - offset, screen.height - size - offset);
	rectangle.setSize(sf::Vector2f(size, size));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color::White);
	
	line[0] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset, screen.height - size / 2 - offset));
	line[1] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset, screen.height - size / 2 - offset));

	point = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset, screen.height - size / 2 - offset));
	point.color = sf::Color::Red;
}

float VelocityVector::map(float v, float lmin, float lmax, float rmin, float rmax) {
	if (v < lmin)
		v = lmin;

	if (v > lmax)
		v = lmax;

	float leftRange = lmax - lmin;
	float rightRange = rmax - rmin;

	float leftPercentage = (v - lmin) / leftRange;

	return rmin + (leftPercentage * rightRange);
}

void VelocityVector::update(sf::Vector2f velocity) {
	float x, y;
	x = map(velocity.x, -10, 10, screen.width - size - offset, screen.width - offset);
	y = map(velocity.y, -10, 10, screen.height - size - offset, screen.height - offset);

	line[1] = sf::Vertex(sf::Vector2f(x, y));

	speed = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	//line[1] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset + velocity.x, screen.height - size / 2 - offset + velocity.y));
}

void VelocityVector::render(sf::RenderWindow &window) {
	window.draw(rectangle);
	window.draw(line, 2, sf::Lines);
	window.draw(&point, 1, sf::Points);
	
}