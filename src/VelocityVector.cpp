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

	innerRectangle.setPosition(screen.width - 3 * size / 4 - offset, screen.height - 3 * size / 4 - offset);
	innerRectangle.setSize(sf::Vector2f(size / 2, size / 2));
	innerRectangle.setFillColor(sf::Color::Transparent);
	innerRectangle.setOutlineThickness(1);
	innerRectangle.setOutlineColor(sf::Color::White);
	
	line[0] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset, screen.height - size / 2 - offset));
	line[1] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset, screen.height - size / 2 - offset));

	point = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset, screen.height - size / 2 - offset));
	point.color = sf::Color::Red;

	zoom.setFont(font);
	zoom.setCharacterSize(16);
	sf::FloatRect textBounds = zoom.getLocalBounds();
	zoom.setOrigin((float)zoom.getCharacterSize() / 2, (float)zoom.getCharacterSize() / 2);
	//zoom.setOrigin(zoom.getLocalBounds().left + zoom.getLocalBounds().width / 2, zoom.getLocalBounds().top + zoom.getLocalBounds().height / 2);
	zoom.setString("x1");
	//std::cout << zoom.getCharacterSize();
	zoom.setPosition(screen.width - size + offset, screen.height - zoom.getCharacterSize() - offset);

	zoomLevel = 1;
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

bool VelocityVector::getHovered() {
	if (mouse.getPosition().x > rectangle.getPosition().x && mouse.getPosition().x < rectangle.getPosition().x + rectangle.getSize().x
		&& mouse.getPosition().y > rectangle.getPosition().y && mouse.getPosition().y < rectangle.getPosition().y + rectangle.getSize().y)
		return true;
	else
		return false;
}

std::string VelocityVector::getDescription() {
	return "Shows the Velocity Vector \ni.e. the direction of the Velocity";
}

void VelocityVector::update(sf::Vector2<double> velocity) {
	double x, y;

	//std::cout << velocity.x << " " << velocity.y << std::endl;

	if (velocity.x > 5 * zoomLevel || velocity.y > 5 * zoomLevel || velocity.x < -5 * zoomLevel || velocity.y < -5 * zoomLevel) {
		zoomLevel *= 2;
		char zlt[10];
		sprintf_s(zlt, "x%d", zoomLevel);
		zoom.setString(zlt);
	}
	if ((velocity.x < 5 * (zoomLevel / 2) && velocity.y < 5 * (zoomLevel / 2) && velocity.x > -5 * (zoomLevel / 2) && velocity.y > -5 * (zoomLevel / 2)) 
		&& (zoomLevel > 1)) {
		zoomLevel /= 2;
		char zlt[10];
		sprintf_s(zlt, "x%d", zoomLevel);
		zoom.setString(zlt);
	}

	x = map(velocity.x, -5 * zoomLevel, 5 * zoomLevel, screen.width - size - offset, screen.width - offset);
	y = map(velocity.y, -5 * zoomLevel, 5 * zoomLevel, screen.height - size - offset, screen.height - offset);

	line[1] = sf::Vertex(sf::Vector2f((float)x, (float)y));

	speed = (float)sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	//line[1] = sf::Vertex(sf::Vector2f(screen.width - size / 2 - offset + velocity.x, screen.height - size / 2 - offset + velocity.y));
}

void VelocityVector::render(sf::RenderWindow &window) {
	window.draw(rectangle);
	window.draw(innerRectangle);
	window.draw(line, 2, sf::Lines);
	window.draw(&point, 1, sf::Points);
	window.draw(zoom);
}