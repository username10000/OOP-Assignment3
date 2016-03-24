#ifndef PLANET_H
#define PLANET_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <AstroObject.h>
#include <Ship.h>

// Planet
class Planet : public AstroObject {
	private:
		sf::CircleShape circle;
	public:
		Planet(double x, double y, float _radius, sf::Color _colour, float _rotation);
		Planet();
		void update();
		//void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen);
};

#endif