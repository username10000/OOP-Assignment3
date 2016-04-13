#include <Button.h>

Button::Button() {
	active = false;
	hover = false;
}

Button::Button(sf::CircleShape shape) : Button() {
	circle = shape;
	circle.setOutlineColor(sf::Color::Red);
	rect = false;
}

Button::Button(sf::RectangleShape shape) : Button() {
	rectangle = shape;
	rect = true;
}

//Button::Button(sf::Texture &texture) : Button() {
//	this->texture = texture;
//	sprite.setTexture(this->texture);
//	isSprite = true;
//	rect = true;
//}

void Button::setPosition(double x, double y) {
	if (!rect)
		circle.setPosition(x, y);
	else
		rectangle.setPosition(x, y);
}

double Button::getX() {
	if (!rect)
		return circle.getPosition().x + circle.getRadius();
	else
		return rectangle.getPosition().x + getWidth() / 2;
}

double Button::getY() {
	if (!rect)
		return circle.getPosition().y + circle.getRadius();
	else
		return rectangle.getPosition().y + getWidth() / 2;
}

double Button::getWidth() {
	if (!rect)
		return circle.getRadius() * 2;
	else
		return rectangle.getLocalBounds().width;
}

bool Button::isActive() {
	return active;
}

void Button::update(sf::RenderWindow &window) {
	if (!rect) {
		// Cirle
		if ( sqrt( pow(mouse.getPosition(window).x - getX(), 2) + pow(mouse.getPosition(window).y - getY(), 2) ) <= circle.getRadius()) {
			if (mouse.isButtonPressed(sf::Mouse::Left)) {
				hover = false;
				active = true;
			} else {
				hover = true;
				active = false;
			}
		} else {
			hover = false;
			active = false;
		}
	} else {
		// Rectangle
	}

	if (!rect) {
		// Check Circle
		if (hover) {
			circle.setOutlineThickness(3);
		}
		if (active) {
			circle.setOutlineThickness(2);
		}
		if (!hover && !active) {
			circle.setOutlineThickness(0);
		}
	} else {
		// Check Rectangle
	}
}

void Button::render(sf::RenderWindow &window) {
	if (!rect)
		window.draw(circle);
	else
		window.draw(rectangle);
}