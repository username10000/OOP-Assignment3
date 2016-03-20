#ifndef ASTROMAP_H
#define ASTROMAP_H

// Dependencies
#include <SFML/Graphics.hpp>

// Map
class AstroMap {
	private:
		float ppm;
		sf::Font font;
		sf::Vector2<double> ship;
		sf::Color shipColour;
		std::vector<sf::Vector2<double>> astro;
		std::vector<sf::Color> astroColour;
		std::vector<float> astroRadius;
	public:
		AstroMap(float ppm, sf::Font);
		void addAstro(double x, double y, sf::Color colour, float radius);
		void setAstro(int p, double x, double y);
		void setShip(double x, double y);
		void setppm(float ppm);
		void render(sf::RenderWindow &window, sf::VideoMode screen);
};

#endif