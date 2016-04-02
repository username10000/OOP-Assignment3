#include <CommonObject.h>

CommonObject::CommonObject(sf::Texture *texture, sf::Color col, float sA, float rA, float r) {
	dimension.x = texture->getSize().x / 6;
	dimension.y = texture->getSize().y / 2;
	colour = col;
	sprite.setTexture(*texture);
	sprite.setColor(colour);
	sprite.setOrigin(dimension.x / 2, dimension.y / 2);
	//middleObject.x = mX;
	//middleObject.y = mY;
	angle = sA;
	rotAngle = rA;
	radius = r;
	sprite.setRotation(angle * 180 / PI - PI / 2 * 180 / PI);
	scale = 0.3;
}

void CommonObject::setScale(float s) {
	scale = s;
}

float CommonObject::getScale() {
	return scale;
}

sf::Vector2<double> CommonObject::getDimension() {
	return dimension;
}

void CommonObject::setTextureRect(sf::IntRect tR) {
	sprite.setTextureRect(tR);
}

float CommonObject::getAngle() {
	return angle;
}

void CommonObject::update() {

}

bool CommonObject::isTree() {
	if (sprite.getTextureRect().left == 0)
		return true;
	else
		return false;
}

void CommonObject::update(double mX, double mY) {
	setX(mX - cos(angle) * (radius + dimension.y * scale / 2 - 0.1));
	setY(mY - sin(angle) * (radius + dimension.y * scale / 2 - 0.1));
	angle += rotAngle * PI / 180;
	sprite.rotate(rotAngle);
}

void CommonObject::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	sprite.setScale(scale / (double)ppm, scale / (double)ppm);
	sprite.setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
	window.draw(sprite);
}