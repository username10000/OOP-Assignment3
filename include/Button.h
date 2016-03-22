#ifndef BUTTON_H
#define BUTTON_H

// Dependencies
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

// Button
class Button {
	private:
		//sf::Vector2<double> position;
		sf::CircleShape circle;
		sf::RectangleShape rectangle;
		sf::Mouse mouse;
		bool hover, active;
		bool rect;
	public:
		Button();
		Button(sf::CircleShape shape);
		Button(sf::RectangleShape shape);
		void setPosition(double x, double y);
		double getX();
		double getY();
		double getWidth();
		bool isActive();
		void update(sf::RenderWindow &window);
		void render(sf::RenderWindow &window);
};

#endif