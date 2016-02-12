#include <GameObject.h>

GameObject::GameObject(long long x, long long y) {
	position.x = x;
	position.y = y;
}

GameObject::GameObject() {
	position.x = 0;
	position.y = 0;
}

long long GameObject::getX() {
	return position.x;
}

long long GameObject::getY() {
	return position.y;
}

sf::Vector2<long long> GameObject::getPosition() {
	return position;
}

void GameObject::setScreenPosition(float x, float y) {
	screenPosition.x = x;
	screenPosition.y = y;
}