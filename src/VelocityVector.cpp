#include <VelocityVector.h>

VelocityVector::VelocityVector(sf::VideoMode _screen) {
	screen = _screen;

	size = (float)(screen.height / 5);
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

	zoom.setFont(font);
	zoom.setCharacterSize(16);
	zoom.setOrigin(zoom.getLocalBounds().width / 2, zoom.getLocalBounds().height / 2);
	zoom.setString("x1");
	zoom.setPosition(screen.width - offset - 25, screen.height - offset - 25);
}

double VelocityVector::map(double v, double lmin, double lmax, double rmin, double rmax) {
	if (v < lmin)
		v = lmin;

	if (v > lmax)
		v = lmax;

	double leftRange = lmax - lmin;
	double rightRange = rmax - rmin;

	double leftPercentage = (v - lmin) / leftRange;

	return rmin + (leftPercentage * rightRange);
}

void VelocityVector::setFont(sf::Font font) {
	this -> font = font;
}

void VelocityVector::update(sf::Vector2<double> velocity) {
	double x, y;
	x = map(velocity.x, -5, 5, screen.width - size - offset, screen.width - offset);
	y = map(velocity.y, -5, 5, screen.height - size - offset, screen.height - offset);

	line[1] = sf::Vertex(sf::Vector2f((float)x, (float)y));

	speed = (float)sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	//line[1] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset + velocity.x, screen.height - size / 2 - offset + velocity.y));
}

void VelocityVector::render(sf::RenderWindow &window) {
	window.draw(rectangle);
	window.draw(line, 2, sf::Lines);
	window.draw(&point, 1, sf::Points);
	window.draw(zoom);
}