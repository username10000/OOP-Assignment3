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

float AstroObject::getRadius() {
	return radius;
}

double AstroObject::getMass() {
	return mass;
}

double AstroObject::getForce() {
	return force;
}

sf::Vector2<double> AstroObject::getVelocity() {
	return velocity;
}

double AstroObject::getG() {
	return G;
}

void AstroObject::setForce(double _force) {
	force = _force;
}

void AstroObject::setAcceleration(float _acceleration) {
	acceleration = _acceleration;
}

void AstroObject::addVelocity(double x, double y) {
	velocity.x += x;
	velocity.y += y;
}

sf::Vector2<double> AstroObject::getDirection() {
	return direction;
}

void AstroObject::setDirection(double x, double y) {
	direction.x = x;
	direction.y = y;
}

std::string AstroObject::getName() {
	return name;
}

void AstroObject::setName(std::string n) {
	name = n;
}

void AstroObject::setMass(float m) {
	mass = m;
}

sf::FloatRect AstroObject::getBoundingBox() {
	return circle.getGlobalBounds();
}

float AstroObject::getRotation() {
	return rotation;
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

void AstroObject::setSecondColour(sf::Color col) {
	ndColour = col;
}

void AstroObject::createCommonObjects(sf::Texture *cT) {
	for (int i = 0; i < Functions::randomInt(50, 100); i++) {
		objs.push_back(std::unique_ptr<CommonObject>(new CommonObject(cT, ndColour, Functions::randomFloat(0, 2 * PI), rotation, radius)));
	}
}

void AstroObject::updateCommonObject() {
	for (int i = 0; i < objs.size(); i++) {
		objs[i]->update(getX(), getY());
	}
}

void AstroObject::update() {
	//circle.rotate(rotation);
}

void AstroObject::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	circle.setRadius(getRadius() / (double)ppm);
	circle.setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	if (rotation != 0) {
		atmosphere.setScale(1 / (double)ppm, 1 / (double)ppm);
		atmosphere.setPosition(circle.getPosition().x, circle.getPosition().y);
		window.draw(atmosphere);
		for (int i = 0; i < objs.size(); i++) {
			objs[i]->render(window, view, screen, ppm);
		}
	}
	window.draw(circle);
}