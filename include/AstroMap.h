#ifndef ASTROMAP_H
#define ASTROMAP_H

// Dependencies
#include <memory>
#include <SFML/Graphics.hpp>
#include <Button.h>

// Map
class AstroMap {
	private:
		float ppm;
		sf::Font font;
		sf::Vector2<double> ship;
		sf::Color shipColour;
		//std::vector<sf::Vector2<double>> astro;
		//std::vector<sf::Color> astroColour;
		//std::vector<float> astroRadius;
		std::vector<std::unique_ptr<Button>> buttons;
	public:
		AstroMap(float ppm, sf::Font);
		void addAstro(sf::VideoMode screen, double x, double y, sf::Color colour, float radius);
		void setAstro(sf::RenderWindow &window, sf::VideoMode screen, int p, double x, double y);
		void setShip(double x, double y);
		void setppm(float ppm);
		int getClickedPlanet();
		void render(sf::RenderWindow &window, sf::VideoMode screen);
};

#endif