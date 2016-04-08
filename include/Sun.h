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
};

#endif