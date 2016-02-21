#ifndef VELOCITYVECTOR_H
#define VELOCITYVECTOR_H

// Dependencies
#include <SFML/Graphics.hpp>

// Velocity Vector
class VelocityVector {
	private:
		float size;
		float offset;
		sf::RectangleShape rectangle;
		sf::Vertex line[2];
		sf::Vertex point;
		sf::VideoMode screen;
	public:
		VelocityVector(sf::VideoMode screen);
		float map(float v, float lmin, float lmax, float rmin, float rmax);
		void update(sf::Vector2f velocity);
		void render(sf::RenderWindow &window);
};

#endif