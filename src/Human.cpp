#include <Human.h>

Human::Human(double x, double y, sf::Texture *texture) : GameObject(x, y) {
	//texture.loadFromFile("human.png");
	sprite.setTexture(*texture);
	sf::IntRect textureRect;
	textureRect.top = 0;
	textureRect.left = 15;
	textureRect.width = 15;
	textureRect.height = 40;
	sprite.setTextureRect(textureRect);
	sprite.setOrigin(10, 20);

	mass = 0.01;
	velocity.x = velocity.y = 0;
	direction.x = direction.y = 0;
	force = 0;
	angle = 0;

	dir = 1;

	jump = false;

	state = 0;
	nextStateChange = 0;

	closestSpecial = -1;
}

sf::Vector2<double> Human::getVelocity() {
	return velocity;
}

sf::Vector2<double> Human::getDirection() {
	return direction;
}

float Human::getMass() {
	return mass;
}

float Human::getForce() {
	return force;
}

int Human::getDir() {
	return dir;
}

void Human::addVelocity(double x, double y) {
	velocity.x += x;
	velocity.y += y;
}

void Human::setDirection(double x, double y) {
	direction.x = x;
	direction.y = y;
}

void Human::setForce(float f) {
	force = f;
}

void Human::resetVelocity() {
	velocity.x = velocity.y = 0;
}

void Human::setAngle(float a) {
	angle = a;
}

void Human::setDir(int d) {
	sf::IntRect tR = sprite.getTextureRect();
	if (dir == d) {
		if (clock.getElapsedTime().asSeconds() > 0.05) {
			tR.left = tR.left + 15;
			if (tR.left == 75)
				tR.left = 15;
			clock.restart();
		}
	} else {
		dir = d;
		tR.left = 0;
	}
	sprite.setTextureRect(tR);
}

void Human::setDirJump(int d) {
	dir = d;
	sf::IntRect tR = sprite.getTextureRect();
	tR.left = 15;
	sprite.setTextureRect(tR);
}

void Human::resetSprite() {
	if (clock.getElapsedTime().asSeconds() >= 0.05) {
		sf::IntRect tR = sprite.getTextureRect();
		tR.left = 0;
		sprite.setTextureRect(tR);
	}
}

void Human::setState(int s) {
	state = s;
}

int Human::getState() {
	return state;
}

void Human::setNextStateChange(int nSC) {
	nextStateChange = nSC;
}

int Human::getNextStateChange() {
	return nextStateChange;
}

void Human::setJump(bool j) {
	jump = j;
}

bool Human::getJump() {
	return jump;
}

void Human::setClosestSpecial(int cS) {
	closestSpecial = cS;
}

int Human::getClosestSpecial() {
	return closestSpecial;
}

void Human::update() {
	// Apply Force
	float acceleration = getForce() / getMass();
	sf::Vector2<double> direction = getDirection();
	addVelocity(direction.x * acceleration, direction.y * acceleration);
	sf::Vector2<double> velocity = getVelocity();
	setOldX(getX());
	setOldY(getY());
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);
}

void Human::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	sprite.setRotation(angle);
	sprite.setScale((double)0.07 * dir / ppm, (double)0.07 / ppm);
	sprite.setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
	window.draw(sprite);
}