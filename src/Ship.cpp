#include <Ship.h>

Ship::Ship(double x, double y, float screenX, float screenY) : GameObject(x, y) {
	texture.loadFromFile("ship.png");
	sprite.setTexture(texture);
	//setScreenPosition(screenX, screenY);
	sprite.setPosition(screenX - 20, screenY - 20);
	sprite.setOrigin(20, 20);
	//sprite.setScale(sf::Vector2f(10.0f, 10.0f));

	// Load Sprites
	shipTexture[0].loadFromFile("Source/resources/ship.png");
	shipTexture[1].loadFromFile("Source/resources/ship1.png");
	shipTexture[2].loadFromFile("Source/resources/ship2.png");
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
	//mass = 0.00000000000000000000040 * 9.3;
	mass = 1;
	speed = 0.0003;

	accelerating = false;
	spriteNo = 0;

	landed = false;

	fuel = maxFuel = 100000;

	thrust = 0;
	maxThrust = 75;

	inertiaDamper = true;

	maxVelocity = 1;

	leftRotate = 0;
}

Ship::Ship() : Ship(0, 0, 0, 0) {

}

void Ship::addVelocity() {
	thrust += 0.5;
	thrust = thrust > maxThrust ? maxThrust : thrust;
	//thrust.x += sin(angle * PI / 180) * speed;
	//thrust.y += -cos(angle * PI / 180) * speed;
	//velocity.x += sin(angle * PI / 180) * speed;
	//velocity.y += -cos(angle * PI / 180) * speed;
}

void Ship::subVelocity() {
	thrust -= 0.5;
	thrust = thrust < 0 ? 0 : thrust;
	//thrust.x -= sin(angle * PI / 180) * speed;
	//thrust.y -= -cos(angle * PI / 180) * speed;
	//velocity.x -= sin(angle * PI / 180) * speed;
	//velocity.y -= -cos(angle * PI / 180) * speed;
}

void Ship::addVelocity(double x, double y) {
	velocity.x += x;
	velocity.y += y;
}

void Ship::setVelocity(double x, double y) {
	velocity.x = x;
	velocity.y = y;
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
	return ship[0].getLocalBounds().width * sqrt(2);
}

bool Ship::getLanded() {
	return landed;
}

void Ship::setLanded(bool l) {
	landed = l;
}

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

float Ship::getAngle() {
	return angle * 3.14159 / 180;
}

void Ship::setClosestPlanet(int p) {
	closestPlanet = p;
}

int Ship::getClosestPlanet() {
	return closestPlanet;
}

void Ship::setRotation(float r) {
	for (int i = 0; i < 3; i++) {
		ship[i].rotate(r);
	}
	angle += r;
}

float Ship::getThrustPercentage() {
	return Functions::map(thrust, 0, maxThrust, 0, 100);
}

void Ship::cutThrust() {
	thrust = 0;
}

void Ship::setInertiaDamper(bool iD) {
	inertiaDamper = iD;
}

bool Ship::getInertiaDamper() {
	return inertiaDamper;
}

float Ship::getFuelPercentage() {
	return Functions::map(fuel, 0, maxFuel, 0, 100);
}

void Ship::refuel() {
	fuel = maxFuel;
}

void Ship::addMaxFuel(float f) {
	maxFuel += f;
}

void Ship::addMaxThrust(float t) {
	maxThrust += t;
}

void Ship::addMaxVelocity(float v) {
	maxVelocity += v;
}

float Ship::getMaxVelocity() {
	return maxVelocity;
}

float Ship::getThrust() {
	return thrust;
}

float Ship::getMaxThrust() {
	return maxThrust;
}

float Ship::getFuel() {
	return fuel;
}

float Ship::getMaxFuel() {
	return maxFuel;
}

void Ship::setStraight(float a) {
	for (int i = 0; i < 3; i++) {
		ship[i].setRotation(a * 180 / PI);
	}
	angle = a;
}

void Ship::setLeftRotate(float r) {
	leftRotate = r;
}

float Ship::getRotation() {
	return ship[0].getRotation() * PI / 180;
}

void Ship::update() {
	if (!landed) {
		for (int i = 0; i < 3; i++) {
			ship[i].rotate(rotation);
		}
		sprite.rotate(rotation);
		angle += rotation;
	}

	if (leftRotate != 0) {
		if (leftRotate < 0) {
			float rot = 1;
			//std::cout << leftRotate << " " << rot << "  ";
			if (abs(leftRotate) < abs(rot)) {
				rot = leftRotate;
				leftRotate = 0;
				angle -= rot;
			} else {
				leftRotate += rot;
				angle += rot;
			}
			//std::cout << leftRotate << " " << rot << std::endl;
			for (int i = 0; i < 3; i++) {
				ship[i].rotate(rot);
			}
		} else {
			float rot = -1;
			//std::cout << leftRotate << " " << rot << "  ";
			if (abs(leftRotate) < abs(rot)) {
				rot = leftRotate;
				leftRotate = 0;
				angle -= rot;
			}
			else {
				leftRotate += rot;
				angle += rot;
			}
			//std::cout << leftRotate << " " << rot << std::endl;
			for (int i = 0; i < 3; i++) {
				ship[i].rotate(rot);
			}
		}
	}


	if (angle >= 360)
		angle -= 360;
	if (angle <= -360)
		angle += 360;

	if (inertiaDamper && rotation != 0 && leftRotate == 0) {
		float oldRotation = rotation;
		if (rotation > 0)
			rotation -= 0.02;
		else
			rotation += 0.02;
		if ((oldRotation < 0 && rotation > 0) || (oldRotation > 0 && rotation < 0))
			rotation = 0;
	}

	if (thrust != 0 && fuel != 0)
		accelerating = true;
	else
		accelerating = false;

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

	if (fuel > thrust * 0.1) {
		// Add Thrust Velocity
		velocity.x += sin(angle * PI / 180) * thrust * speed;
		velocity.y += -cos(angle * PI / 180) * thrust * speed;
		fuel -= thrust * 0.1;
	} else {
		if (fuel > 0) {
			// Add Thrust Velocity for the remaining Fuel
			velocity.x += sin(angle * PI / 180) * (fuel / 0.1) * speed;
			velocity.y += -cos(angle * PI / 180) * (fuel / 0.1) * speed;
			fuel = 0;
		}
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

	//if (landed)
	//	std::cout << "PLANET" << std::endl;
	//else
	//	std::cout << "SPACE" << std::endl;

	//std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << "    " << sprite.getLocalBounds().width << " " << sprite.getLocalBounds().height << std::endl;
}

void Ship::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	for (int i = 0; i < 3; i++) {
		ship[i].setScale((double)0.15 / ppm, (double)0.15 / ppm);
		ship[i].setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
		//ship[i].setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - ship[i].getGlobalBounds().width / 2), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - ship[i].getGlobalBounds().width / 2));
	}
	//sprite.setScale(1 / ppm, 1 / ppm);
	window.draw(ship[spriteNo]);
	//window.draw(sprite);
}