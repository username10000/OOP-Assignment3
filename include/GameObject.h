// Guard
#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

// Dependencies
#include <SFML/Graphics.hpp>

// GameObject
class GameObject {
	private:
		sf::Vector2<long long> position;
		sf::Vector2f screenPosition;
	public:
		GameObject(long long x, long long y);
		GameObject();
		long long getX();
		long long getY();
		sf::Vector2<long long> getPosition();
		virtual void update() = 0;
		virtual void render(sf::RenderWindow &window, sf::Vector2<long long> view, sf::VideoMode screen) = 0;
		void setScreenPosition(float x, float y);
};

#endif