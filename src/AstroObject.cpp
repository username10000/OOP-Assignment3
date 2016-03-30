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

	//rTexture.create(radius, radius);
	//rTexture.clear(sf::Color::Green);

	//float xCentre = radius / 2;
	//float yCentre = radius / 2;
	//std::vector<sf::Vertex> vertices;

	//// Centre
	//vertices.push_back(sf::Vertex(sf::Vector2f(xCentre, yCentre), sf::Color::Red));
	//float maxRadius = 100;
	//float lastRadius = maxRadius;

	//int verticesNum = 100;
	//for (int i = 1; i <= verticesNum; i++) {
	//	float theta = Functions::map(i, 1, verticesNum, 0, 2 * PI);
	//	if (Functions::randomInt(0, 1) == 0 || lastRadius > maxRadius)
	//		lastRadius -= Functions::randomFloat(1, maxRadius / 10);
	//	else
	//		lastRadius += Functions::randomFloat(1, maxRadius / 10);
	//	float xPos = xCentre + sin(theta) * lastRadius;
	//	float yPos = yCentre - cos(theta) * lastRadius;
	//	vertices.push_back(sf::Vertex(sf::Vector2f(xPos, yPos), sf::Color::Red));
	//}

	//rTexture.draw(&vertices[0], vertices.size(), sf::TrianglesFan);

	//rTexture.display();
	//circle.setTexture(&rTexture.getTexture());

	//sf::Image image;
	//int imageRadius = 2000;
	//image.create(imageRadius, imageRadius);

	//// Texture Background
	//for (int i = 0; i < imageRadius; i++) {
	//	for (int j = 0; j < imageRadius; j++) {
	//		image.setPixel(i, j, sf::Color::Green);
	//	}
	//}

	//// Islands
	//for (int z = 0; z < Functions::randomInt(50, 100); z++) {
	//	int maxRadius = Functions::randomInt(50, 100);
	//	sf::Vector2i coords;
	//	coords.x = Functions::randomInt(0, imageRadius - 1);
	//	coords.y = Functions::randomInt(0, imageRadius - 1);

	//	for (int i = coords.x - maxRadius; i <= coords.x + maxRadius; i++) {
	//		for (int j = coords.y - maxRadius; j <= coords.y + maxRadius; j++) {
	//			if (i > 0 && i < imageRadius && j > 0 && j < imageRadius && Functions::dist(i, j, coords.x, coords.y) <= maxRadius) {
	//				int distance = (int)Functions::dist(i, j, coords.x, coords.y);
	//				int mappedDistance = (int)Functions::map(distance, 0, maxRadius, 100, 1);
	//				if (Functions::randomInt(1, 100) <= mappedDistance) {
	//					image.setPixel(i, j, sf::Color::Blue);
	//				}
	//			}
	//		}
	//	}
	//}

	//texture.loadFromImage(image);
	//circle.setTexture(&texture);

	//circle.setTexture(&texture);
	//sf::IntRect sR;
	//sR.left = 100;
	//sR.top = 100;
	//sR.width = radius * 10;
	//sR.height = radius * 10;
	//circle.setTextureRect(sR);

	//circle.setFillColor(sf::Color::Yellow);
	direction.x = 1;
	direction.y = 1;
	G = 0.667;
	name = "OBJECT";
	rotation = _rotation;
	habitable = true;
	
	//if (habitable) {
	//	for (int i = 0; i < rand() % (20 - 5) + 5; i++) {
	//		locals.push_back(std::unique_ptr<Human>(new Human(0, 0, &humanTexture)));
	//		float rAngle = Functions::randomFloat(0, 2 * PI);
	//		locals[i] -> setX(getX() - cos(rAngle) * radius);
	//		locals[i] -> setY(getY() - sin(rAngle) * radius);
	//	}
	//}
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
}

void AstroObject::setInhabitants(int h) {
	inhabitants = h;
}

int AstroObject::getInhabitants() {
	return inhabitants;
}

void AstroObject::update() {
	//circle.rotate(rotation);
}

void AstroObject::render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen, float ppm) {
	circle.setRadius(getRadius() / (double)ppm);
	circle.setPosition((double)(((double)screen.width / 2) + (getX() - view.x) / (double)ppm - 20), (double)(((double)screen.height / 2) + (getY() - view.y) / (double)ppm - 20));
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	window.draw(circle);
}