// Guard
#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

// Dependencies
#include <SFML/Graphics.hpp>

// GameObject
class GameObject {
	private:
		sf::Vector2f position;
	public:
		GameObject(float x, float y);
		float getX();
		float getY();
		sf::Vector2f getPosition();
};

#endif