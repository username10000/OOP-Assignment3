#include <AstroObject.h>

AstroObject::AstroObject(double x, double y, float _radius, sf::Color _colour, float _rotation) : GameObject(x, y) {
	//texture.loadFromFile("T1.png");
	//texture.setRepeated(false);
	radius = _radius;
	colour = _colour;
	mass = (float)(_radius * 9.3);
	force = velocity.x = velocity.y = 0;
	acceleration = 0;
	circle.setRadius(_radius);
	circle.setOrigin(_radius, _radius);
	circle.setPointCount(200);

	// Create Texture for the Atmosphere
	atmTexture.create(getRadius() * 1.5, getRadius() * 1.5);
	atmTexture.clear(sf::Color::Transparent);
	_colour = sf::Color(Functions::randomInt(0, 255), Functions::randomInt(0, 255), Functions::randomInt(0, 255));
	
	for (int i = 0; i <= atmTexture.getSize().x / 4; i++) {
			sf::Color circleColour = sf::Color(_colour.r, _colour.g, _colour.b, Functions::map(i, 0, (int)atmTexture.getSize().x / 4, 0, 35));
			sf::CircleShape c;
			c.setFillColor(circleColour);
			c.setRadius((atmTexture.getSize().x - 2 * i) / 2);
			c.setOrigin(c.getRadius(), c.getRadius());
			c.setPointCount(200);
			c.setPosition(atmTexture.getSize().x / 2, atmTexture.getSize().y / 2);
			atmTexture.draw(c);
	}

	// Create the Texture
	atmTexture.display();

	// Assign the Texture
	atmosphereTexture = atmTexture.getTexture();

	// Create the Atmosphere
	atmosphere.setRadius(getRadius() * 1.5);
	atmosphere.setOrigin(atmosphere.getRadius(), atmosphere.getRadius());
	atmosphere.setPointCount(200);
	atmosphere.setTexture(&atmosphereTexture);

	// Initialise Variables
	direction.x = 1;
	direction.y = 1;
	G = 0.667;
	name = "OBJECT";
	rotation = _rotation;
	habitable = true;
}

AstroObject::AstroObject() : AstroObject(0, 0, 100, sf::Color(255, 255, 0), 0.01) {
	radius = 100;
	colour = sf::Color(255, 255, 0);
}

sf::Color AstroObject::getColour() {
	return colour;
}

void AstroObject::setSecondColour(sf::Color col) {
	ndColour = col;
}

float AstroObject::getRadius() {
	return radius;
}

void AstroObject::setMass(float m) {
	mass = m;
}

double AstroObject::getMass() {
	return mass;
}

void AstroObject::setForce(double _force) {
	force = _force;
}

double AstroObject::getForce() {
	return force;
}

double AstroObject::getG() {
	return G;
}

void AstroObject::addVelocity(double x, double y) {
	velocity.x += x;
	velocity.y += y;
}

sf::Vector2<double> AstroObject::getVelocity() {
	return velocity;
}

void AstroObject::setAcceleration(float _acceleration) {
	acceleration = _acceleration;
}

void AstroObject::setDirection(double x, double y) {
	direction.x = x;
	direction.y = y;
}

sf::Vector2<double> AstroObject::getDirection() {
	return direction;
}

void AstroObject::setName(std::string n) {
	name = n;
}

std::string AstroObject::getName() {
	return name;
}

sf::FloatRect AstroObject::getBoundingBox() {
	return circle.getGlobalBounds();
}

float AstroObject::getRotation() {
	return rotation;
}

void AstroObject::setHabitable(bool h) {
	habitable = h;
}

bool AstroObject::isHabitable() {
	return habitable;
}

void AstroObject::setPlanetTexture(sf::Texture *pT) {
	circle.setTexture(pT);
}

void AstroObject::rotate() {
	circle.rotate(rotation);
	atmosphere.rotate(rotation);
}

void AstroObject::setInhabitants(int h) {
	inhabitants = h;
}

int AstroObject::getInhabitants() {
	return inhabitants;
}

void AstroObject::createCommonObjects(sf::Texture *cT) {
	float angle = 0, scale = 0, spacing = 0, objSpace = 0, totalEmpty = 0;
	int numObj = 0, type = 0, gValue = 100;
	float sBuildAng = 0, eBuildAng = 0;
	//bool fuelStation = false;
	sf::Color col;
	sf::IntRect tR;
	tR.top = 0;
	tR.left = 0;
	tR.width = 20;
	tR.height = 40;

	if (habitable) {
		do {
			// Change type of Object
			if (numObj == 0) {
				//if (type == 1) {
				//	numObj = Functions::randomInt(5, 9);
				//	for (int b = 0; b < numObj; b++) {
				//		eBuildAng = angle;
				//		scale = Functions::randomFloat(0.5, 0.7);
				//		spacing = Functions::randomFloat(10, 20) * scale;
				//		objSpace = (20 * scale + spacing) / radius;
				//		gValue = Functions::randomInt(50, 200);
				//		col = sf::Color(gValue, gValue, gValue);
				//		tR.top = 0;
				//		tR.left = Functions::randomInt(1, 5) * 21;
				//		// Create the Object
				//		objs.push_back(std::unique_ptr<CommonObject>(new CommonObject(cT, col, Functions::randomFloat(sBuildAng, eBuildAng), rotation, radius)));
				//		objs[objs.size() - 1]->setScale(scale);
				//		objs[objs.size() - 1]->setTextureRect(tR);
				//	}
				//}
				type = Functions::randomInt(0, 2); // (type + 1) % 3;
				switch (type) {
				case 0:
					// Tree
					numObj = Functions::randomInt(10, 20);
					break;
				case 1:
					// Building
					numObj = Functions::randomInt(5, 9);
					sBuildAng = angle;
					break;
				default:
					// Empty Space
					numObj = Functions::randomInt(5, 10);
					break;
				}
			}

			// Change the Properties of each Object
			switch (type) {
				case 0:
					// Tree
					scale = Functions::randomFloat(0.3, 0.5);
					spacing = Functions::randomFloat(0, 5) * scale;
					objSpace = (20 * scale + spacing) / radius;
					col = ndColour;
					tR.top = 0;
					tR.left = 0;
					break;
				case 1:
					// Building
					scale = Functions::randomFloat(0.5, 0.7);
					spacing = Functions::randomFloat(1, 2) * scale;
					objSpace = (20 * scale + spacing) / radius;
					gValue = Functions::randomInt(50, 200);
					col = sf::Color(gValue, gValue, gValue);
					tR.top = 0;
					tR.left = Functions::randomInt(1, 5) * 21;
					break;
				default:
					//Empty Space
					scale = Functions::randomFloat(0.5, 0.9);
					spacing = Functions::randomFloat(10, 20) * scale;
					objSpace = (20 * scale + spacing) / radius;
					//col = sf::Color(Functions::randomInt(0, 255), Functions::randomInt(0, 255), Functions::randomInt(0, 255));
					//tR.left = Functions::randomInt(1, 5) * 21;
					break;
			}

			if (type == 0 || type == 1) {
				// Create the Object
				objs.push_back(std::unique_ptr<CommonObject>(new CommonObject(cT, col, angle, rotation, radius)));
				objs[objs.size() - 1]->setScale(scale);
				objs[objs.size() - 1]->setTextureRect(tR);
			}

			//if (type == 2) {
			//	totalEmpty += objSpace;
			//}

			angle += objSpace;
			numObj--;

		} while (angle < 2 * PI);
	} else {
			float fuelAngle = Functions::randomFloat(0, 2 * PI);
			// Fuel
			scale = 0.3;
			spacing = 0;
			objSpace = (20 * scale + spacing) / radius;
			col = sf::Color::White;
			tR.top = 41;
			tR.left = 0;
			sObjs.push_back(std::unique_ptr<SpecialObject>(new SpecialObject(cT, col, fuelAngle, rotation, radius)));
			sObjs[sObjs.size() - 1]->setScale(scale);
			sObjs[sObjs.size() - 1]->setTextureRect(tR);
			sObjs[sObjs.size() - 1]->setType(0);
		
			float monolithAngle;
			do {
				monolithAngle = Functions::randomFloat(0, 2 * PI);
			} while (abs(fuelAngle - monolithAngle) < PI / 2);

			// Monolith
			scale = 0.3;
			spacing = 0;
			objSpace = (20 * scale + spacing) / radius;
			col = sf::Color::White;
			tR.top = 41;
			tR.left = 21;
			sObjs.push_back(std::unique_ptr<SpecialObject>(new SpecialObject(cT, col, monolithAngle, rotation, radius)));
			sObjs[sObjs.size() - 1]->setScale(scale);
			sObjs[sObjs.size() - 1]->setTextureRect(tR);
			sObjs[sObjs.size() - 1]->setType(Functions::randomInt(1, 3));
	}
}

void AstroObject::updateCommonObject() {
	for (int i = 0; i < objs.size(); i++) {
		objs[i]->update(getX(), getY());
	}
	for (int i = 0; i < sObjs.size(); i++) {
		sObjs[i]->update(getX(), getY());
	}
}

int AstroObject::getNearSpecial(double x, double y) {
	for (int i = 0; i < sObjs.size(); i++) {
		if (Functions::dist(x, y, sObjs[i]->getX(), sObjs[i]->getY()) <= sObjs[i]->getDimension().x * sObjs[i]->getScale() && sObjs[i]->getActive()) {
			return i;
		}
	}
	return -1;
}

int AstroObject::getType(int index) {
	return sObjs[index]->getType();
}

void AstroObject::setInactive(int index) {
	sObjs[index]->setActive(false);
}

void AstroObject::setParentPlanet(int pP) {
	parentPlanet = pP;
}

int AstroObject::getParentPlanet() {
	return parentPlanet;
}

void AstroObject::update() {
	//circle.rotate(rotation);
}

void AstroObject::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	circle.setRadius(getRadius() / (double)ppm);
	circle.setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	if (habitable) {
		atmosphere.setScale(1 / (double)ppm, 1 / (double)ppm);
		atmosphere.setPosition(circle.getPosition().x, circle.getPosition().y);
		window.draw(atmosphere);
	}
	if (rotation != 0) {
		for (int i = 0; i < objs.size(); i++) {
			objs[i]->render(window, view, screen, ppm);
		}
		for (int i = 0; i < sObjs.size(); i++) {
			sObjs[i]->render(window, view, screen, ppm);
		}
	}
	window.draw(circle);
}