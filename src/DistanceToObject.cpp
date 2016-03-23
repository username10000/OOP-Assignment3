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
	distanceText.setColor(sf::Color::Red);
	distanceText.setPosition(size / 2 + offset, screen.height - size / 2 - distanceText.getCharacterSize() - offset);
	distanceText.setString("0");

	// Settings for the target text
	targetText.setFont(font);
	targetText.setCharacterSize(10);
	targetText.setColor(sf::Color::Cyan);
	targetText.setPosition(size / 2 + offset, screen.height - size / 2 + distanceText.getCharacterSize() - offset);
	targetText.setString("0");

	// Settings for the closest name
	closestName.setFont(font);
	closestName.setCharacterSize(12);
	closestName.setColor(sf::Color::Red);
	closestName.setStyle(sf::Text::Bold);
	closestName.setPosition(size / 2 + offset, screen.height - size / 2 - distanceText.getCharacterSize() * 3 - offset);
	closestName.setString("0");

	// Settings for the target name
	targetName.setFont(font);
	targetName.setCharacterSize(12);
	targetName.setColor(sf::Color::Cyan);
	targetName.setStyle(sf::Text::Bold);
	targetName.setPosition(size / 2 + offset, screen.height - size / 2 + distanceText.getCharacterSize() * 3 - offset);
	targetName.setString("0");

	// Initialising the direction line
	line[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red);
	line[1] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red);

	// Initialising the target line
	targetLine[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Cyan);
	targetLine[1] = sf::Vertex(sf::Vector2f(0, 0), sf::Color::Cyan);

	// Initialising the split line
	splitLine[0] = sf::Vertex(sf::Vector2f(size / 4 + offset, screen.height - size / 2 - offset));
	splitLine[1] = sf::Vertex(sf::Vector2f(size / 4 + size / 2 + offset, screen.height - size / 2 - offset));

	// Initialise the target object
	targetDistance = -1;
	targetAngle = 0;

	// Initialise the Ship Direction indication
	shipDirection.setPointCount(3);
	shipDirection.setRadius(size / 4 / 8);
}

void DistanceToObject::setTargetDistance(float d) {
	targetDistance = d;
}

void DistanceToObject::setTargetAngle(float a) {
	targetAngle = a;
}

void DistanceToObject::setTargetName(std::string n) {
	targetName.setString(n);
}

void DistanceToObject::update(float _angle, float _distance, std::string _name, float _shipAngle) {
	angle = _angle;
	distance = _distance;

	// Creating the string
	char d[15];
	sprintf_s(d, "%d KM", (int)distance);
	distanceText.setString(d);
	// Set the centre of the text
	distanceText.setOrigin(distanceText.getCharacterSize() * strlen(d) / 4, distanceText.getCharacterSize() / 2);

	// Setting the name of the Object
	closestName.setOrigin(closestName.getCharacterSize() * _name.size() / 4, closestName.getCharacterSize() / 2);
	closestName.setString(_name);

	// Setting the coordinates of the direction line
	line[0] = sf::Vertex(sf::Vector2f(offset + size / 2 - cos(angle) * size / 4, screen.height - size / 2 - offset - sin(angle) * size / 4), sf::Color::Red);
	line[1] = sf::Vertex(sf::Vector2f(offset + size / 2 - cos(angle) * size / 2, screen.height - size / 2 - offset - sin(angle) * size / 2), sf::Color::Red);

	// Set the angle of the Ship
	shipAngle = _shipAngle + 3.14159 / 2;
	shipDirection.setPosition(size / 2 + offset - cos(shipAngle) * (size / 4 + shipDirection.getRadius()), screen.height - size / 2 - offset - sin(shipAngle) * (size / 4 + shipDirection.getRadius()));
	shipDirection.setRotation(shipAngle * 180 / 3.14159265359 + 23);

	if (targetDistance != -1) {
		// Creating the string
		char dA[15];
		sprintf_s(dA, "%d KM", (int)targetDistance);
		targetText.setString(dA);
		targetText.setOrigin(targetText.getCharacterSize() * strlen(dA) / 4, targetText.getCharacterSize() / 2);

		// Set the centre of the text
		targetName.setOrigin(targetName.getCharacterSize() * targetName.getString().getSize() / 4, targetName.getCharacterSize() / 2);

		// Setting the coordinates of the target line
		targetLine[0] = sf::Vertex(sf::Vector2f(offset + size / 2 - cos(targetAngle) * size / 4, screen.height - size / 2 - offset - sin(targetAngle) * size / 4), sf::Color::Cyan);
		targetLine[1] = sf::Vertex(sf::Vector2f(offset + size / 2 - cos(targetAngle) * size / 2, screen.height - size / 2 - offset - sin(targetAngle) * size / 2), sf::Color::Cyan);
	}
}

void DistanceToObject::render(sf::RenderWindow &window) {
	window.draw(line, 2, sf::Lines);
	if (targetDistance != -1)
		window.draw(targetLine, 2, sf::Lines);
	window.draw(splitLine, 2, sf::Lines);
	window.draw(circle);
	window.draw(innerCircle);
	window.draw(distanceText);
	if (targetDistance != -1)
		window.draw(targetText);
	window.draw(closestName);
	if (targetDistance != -1)
		window.draw(targetName);
	window.draw(shipDirection);
}