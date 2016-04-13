#ifndef SHOP_H
#define SHOP_H

// Dependencies
#include <memory>
#include <SFML/Graphics.hpp>
#include <Functions.h>
#include <Button.h>

// Shop
class Shop {
	private:
		sf::Texture shipTextures;
		sf::Font font;
		std::vector<std::unique_ptr<Button>> buttons;
	public:
		Shop(sf::VideoMode screen, sf::Font, sf::Texture *shipTextures);
		void update(sf::RenderWindow &window);
		void render(sf::RenderWindow &window);
};

#endif