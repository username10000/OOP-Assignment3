#include <Message.h>

Message::Message(sf::VideoMode _screen, sf::Font _font) {
	font = _font;

	text.setFont(font);
	text.setCharacterSize(20);
	text.setColor(sf::Color::White);
	text.setPosition(_screen.width / 2, _screen.height / 4);

	background.setFillColor(sf::Color(0, 0, 0, 100));
	background.setPosition(_screen.width / 2, _screen.height / 4);
	background.setSize(sf::Vector2f(0, text.getCharacterSize() * 2));

	isVisible = false;
}

void Message::show() {
	isVisible = true;
}

void Message::hide() {
	isVisible = false;
}

bool Message::getIsVisible() {
	return isVisible;
}

void Message::update(std::string string) {
	text.setString(string);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setColor(sf::Color::White);
	background.setSize(sf::Vector2f(text.getLocalBounds().width + text.getCharacterSize() * 2, text.getLocalBounds().height + text.getCharacterSize() * 2)); // background.getSize().y
	background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
	show();
}

void Message::update(std::string string, sf::Color colour) {
	update(string);
	text.setColor(colour);
}

void Message::render(sf::RenderWindow &window) {
	window.draw(background);
	window.draw(text);
}