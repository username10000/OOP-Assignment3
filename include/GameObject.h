// Guard
#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

// Dependencies
#include <SFML/Graphics.hpp>

// GameObject
class GameObject {
	private:
		sf::Vector2<double> position;
		sf::Vector2f screenPosition;
	public:
		GameObject(double x, double y);
		GameObject();
		double getX();
		double getY();
		void setX(double x);
		void setY(double y);
		sf::Vector2<double> getPosition();
		virtual void update() = 0;
		virtual void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) = 0;
		void setScreenPosition(float x, float y);
};

#endif