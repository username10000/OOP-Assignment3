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
		//sf::Texture texture;
		//sf::Sprite sprite;
		bool hover, active;
		bool rect;
		//bool isSprite;
	public:
		Button();
		Button(sf::CircleShape shape);
		Button(sf::RectangleShape shape);
		//Button(sf::Texture &texture);
		void setPosition(double x, double y);
		double getX();
		double getY();
		double getWidth();
		bool isActive();
		void update(sf::RenderWindow &window);
		void render(sf::RenderWindow &window);
};

#endif