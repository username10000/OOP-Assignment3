#include <Thrust.h>

Thrust::Thrust(sf::VideoMode _screen, sf::Font _font) {
	// Save the screen and font
	screen = _screen;
	font = _font;

	// Set the Offset
	offset = 10;

	// Rectangular
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::White);
	rect.setSize(sf::Vector2f(screen.height / 5, screen.height / 30));
	rect.setPosition(screen.width - rect.getSize().x - offset, offset);

	// Indicator
	indicator.setPointCount(3);
	indicator.setRadius(rect.getSize().y / 5);
	indicator.setOrigin(indicator.getRadius(), indicator.getRadius());
	indicator.setPosition(rect.getPosition().x + indicator.getRadius(), rect.getPosition().y + indicator.getRadius());

	// Gradations
	lines.setPrimitiveType(sf::Lines);
	// 0 %
	lines.append(sf::Vertex(sf::Vector2f(rect.getPosition().x + indicator.getRadius(), rect.getPosition().y)));
	lines.append(sf::Vertex(sf::Vector2f(rect.getPosition().x + indicator.getRadius(), rect.getPosition().y + rect.getSize().y / 2)));
	// 10 - 40 %
	for (int i = 1; i <= 4; i++) {
		double xPos = Functions::map(i, 0, 5, rect.getPosition().x + indicator.getRadius(), rect.getPosition().x + rect.getSize().x / 2);
		lines.append(sf::Vertex(sf::Vector2f(xPos, rect.getPosition().y)));
		lines.append(sf::Vertex(sf::Vector2f(xPos, rect.getPosition().y + rect.getSize().y / 4)));
	}
	// 50%
	lines.append(sf::Vertex(sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y)));
	lines.append(sf::Vertex(sf::Vector2f(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2)));
	// 60 - 90 %
	for (int i = 1; i <= 4; i++) {
		double xPos = Functions::map(i, 0, 5, rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().x + rect.getSize().x - indicator.getRadius());
		lines.append(sf::Vertex(sf::Vector2f(xPos, rect.getPosition().y)));
		lines.append(sf::Vertex(sf::Vector2f(xPos, rect.getPosition().y + rect.getSize().y / 4)));
	}
	// 100 %
	lines.append(sf::Vertex(sf::Vector2f(rect.getPosition().x + rect.getSize().x - indicator.getRadius(), rect.getPosition().y)));
	lines.append(sf::Vertex(sf::Vector2f(rect.getPosition().x + rect.getSize().x - indicator.getRadius(), rect.getPosition().y + rect.getSize().y / 2)));

	// Percentage Text
	// 0
	left.setFont(font);
	left.setCharacterSize(10);
	left.setString("0");
	left.setOrigin(left.getLocalBounds().width / 2, left.getLocalBounds().height / 2);
	left.setPosition(rect.getPosition().x + indicator.getRadius(), rect.getPosition().y + rect.getSize().y - left.getCharacterSize());
	// 100
	right.setFont(font);
	right.setCharacterSize(10);
	right.setString("100");
	right.setOrigin(right.getLocalBounds().width, right.getLocalBounds().height / 2);
	right.setPosition(rect.getPosition().x + rect.getSize().x - indicator.getRadius(), rect.getPosition().y + rect.getSize().y - right.getCharacterSize());

	// Text
	name.setFont(font);
	name.setColor(sf::Color::White);
	name.setCharacterSize(12);
	name.setString("Thrust");
	name.setOrigin(name.getLocalBounds().width / 2, 0);
	name.setPosition(rect.getPosition().x + rect.getSize().x / 2, rect.getPosition().y + rect.getSize().y / 2);
}

bool Thrust::getHovered() {
	if (mouse.getPosition().x > rect.getPosition().x && mouse.getPosition().x < rect.getPosition().x + rect.getSize().x
		&& mouse.getPosition().y > rect.getPosition().y && mouse.getPosition().y < rect.getPosition().y + rect.getSize().y)
		return true;
	else
		return false;
}

std::string Thrust::getDescription() {
	return "Shows the Power of the Thrust";
}

void Thrust::update(float percentage) {
	indicator.setPosition(Functions::map(percentage, 0, 100, lines[0].position.x, lines[lines.getVertexCount() - 1].position.x), indicator.getPosition().y);
}

void Thrust::render(sf::RenderWindow &window) {
	window.draw(rect);
	window.draw(lines);
	window.draw(indicator);
	window.draw(left);
	window.draw(right);
	window.draw(name);
}