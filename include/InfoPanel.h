#ifndef INFOPANEL_H
#define INFOPANEL_H

// Dependencies
#include <SFML/Graphics.hpp>

// Information Panel
class InfoPanel {
	private:
		sf::VideoMode screen;
		sf::Font font;
		sf::RectangleShape container;
		std::vector<sf::Text> lines;
		int noLines;
		float offset;
	public:
		InfoPanel(sf::VideoMode _screen, sf::Font _font);
		void update(std::string inertia, float thrust, float maxThrust, float fuel, float maxFuel, float speed, float speedToClosest, float speedToTarget, float maxSpeed);
		void render(sf::RenderWindow &window);
};

#endif