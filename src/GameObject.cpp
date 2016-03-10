#include <GameObject.h>

GameObject::GameObject(double x, double y) {
	position.x = x;
	position.y = y;
}

GameObject::GameObject() {
	position.x = 0;
	position.y = 0;
}

double GameObject::getX() {
	return position.x;
}

double GameObject::getY() {
	return position.y;
}

double GameObject::getOldX() {
	return oldPosition.x;
}

double GameObject::getOldY() {
	return oldPosition.y;
}

void GameObject::setX(double x) {
	position.x = x;
}

void GameObject::setY(double y) {
	position.y = y;
}

void GameObject::setOldX(double x) {
	oldPosition.x = x;
}

void GameObject::setOldY(double y) {
	oldPosition.y = y;
}


sf::Vector2<double> GameObject::getPosition() {
	return position;
}

void GameObject::setScreenPosition(float x, float y) {
	screenPosition.x = x;
	screenPosition.y = y;
}