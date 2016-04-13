#include <AstroMap.h>

AstroMap::AstroMap(float ppm, sf::Font font) {
	this -> ppm = ppm;
	this -> font = font;
}

void AstroMap::addAstro(sf::VideoMode screen, double x, double y, sf::Color colour, float radius) {
	//sf::Vector2<double> pos;
	//pos.x = x;
	//pos.y = y;
	//astro.push_back(pos);
	//astroColour.push_back(colour);
	//astroRadius.push_back(radius);

	sf::CircleShape circle;
	if (radius > 1500)
		circle.setRadius(radius / 75);
	else
		circle.setRadius(radius / 50);
	circle.setFillColor(colour);
	circle.setPosition((double)(((double)screen.width / 2) + x / (double)ppm - circle.getRadius() - 20), (double)(((double)screen.height / 2) + y / (double)ppm - circle.getRadius() - 20));
	buttons.push_back( std::unique_ptr<Button>( new Button(circle) ) );
}

void AstroMap::setAstro(sf::RenderWindow &window, sf::VideoMode screen, int p, double x, double y) {
	//if (p < astro.size()) {
	//	astro[p].x = x;
	//	astro[p].y = y;
	//}
	if (p < buttons.size()) {
		buttons[p] -> setPosition((double)(((double)screen.width / 2) + x / (double)ppm - buttons[p] -> getWidth() / 4 - 20), (double)(((double)screen.height / 2) + y / (double)ppm - buttons[p]->getWidth() / 4 - 20));
		buttons[p] -> update(window);
	}
}

void AstroMap::setShip(double x, double y) {
	ship.x = x;
	ship.y = y;
}

void AstroMap::setppm(float ppm) {
	this->ppm = ppm;
}

void AstroMap::setNoPlanets(int nP) {
	noPlanets = nP;
}

void AstroMap::setParent(int moon, int planet) {
	parent[moon] = planet;
}

int AstroMap::getClickedPlanet() {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttons[i] -> isActive())
			return i;
	}
	return -1;
}

void AstroMap::render(sf::RenderWindow &window, sf::VideoMode screen) {
	// Draw Astro Object
	//for (unsigned i = 0; i < astro.size(); i++) {
	//	sf::CircleShape circle(astroRadius[i] / 50);
	//	circle.setFillColor(astroColour[i]);
	//	circle.setPosition((double)(((double)screen.width / 2) + astro[i].x / (double)ppm - circle.getRadius() - 20), (double)(((double)screen.height / 2) + astro[i].y / (double)ppm - circle.getRadius() - 20));
	//	window.draw(circle);
	//}
	for (unsigned i = 0; i < buttons.size(); i++) {
		if (i != 0) {
			double dFC = sqrt(pow(buttons[i]->getX() - buttons[parent[i]]->getX(), 2) + pow(buttons[i]->getY() - buttons[parent[i]]->getY(), 2));
			sf::CircleShape orbit(dFC);
			orbit.setFillColor(sf::Color::Transparent);
			orbit.setOutlineThickness(1);
			orbit.setOutlineColor(sf::Color::White);
			orbit.setPointCount(200);
			orbit.setPosition(buttons[parent[i]]->getX() - orbit.getRadius(), buttons[parent[i]]->getY() - orbit.getRadius());
			window.draw(orbit);
		}
		buttons[i] -> render(window);
	}

	// Draw Ship
	sf::CircleShape circle(1);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(1);
	circle.setPosition(screen.width / 2 + ship.x / ppm - circle.getRadius() / 2 - 20, screen.height / 2 + ship.y / ppm - circle.getRadius() / 2 - 20);
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