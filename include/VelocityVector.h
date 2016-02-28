#ifndef VELOCITYVECTOR_H
#define VELOCITYVECTOR_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <cmath>

// Velocity Vector
class VelocityVector {
	private:
		float size;
		float offset;
		float speed;
		sf::RectangleShape rectangle;
		sf::Vertex line[2];
		sf::Vertex point;
		sf::VideoMode screen;
	public:
		VelocityVector(sf::VideoMode screen);
		double map(double v, double lmin, double lmax, double rmin, double rmax);
		void update(sf::Vector2<double> velocity);
		void render(sf::RenderWindow &window);
};

#endif