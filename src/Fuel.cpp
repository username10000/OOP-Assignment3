#include <Fuel.h>

Fuel::Fuel(sf::VideoMode _screen, sf::Font _font) {
	// Save the screen and font
	screen = _screen;
	font = _font;

	// Set the Offset
	offset = 10;

	// Create the Colours for the Inner Rectangle
	colours[0] = sf::Color(51, 102, 0);
	colours[1] = sf::Color(204, 153, 0);
	colours[2] = sf::Color(204, 0, 0);

	// Outer Rectangular
	outerRect.setFillColor(sf::Color::Transparent);
	outerRect.setOutlineThickness(1);
	outerRect.setOutlineColor(sf::Color::White);
	outerRect.setSize(sf::Vector2f(screen.height / 5, screen.height / 30));
	outerRect.setPosition(screen.width - outerRect.getSize().x - offset, offset + outerRect.getSize().y + offset);

	// Inner Rectangular
	innerRect.setFillColor(colours[2]);
	innerRect.setSize(sf::Vector2f(screen.height / 5, screen.height / 30));
	innerRect.setPosition(outerRect.getPosition().x, outerRect.getPosition().y);

	// Text
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(15);
	text.setString("Fuel");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(outerRect.getPosition().x + outerRect.getSize().x / 2, outerRect.getPosition().y + outerRect.getSize().y / 2);
}

bool Fuel::getHovered() {
	if (mouse.getPosition().x > outerRect.getPosition().x && mouse.getPosition().x < outerRect.getPosition().x + outerRect.getSize().x
		&& mouse.getPosition().y > outerRect.getPosition().y && mouse.getPosition().y < outerRect.getPosition().y + outerRect.getSize().y)
		return true;
	else
		return false;
}

std::string Fuel::getDescription() {
	return "Shows the Remaining Fuel";
}

void Fuel::update(float percentage) {
	innerRect.setSize(sf::Vector2f(Functions::map(percentage, 0, 100, 0, outerRect.getSize().x), innerRect.getSize().y));
	if (percentage <= 35)
		innerRect.setFillColor(colours[2]);
	if (percentage > 35 && percentage < 65)
		innerRect.setFillColor(colours[1]);
	if (percentage >= 65)
		innerRect.setFillColor(colours[0]);
}

void Fuel::render(sf::RenderWindow &window) {
	window.draw(outerRect);
	window.draw(innerRect);
	window.draw(text);
}