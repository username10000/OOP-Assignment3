#include <DistanceToObject.h>

DistanceToObject::DistanceToObject(sf::VideoMode _screen, sf::Font _font) {
	screen = _screen;
	font = _font;

	size = (float)(screen.height / 5);
	offset = 10;

	// Settings for the outer circle
	circle.setPosition(offset, screen.height - size - offset);
	circle.setRadius(size / 2);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(2);
	circle.setOutlineColor(sf::Color::White);

	// Settings for the inner circle
	innerCircle.setPosition(offset + size / 4, screen.height - 3 * size / 4 - offset);
	innerCircle.setRadius(size / 4);
	innerCircle.setFillColor(sf::Color::Transparent);
	innerCircle.setOutlineThickness(1);
	innerCircle.setOutlineColor(sf::Color::White);

	// Settings for the text
	distanceText.setFont(font);
	distanceText.setCharacterSize(10);
	distanceText.setPosition(offset + size / 2, screen.height - size / 2 - offset);
	distanceText.setString("0");

	// Initialising the direction line
	line[0] = sf::Vertex(sf::Vector2f(0, 0));
	line[1] = sf::Vertex(sf::Vector2f(0, 0));
}

void DistanceToObject::update(float _angle, float _distance) {
	angle = _angle;
	distance = _distance;

	// Creating the string
	char d[15];
	sprintf_s(d, "%d KM", (int)distance);
	distanceText.setString(d);
	//while (distanceText.getCharacterSize() * strlen(d) > size) {
	//	distanceText.setCharacterSize(distanceText.getCharacterSize() - 1);
	//}
	//while (distanceText.getCharacterSize() * strlen(d) < size) {
	//	distanceText.setCharacterSize(distanceText.getCharacterSize() + 1);
	//}
	distanceText.setOrigin(distanceText.getCharacterSize() * strlen(d) / 4, distanceText.getCharacterSize() / 2);

	// Settings the coordinates of the direction line
	line[0] = sf::Vertex(sf::Vector2f(offset + size / 2 - cos(angle) * size / 4, screen.height - size / 2 - offset - sin(angle) * size / 4));
	line[1] = sf::Vertex(sf::Vector2f(offset + size / 2 - cos(angle) * size / 2, screen.height - size / 2 - offset - sin(angle) * size / 2));
}

void DistanceToObject::render(sf::RenderWindow &window) {
	window.draw(line, 2, sf::Lines);
	window.draw(circle);
	window.draw(innerCircle);
	window.draw(distanceText);
}