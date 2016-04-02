#include <SpecialObject.h>

SpecialObject::SpecialObject(sf::Texture *texture, sf::Color col, float sA, float rA, float r) : CommonObject(texture, col, sA, rA, r) {
	active = true;
}

void SpecialObject::setType(int t) {
	type = t;
}

int SpecialObject::getType() {
	return type;
}

void SpecialObject::setActive(bool a) {
	active = a;
}

bool SpecialObject::getActive() {
	return active;
}