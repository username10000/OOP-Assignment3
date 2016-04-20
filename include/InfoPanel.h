#ifndef INFOPANEL_H
#define INFOPANEL_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <Functions.h>
#include <UI.h>

// Information Panel
class InfoPanel : public UI {
	private:
		sf::VideoMode screen;
		sf::Font font;
		sf::RectangleShape container;
		std::vector<sf::Text> lines;
		sf::Mouse mouse;
		int noLines;
		float offset;
	public:
		InfoPanel(sf::VideoMode _screen, sf::Font _font);
		bool getHovered();
		std::string getDescription();
		void update(std::string inertia, float thrust, float maxThrust, float fuel, float maxFuel, float speed, float speedToClosest, float speedToTarget, float maxSpeed, int cargo, int maxCargo);
		void render(sf::RenderWindow &window);
};

#endif