#include <GameObject.h>

GameObject::GameObject(float x, float y) {
	position.x = x;
	position.y = y;
}

GameObject::GameObject() {
	position.x = 0;
	position.y = 0;
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

//void GameObject::update() {}
//void GameObject::render() {}