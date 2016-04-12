#include <SpeedLine.h>

SpeedLine::SpeedLine(sf::VideoMode screen, float angle, float speed) {
	this->screen = screen;
	if (angle == 0)
		up = true;
	else
		up = false;

	if ((float)angle == (float)PI)
		down = true;
	else
		down = false;

	float x2 = screen.width / 2 + sin(angle) * screen.width / 2;
	float y2 = screen.height / 2 - cos(angle) * screen.width / 2;
	
	slope = (y2 - screen.height / 2) / (x2 - screen.width / 2);

	float rDif = Functions::randomFloat(-PI / 2, PI / 2);
	angle = (angle + rDif < 0) ? (2 * PI + angle + rDif) : (angle + rDif);
	position.x = screen.width / 2 + sin(angle) * screen.width / 2;
	position.y = screen.height / 2 - cos(angle) * screen.width / 2;

	yintercept = position.y - position.x * slope;

	circle.setRadius(5);
	circle.setPosition(position.x, position.y);

	this->speed = speed;
	if (position.x > screen.width / 2 || down)
		this->speed *= -1;

	isAlive = true;

	onScreen = false;
}

bool SpeedLine::getIsAlive() {
	return isAlive;
}

void SpeedLine::update() {
	if (!up && !down) {
		position.x += speed;
		position.y = slope * position.x + yintercept;
	} else {
		position.y += speed;
	}
	circle.setPosition(position.x, position.y);

	if (!onScreen && position.x > 0 && position.x < screen.width && position.y > 0 && position.y < screen.height)
		onScreen = true;
	else if (onScreen && (position.x < 0 || position.x > screen.width || position.y < 0 || position.y > screen.height))
		isAlive = false;
}

void SpeedLine::render(sf::RenderWindow &window) {
	window.draw(circle);
}