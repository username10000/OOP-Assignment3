#ifndef SUN_H
#define SUN_H

// Dependencies
#include <AstroObject.h>

// Sun
class Sun : public AstroObject {
	private:
		//sf::CircleShape circle;
	public:
		Sun(double x, double y, float _radius, sf::Color _colour, float _rotation);
		Sun();
		void update();
		//void render(sf::RenderWindow &window, sf::Vector2<double> view, sf::VideoMode screen);
};

#endif