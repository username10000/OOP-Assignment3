#include <Shop.h>

Shop::Shop(sf::VideoMode screen, sf::Font font, sf::Texture *shipTextures) {
	this->font = font;
	this->shipTextures = *shipTextures;
	
	background.setSize(sf::Vector2f(screen.width / 2, screen.height / 2));
	background.setFillColor(sf::Color(0, 0, 0, 150));
	background.setPosition(screen.width / 4, screen.height / 4);

	for (int i = 0; i < shipTextures->getSize().x / 40; i++) {
		sf::RectangleShape shipRect;
		sf::IntRect shipTextureRect;
		shipRect.setSize(sf::Vector2f(100, 100));
		shipRect.setTexture(shipTextures);
		shipTextureRect.top = 0;
		shipTextureRect.left = i * 41;
		shipTextureRect.width = 40;
		shipTextureRect.height = 40;
		shipRect.setTextureRect(shipTextureRect);
		shipRect.setOrigin(shipRect.getLocalBounds().width / 2, shipRect.getLocalBounds().height / 2);
		float xPos = Functions::map(i, 0, (int)(this->shipTextures.getSize().x / 40) - 1, screen.width / 4 + shipRect.getSize().x, screen.width - screen.width / 4 - shipRect.getSize().x);
		float yPos = screen.height / 4 + shipRect.getSize().y;
		buttons.push_back(std::unique_ptr<Button>(new Button(shipRect)));
		buttons[buttons.size() - 1]->setPosition(xPos, yPos);

		sf::Text name;

		names.push_back(name);
		names[names.size() - 1].setFont(this->font);
		names[names.size() - 1].setCharacterSize(15);
		names[names.size() - 1].setString(Functions::toStringWithComma(Functions::randomInt(10000, 50000)));
		names[names.size() - 1].setOrigin(names[names.size() - 1].getLocalBounds().width / 2, names[names.size() - 1].getLocalBounds().height / 2);
		names[names.size() - 1].setPosition(xPos, yPos + 40 + names[names.size() - 1].getCharacterSize());
	}
}

void Shop::update(sf::RenderWindow &window) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->update(window);
	}
}

void Shop::render(sf::RenderWindow &window) {
	window.draw(background);
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->render(window);
		window.draw(names[i]);
	}
}