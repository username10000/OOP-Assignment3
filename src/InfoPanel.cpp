#include <InfoPanel.h>

InfoPanel::InfoPanel(sf::VideoMode _screen, sf::Font _font) {
	screen = _screen;
	font = _font;

	offset = 10;

	noLines = 7;

	for (int i = 0; i < noLines; i++) {
		sf::Text line;
		line.setFont(font);
		line.setCharacterSize(12);
		line.setPosition(offset * 2, offset * 2 + i * line.getCharacterSize() * 1.5);
		line.setString("LINE");
		lines.push_back(line);
	}

	container.setOutlineThickness(1);
	container.setOutlineColor(sf::Color::White);
	container.setFillColor(sf::Color::Transparent);
	container.setPosition(offset, offset);
	container.setSize(sf::Vector2f(screen.height / 5, lines[0].getCharacterSize() * noLines * 1.5 + offset * 2));
}

void InfoPanel::update(std::string inertia, float thrust, float maxThrust, float fuel, float maxFuel, float speed, float speedToClosest, float speedToTarget, float maxSpeed) {
	float length = 0;
	
	lines[0].setString(inertia);
	lines[1].setString("Thrust: " + std::to_string((int)thrust) + " / " + std::to_string((int)maxThrust));
	lines[2].setString("Fuel: " + std::to_string((int)fuel) + " / " + std::to_string((int)maxFuel));
	lines[3].setString("Speed: " + std::to_string((int)(speed * 60)) + " KM / S");
	lines[4].setString("Speed to Closest: " + std::to_string((int)(speedToClosest * 60)) + " KM / S");
	if (speedToTarget != -1)
		lines[5].setString("Speed to Target: " + std::to_string((int)(speedToTarget * 60)) + " KM / S");
	else
		lines[5].setString("Speed to Target: N / A");
	lines[6].setString("Max Relative Speed: " + std::to_string((int)(maxSpeed * 60)) + " KM / S");

	// Increase the Container's Size to fit the Text
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].getLocalBounds().width > length)
			length = lines[i].getLocalBounds().width;
	}
	container.setSize(sf::Vector2f(offset * 2 + length, container.getSize().y));
}

void InfoPanel::render(sf::RenderWindow &window) {
	window.draw(container);
	for (int i = 0; i < lines.size(); i++) {
		window.draw(lines[i]);
	}
}