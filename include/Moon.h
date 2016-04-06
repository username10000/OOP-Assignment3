#ifndef MOON_H
#define MOON_H

// Dependencies
#include <SFML/Graphics.hpp>
#include <Planet.h>

// Moon
class Moon : public Planet {
	private:
		sf::RenderTexture rTexture;
		sf::Texture texture;
	public:
		Moon(double x, double y, float _radius, sf::Color _colour, float _rotation);
};

#endif