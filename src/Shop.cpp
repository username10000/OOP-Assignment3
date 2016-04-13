#include <Shop.h>

Shop::Shop(sf::VideoMode screen, sf::Font font, sf::Texture *shipTextures) {
	this->font = font;
	this->shipTextures = *shipTextures;
	
	for (int i = 0; i < shipTextures->getSize().y / 40; i++) {
		sf::RectangleShape shipRect;
		sf::IntRect shipTextureRect;
		shipRect.setSize(sf::Vector2f(40, 40));
		shipRect.setTexture(shipTextures);
		shipTextureRect.top = 0;
		shipTextureRect.left = i * 41;
		shipTextureRect.width = 40;
		shipTextureRect.height = 40;
		shipRect.setTextureRect(shipTextureRect);
		buttons.push_back(std::unique_ptr<Button>(new Button(shipRect)));
		buttons[buttons.size() - 1]->setPosition(Functions::map(i, 0, this->shipTextures.getSize().y / 40, screen.width / 2, screen.width - screen.width / 2), screen.height / 2);
	}
}

void Shop::update(sf::RenderWindow &window) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->update(window);
	}
}

void Shop::render(sf::RenderWindow &window) {
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->render(window);
	}
}