#ifndef VELOCITYVECTOR_H
#define VELOCITYVECTOR_H

// Dependencies
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <UI.h>

// Velocity Vector
class VelocityVector : public UI {
	private:
		float size;
		float offset;
		float speed;
		int zoomLevel;
		sf::RectangleShape rectangle;
		sf::RectangleShape innerRectangle;
		sf::Vertex line[2];
		sf::Vertex point;
		sf::VideoMode screen;
		sf::Text zoom;
		sf::Font font;
		sf::Mouse mouse;
	public:
		VelocityVector(sf::VideoMode screen);
		double map(double v, double lmin, double lmax, double rmin, double rmax);
		void setFont(sf::Font font);
		bool getHovered();
		std::string getDescription();
		void update(sf::Vector2<double> velocity);
		void render(sf::RenderWindow &window);
};

#endif