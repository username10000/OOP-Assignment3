#include <Ship.h>

Ship::Ship(double x, double y, float screenX, float screenY) : GameObject(x, y) {
	// Load the Ship Sprites
	texture.loadFromFile("Source/resources/shipSheet.png");
	sprite.setTexture(texture);
	sf::IntRect shipRect;
	shipRect.top = 0;
	shipRect.left = 0;
	shipRect.width = 40;
	shipRect.height = 40;
	sprite.setTextureRect(shipRect);
	sprite.setPosition(screenX - 20, screenY - 20);
	sprite.setOrigin(20, 20);

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

	explosion.loadFromFile("Source/resources/explosionSheet.png");

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

	cargo = 0;
	maxCargo = 50;

	thrust = 0;
	maxThrust = 75;

	inertiaDamper = true;

	maxVelocity = 1;

	leftRotate = 0;

	// Dynamic Thrust Test
	//fireTexture.loadFromFile("Source/resources/fire1.png");
	//fire.setTexture(fireTexture);
	//fire.setOrigin(fire.getLocalBounds().width / 2, fire.getLocalBounds().height / 2);

	// Get the Locations of all the Fires from File ***
	std::ifstream f;
	f.open("Source/resources/Ships.txt");
	if (f) {
		while (!f.eof()) {
			std::vector<sf::Vector2f> tempLoc;
			sf::Vector2f fireLocation;
			int numThrusters;

			f >> numThrusters;
			for (int i = 1; i <= numThrusters; i++) {
				f >> fireLocation.x >> fireLocation.y;

				fireLocation.x = Functions::map(fireLocation.x, 0, 39, -19.5, 19.5);
				fireLocation.y = Functions::map(fireLocation.y, 0, 39, -19.5, 19.5);

				float angleToShip = atan2(fireLocation.y, fireLocation.x);
				angleToShip = angleToShip >= 0 ? angleToShip : angleToShip + 2 * PI;
				angleToShip += PI / 2;

				float distFromShip = sqrt( pow(fireLocation.x, 2) + pow(fireLocation.y, 2) );
				distFromShip *= 0.15;

				fireLocation.x = angleToShip;
				fireLocation.y = distFromShip;

				tempLoc.push_back(fireLocation);
			}
			firePos.push_back(tempLoc);
		}
	}
	f.close();

	// Create the Fire Sprites
	fireTexture.loadFromFile("Source/resources/fireSheet.png");
	fires.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(fireTexture)));
	fires.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(fireTexture)));
	fires.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(fireTexture)));

	sf::IntRect fireRect;
	fireRect.top = 0;
	fireRect.left = 0;
	fireRect.width = 5;
	fireRect.height = 5;
	for (int i = 0; i < fires.size(); i++) {
		fires[i]->setTextureRect(fireRect);
		fires[i]->setOrigin(fires[i]->getLocalBounds().width / 2, fires[i]->getLocalBounds().height / 2);
	}

	curShip = 0;

	fireScale = 1;

	isAlive = true;

	//fireLocation.x = 33;
	//fireLocation.y = 37;

	//fireLocation.x = Functions::map(fireLocation.x, 0, 39, -19.5, 19.5);
	//fireLocation.y = Functions::map(fireLocation.y, 0, 39, -19.5, 19.5);

	////fireLocation.x = (fireLocation.x < 20) ? - (20 - fireLocation.x) : fireLocation.x - 20;
	////fireLocation.y = (fireLocation.y < 20) ? - (20 - fireLocation.y) : fireLocation.y - 20;

	//angleToShip = atan2(fireLocation.y, fireLocation.x);
	//angleToShip = angleToShip >= 0 ? angleToShip : angleToShip + 2 * PI;
	//angleToShip += PI / 2;

	//distFromShip = sqrt( pow(fireLocation.x, 2) + pow(fireLocation.y, 2) );
	////std::cout << fireLocation.x << " " << fireLocation.y << " " << distFromShip << std::endl;
	//distFromShip *= 0.15;

	buffer.loadFromFile("Source/resources/Audio/thrust.ogg");
	sound.setBuffer(buffer);

	isVisible = false;
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
	return sprite.getLocalBounds().width * sqrt(2);
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
	//for (int i = 0; i < 3; i++) {
	//	ship[i].rotate(r);
	//}
	sprite.rotate(r);
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
	return thrust * speed;
}

float Ship::getMaxThrust() {
	return maxThrust * speed;
}

float Ship::getFuel() {
	return fuel;
}

float Ship::getMaxFuel() {
	return maxFuel;
}

void Ship::setStraight(float a) {
	//for (int i = 0; i < 3; i++) {
	//	ship[i].setRotation(a * 180 / PI);
	//}
	sprite.setRotation(a * 180 / PI);
	angle = a;
}

void Ship::setLeftRotate(float r) {
	leftRotate = r;
}

float Ship::getRotation() {
	return sprite.getRotation() * PI / 180;
}

void Ship::destroy() {
	isAlive = false;
	sprite.setTexture(explosion);
	sf::IntRect expRect;
	expRect.top = 0;
	expRect.left = 0;
	expRect.width = 40;
	expRect.height = 40;
}

void Ship::setShip(int num) {
	if (num < texture.getSize().x / 40) {
		if (!isVisible && num == 0) {
			isVisible = true;
		} else {
			sf::IntRect shipRect = sprite.getTextureRect();
			shipRect.left = num * 41;
			sprite.setTextureRect(shipRect);
			curShip = num;
		}
	}
}

int Ship::getCargo() {
	return cargo;
}

void Ship::setCargo(int c) {
	cargo = c;
}
int Ship::getMaxCargo() {
	return maxCargo;
}

void Ship::setMaxCargo(int mC) {
	maxCargo = mC;
}

void Ship::setVisible(bool v) {
	isVisible = v;
}

bool Ship::getVisible() {
	return isVisible;
}

void Ship::update() {
	if (!landed) {
		sprite.rotate(rotation);
		angle += rotation;
	}

	// Automatically Spin the Ship
	if (leftRotate != 0) {
		if (leftRotate < 0) {
			float rot = 1;
			if (abs(leftRotate) < abs(rot)) {
				rot = leftRotate;
				leftRotate = 0;
				angle -= rot;
			} else {
				leftRotate += rot;
				angle += rot;
			}
			sprite.rotate(rot);
		} else {
			float rot = -1;
			if (abs(leftRotate) < abs(rot)) {
				rot = leftRotate;
				leftRotate = 0;
				angle -= rot;
			}
			else {
				leftRotate += rot;
				angle += rot;
			}
			sprite.rotate(rot);
		}
	}

	// Reset the Angle
	if (angle >= 360)
		angle -= 360;
	if (angle <= -360)
		angle += 360;

	// Slow down Rotation
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

	// Animate Fire Sprite
	if (accelerating) {
		sf::IntRect fireRect;
		fireRect = fires[0]->getTextureRect();

		if (lastChange.getElapsedTime().asSeconds() > 0.2) {
			fireRect.left = (fireRect.left + 6) % (fireTexture.getSize().x + 1);
			for (int i = 0; i < fires.size(); i++) {
				fires[i]->setTextureRect(fireRect);
			}
			lastChange.restart();
		}

		if (sound.getStatus() != sf::Sound::Playing) {
			sound.setLoop(true);
			sound.play();
		} else {
			sound.setVolume(Functions::map(thrust, 0, maxThrust, 0, 25));
		}
	} else {
		if (sound.getStatus() == sf::Sound::Playing) {
			sound.stop();
		}
	}

	if (fuel > thrust * 0.1) {
		// Add Thrust Velocity
		if ((sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) + sqrt(pow(sin(angle * PI / 180) * thrust * speed, 2) + pow(-cos(angle * PI / 180) * thrust * speed, 2))) * 60 < 299792458) {
			velocity.x += sin(angle * PI / 180) * thrust * speed;
			velocity.y += -cos(angle * PI / 180) * thrust * speed;
		}
		fuel -= thrust * 0.1;
		fireScale = Functions::map(thrust, 0, maxThrust, 0.1, 1);
	} else {
		if (fuel > 0) {
			// Add Thrust Velocity for the remaining Fuel
			if ((sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) + sqrt(pow(sin(angle * PI / 180) * (fuel / 0.1) * speed, 2) + pow(-cos(angle * PI / 180) * (fuel / 0.1) * speed, 2))) * 60 < 299792458) {
				velocity.x += sin(angle * PI / 180) * (fuel / 0.1) * speed;
				velocity.y += -cos(angle * PI / 180) * (fuel / 0.1) * speed;
			}
			fuel = 0;
			fireScale = Functions::map(fuel / 0.1, 0, maxThrust, 0.1, 1);
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

	if (!isAlive) {
		sf::IntRect expRect = sprite.getTextureRect();
		expRect.left += 41;
		if (expRect.left > explosion.getSize().x) {
			expRect.left = 0;
			expRect.top += 41;
			if (expRect.top > explosion.getSize().y) {
				expRect.top -= 41;
				sprite.setColor(sf::Color::Transparent);
				isAlive = true;
			}
		}
		sprite.setTextureRect(expRect);
	}
}

void Ship::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	sprite.setScale((double)0.15 / ppm, (double)0.15 / ppm);
	sprite.setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
	window.draw(sprite);

	if (accelerating) {
		for (int i = 0; i < firePos[curShip].size(); i++) {
			fires[i]->setScale((double)0.15 * (double)fireScale / ppm, (double)0.15 / ppm);
			fires[i]->setRotation(sprite.getRotation());
			fires[i]->setPosition(sprite.getPosition().x + sin(firePos[curShip][i].x + sprite.getRotation() * PI / 180) * firePos[curShip][i].y / ppm, sprite.getPosition().y - cos(firePos[curShip][i].x + sprite.getRotation() * PI / 180) * firePos[curShip][i].y / ppm);
			window.draw(*fires[i]);
		}
	}
}