#include <InfoPanel.h>

InfoPanel::InfoPanel(sf::VideoMode _screen, sf::Font _font) {
	screen = _screen;
	font = _font;

	offset = 10;

	noLines = 8;

	for (int i = 0; i < noLines; i++) {
		sf::Text line;
		line.setFont(font);
		line.setCharacterSize(12);
		line.setPosition((float)offset * 2, (float)offset * 2 + i * (float)line.getCharacterSize() * 1.5);
		line.setString("LINE");
		lines.push_back(line);
	}

	container.setOutlineThickness(1);
	container.setOutlineColor(sf::Color::White);
	container.setFillColor(sf::Color::Transparent);
	container.setPosition(offset, offset);
	container.setSize(sf::Vector2f((float)screen.height / 5, lines[0].getCharacterSize() * noLines * 1.5 + offset * 2));
}

bool InfoPanel::getHovered() {
	if (mouse.getPosition().x > container.getPosition().x && mouse.getPosition().x < container.getPosition().x + container.getSize().x
		&& mouse.getPosition().y > container.getPosition().y && mouse.getPosition().y < container.getPosition().y + container.getSize().y)
		return true;
	else
		return false;
}

std::string InfoPanel::getDescription() {
	return "Shows detailed information about every system of the Ship";
}

void InfoPanel::update(std::string inertia, float thrust, float maxThrust, float fuel, float maxFuel, float speed, float speedToClosest, float speedToTarget, float maxSpeed, int cargo, int maxCargo) {
	float length = 0;
	
	lines[0].setString(inertia);
	lines[1].setString("Thrust: " + Functions::toStringWithComma((int)(thrust * 60 * 1000)) + " / " + Functions::toStringWithComma((int)(maxThrust * 60 * 1000)) + " m / s / s");
	lines[2].setString("Fuel: " + Functions::toStringWithComma((int)fuel) + " / " + Functions::toStringWithComma((int)maxFuel) + " l");
	lines[3].setString("Speed: " + Functions::toStringWithComma((int)(speed * 60 * 1000)) + " m / s");
	lines[4].setString("Speed to Closest: " + Functions::toStringWithComma((int)(speedToClosest * 60 * 1000)) + " m / s");
	if (speedToTarget != -1)
		lines[5].setString("Speed to Target: " + Functions::toStringWithComma((int)(speedToTarget * 60 * 1000)) + " m / s");
	else
		lines[5].setString("Speed to Target: N / A");
	lines[6].setString("Max Relative Speed: " + Functions::toStringWithComma((int)(maxSpeed * 60 * 1000)) + " m / s");
	lines[7].setString("Cargo: " + Functions::toStringWithComma(cargo) + " / " + Functions::toStringWithComma(maxCargo));

	// Increase the Container's Size to fit the Text
	for (unsigned int i = 0; i < lines.size(); i++) {
		if (lines[i].getLocalBounds().width > length)
			length = lines[i].getLocalBounds().width;
	}
	container.setSize(sf::Vector2f(offset * 2 + length, container.getSize().y));
}

void InfoPanel::render(sf::RenderWindow &window) {
	window.draw(container);
	for (unsigned int i = 0; i < lines.size(); i++) {
		window.draw(lines[i]);
	}
}