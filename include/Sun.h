#ifndef SUN_H
#define SUN_H

// Dependencies
#include <AstroObject.h>

// Sun
class Sun : public AstroObject {
	private:
		sf::CircleShape circle;
	public:
		Sun(float x, float y, float _radius, sf::Color _colour);
		Sun();
		void update();
		void render(sf::RenderWindow &window);
};

#endif