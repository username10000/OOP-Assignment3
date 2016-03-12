#include <Ship.h>

Ship::Ship(double x, double y, float screenX, float screenY) : GameObject(x, y) {
	texture.loadFromFile("ship.png");
	sprite.setTexture(texture);
	//setScreenPosition(screenX, screenY);
	sprite.setPosition(screenX - 20, screenY - 20);
	sprite.setOrigin(20, 20);
	//sprite.setScale(sf::Vector2f(10.0f, 10.0f));

	// Load Sprites
	shipTexture[0].loadFromFile("ship.png");
	shipTexture[1].loadFromFile("ship1.png");
	shipTexture[2].loadFromFile("ship2.png");
	ship[0].setTexture(shipTexture[0]);
	ship[1].setTexture(shipTexture[1]);
	ship[2].setTexture(shipTexture[2]);
	for (int i = 0; i < 3; i++) {
		ship[i].setPosition(screenX - ship[i].getGlobalBounds().width / 2, screenY - ship[i].getGlobalBounds().width / 2);
		ship[i].setOrigin(ship[i].getGlobalBounds().width / 2, ship[i].getGlobalBounds().width / 2);
	}

	velocity.x = velocity.y = 0;
	rotation = angle = 0;
	force = acceleration = 0;
	direction.x = direction.y = 0;
	mass = 0.00000000000000000000040 * 9.3;
	speed = 0.02;

	accelerating = false;
	spriteNo = 0;

	//landed = false;
	//angleToPlanet = 0;
	//planet = -1;
	//std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height;
}

Ship::Ship() : Ship(0, 0, 0, 0) {

}

void Ship::addVelocity() {
	velocity.x += sin(angle * PI / 180) * speed;
	velocity.y += -cos(angle * PI / 180) * speed;
}

void Ship::addVelocity(double x, double y) {
	velocity.x += x;
	velocity.y += y;
}

void Ship::subVelocity() {
	velocity.x -= sin(angle * PI / 180) * speed;
	velocity.y -= -cos(angle * PI / 180) * speed;
}

sf::Vector2<double> Ship::getVelocity() {
	return velocity;
}

void Ship::addRotation(float x) {
	rotation += x;
}

void Ship::resetRotation() {
	rotation = 0;
}

void Ship::setSpeed(float s) {
	speed = s;
}

float Ship::getMass() {
	return mass;
}

float Ship::getForce() {
	return force;
}

void Ship::setForce(double f) {
	force = f;
}

void Ship::addForce(double f) {
	force += f;
}

sf::Vector2<double> Ship::getDirection() {
	return direction;
}

void Ship::setDirection(double x, double y) {
	direction.x = x;
	direction.y = y;

	/*
	if (direction.x > 1)
		direction.x = 1;
	if (direction.x < -1)
		direction.x = -1;
	if (direction.y > 1)
		direction.y = 1;
	if (direction.y < -1)
		direction.y = -1;
	*/
}

void Ship::setAccelerating(bool a) {
	accelerating = a;
}

bool Ship::getAccelerating() {
	return accelerating;
}

void Ship::resetVelocity() {
	velocity.x = velocity.y = 0;
}

float Ship::getRadius() {
	return ship[0].getGlobalBounds().width * sqrt(2);
}

//bool Ship::getLanded() {
//	return landed;
//}
//
//void Ship::setLanded(bool l) {
//	landed = l;
//}
//
//float Ship::getAngleToPlanet() {
//	return angleToPlanet;
//}
//
//void Ship::setAngleToPlanet(float t) {
//	angleToPlanet = t;
//}
//
//int Ship::getPlanet() {
//	return planet;
//}
//
//void Ship::setPlanet(int p) {
//	planet = p;
//}

sf::FloatRect Ship::getBoundingBox() {
	return sprite.getGlobalBounds();
}

void Ship::update() {
	for (int i = 0; i < 3; i++) {
		ship[i].rotate(rotation);
	}
	sprite.rotate(rotation);
	angle += rotation;

	if (angle >= 360)
		angle -= 360;
	if (angle <= -360)
		angle += 360;

	// Animate Sprite
	if (accelerating) {
		if (spriteNo == 0) {
			spriteNo = 1;
			lastChange.restart();
		} else {
			if (lastChange.getElapsedTime().asSeconds() > 0.2) {
				if (spriteNo == 1)
					spriteNo = 2;
				else
					spriteNo = 1;
				lastChange.restart();
			}
		}
	} else {
		 spriteNo = 0;
	 }
	
	// Force
	float acceleration = getForce() / getMass();
	sf::Vector2<double> direction = getDirection();
	//setAcceleration(acceleration);
	addVelocity(direction.x * acceleration, direction.y * acceleration);
	sf::Vector2<double> velocity = getVelocity();
	setOldX(getX());
	setOldY(getY());
	setX(getX() + velocity.x);
	setY(getY() + velocity.y);
	//std::cout << acceleration << std::endl;

	//std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << "    " << sprite.getLocalBounds().width << " " << sprite.getLocalBounds().height << std::endl;
}

void Ship::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	for (int i = 0; i < 3; i++) {
		ship[i].setScale((double)0.15 / ppm, (double)0.15 / ppm);
	}
	//sprite.setScale(1 / ppm, 1 / ppm);
	window.draw(ship[spriteNo]);
	//window.draw(sprite);
}