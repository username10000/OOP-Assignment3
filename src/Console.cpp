#include <Console.h>

Console::Console(sf::VideoMode _screen, sf::Font _font) {
	font = _font;

	inputText.setFont(font);
	inputText.setCharacterSize(20);
	inputText.setPosition(15, 15);
	inputText.setString("");

	inputField.setPosition(10, 10);
	inputField.setSize(sf::Vector2f(_screen.width - 2 * inputField.getPosition().x, inputText.getCharacterSize() * 1.5 + 5));
	inputField.setFillColor(sf::Color(0, 0, 0, 150));
	inputField.setOutlineThickness(2);

	line[0] = sf::Vertex(sf::Vector2f(inputText.getPosition().x, inputText.getPosition().y), sf::Color::White);
	line[1] = sf::Vertex(sf::Vector2f(inputText.getPosition().x, inputText.getPosition().y + inputText.getCharacterSize()), sf::Color::White);

	cursor = true;
}

void Console::update(std::string input) {
	bool changed = false;

	if (input.compare(inputText.getString()) != 0)
		changed = true;

	inputText.setString(input);

	if (changed) {
		cursor = false;
		lastBlink.restart();
	} else {
		line[0] = sf::Vertex(sf::Vector2f(inputText.getPosition().x * 1.2 + inputText.getLocalBounds().width, inputText.getPosition().y), sf::Color::White);
		line[1] = sf::Vertex(sf::Vector2f(inputText.getPosition().x * 1.2 + inputText.getLocalBounds().width, inputText.getPosition().y + inputText.getCharacterSize()), sf::Color::White);

		if (lastBlink.getElapsedTime().asSeconds() > 0.5) {
			cursor = !cursor;
			lastBlink.restart();
		}
	}
}

void Console::render(sf::RenderWindow &window) {
	window.draw(inputField);
	window.draw(inputText);
	if (cursor) {
		window.draw(line, 2, sf::Lines);
	}
}