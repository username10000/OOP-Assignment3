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
		GameObject();
		float getX();
		float getY();
		sf::Vector2f getPosition();
		virtual void update() = 0;
		virtual void render(sf::RenderWindow &window) = 0;
};

#endif