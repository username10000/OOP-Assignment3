#include <GameObject.h>

GameObject::GameObject(float x, float y) {
	position.x = x;
	position.y = y;
}

float GameObject::getX() {
	return position.x;
}

float GameObject::getY() {
	return position.y;
}

sf::Vector2f GameObject::getPosition() {
	return position;
}