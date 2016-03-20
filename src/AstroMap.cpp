#include <AstroMap.h>

AstroMap::AstroMap(float ppm, sf::Font font) {
	this -> ppm = ppm;
	this -> font = font;
}

void AstroMap::addAstro(double x, double y, sf::Color colour, float radius) {
	sf::Vector2<double> pos;
	pos.x = x;
	pos.y = y;
	astro.push_back(pos);
	astroColour.push_back(colour);
	astroRadius.push_back(radius);
}

void AstroMap::setAstro(int p, double x, double y) {
	if (p < astro.size()) {
		astro[p].x = x;
		astro[p].y = y;
	}
}

void AstroMap::setShip(double x, double y) {
	ship.x = x;
	ship.y = y;
}

void AstroMap::setppm(float ppm) {
	this->ppm = ppm;
}

void AstroMap::render(sf::RenderWindow &window, sf::VideoMode screen) {
	// Draw Astro Object
	for (unsigned i = 0; i < astro.size(); i++) {
		sf::CircleShape circle(astroRadius[i] / 50);
		circle.setFillColor(astroColour[i]);
		circle.setPosition((double)(((double)screen.width / 2) + astro[i].x / (double)ppm - circle.getRadius() - 20), (double)(((double)screen.height / 2) + astro[i].y / (double)ppm - circle.getRadius() - 20));
		window.draw(circle);
	}

	// Draw Ship
	sf::CircleShape circle(10);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(1);
	circle.setPosition(screen.width / 2 + ship.x / ppm - circle.getRadius() - 20, screen.height / 2 + ship.y / ppm - circle.getRadius() - 20);
	window.draw(circle);

	// Draw Ship Text
	sf::Text text;
	text.setString("You Are Here");
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(12);
	text.setPosition(screen.width / 2 + ship.x / ppm - circle.getRadius() - 20 + circle.getRadius() * 2.5, screen.height / 2 + ship.y / ppm - circle.getRadius() - 20);
	window.draw(text);
}