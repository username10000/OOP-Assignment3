#include <AlienObject.h>

AlienObject::AlienObject(double x, double y, float _radius, sf::Color _colour, float _rotation) : Planet(x, y, _radius, _colour, _rotation) {
	setMass(getMass() * 0.2);
	setHabitable(false);
	clearObjs();
}


AlienObject::AlienObject() : Planet() {

}