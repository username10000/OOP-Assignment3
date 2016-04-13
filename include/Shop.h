#ifndef SHOP_H
#define SHOP_H

// Dependencies
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <Functions.h>
#include <Button.h>

// Shop
class Shop {
	private:
		sf::RectangleShape background;
		sf::Texture shipTextures;
		sf::Font font;
		std::vector<std::unique_ptr<Button>> buttons;
		std::vector<sf::Text> names;
	public:
		Shop(sf::VideoMode screen, sf::Font, sf::Texture *shipTextures);
		void update(sf::RenderWindow &window);
		void render(sf::RenderWindow &window);
};

#endif