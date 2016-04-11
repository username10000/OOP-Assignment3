#include <SpeedLine.h>

SpeedLine::SpeedLine(sf::VideoMode screen, float angle) {
	this->angle = angle;

	angle += PI / 4;
	float x2 = screen.width / 2 + sin(angle) * screen.height / 2;
	float y2 = screen.height / 2 - cos(angle) * screen.height / 2;
	
	slope = (y2 - screen.height / 2) / (x2 - screen.width / 2);

	float rDif = Functions::randomFloat(-PI / 2, PI / 2);
	angle = (angle + rDif < 0) ? (2 * PI + angle + rDif) : (angle + rDif);
	position.x = screen.width / 2 + sin(angle) * screen.height / 2;
	position.y = screen.height / 2 - cos(angle) * screen.height / 2;

	yintercept = position.y - position.x * slope;

	circle.setRadius(10);
	circle.setPosition(position.x, position.y);

	speed = 0.1;
	if (position.x > screen.width / 2)
		speed *= -1;

	//direction.x = (screen.width / 2 - position.x) / 100;
	//direction.y = (screen.height / 2 - position.y) / 100;
}

void SpeedLine::update() {
	position.x += speed;
	position.y = slope * position.x + yintercept;

	std::cout << position.x << " " << position.y << std::endl;
	circle.setPosition(position.x, position.y);
	//circle.setPosition(circle.getPosition().x + direction.x, circle.getPosition().y + direction.y);
}

void SpeedLine::render(sf::RenderWindow &window) {
	window.draw(circle);
}