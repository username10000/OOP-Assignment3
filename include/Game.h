#ifndef GAME_H
#define GAME_H

// Dependencies
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <math.h>
#include <AstroObject.h>
#include <Sun.h>
#include <Planet.h>
#include <SolarSystem.h>

// Game
class Game {
	private:
		sf::RenderWindow window;
		sf::VideoMode screen;
		sf::ContextSettings settings;
		sf::Font font;
		int keys[512] = { 0 };
		int stop;
		std::vector<std::unique_ptr<AstroObject>> astro;
		SolarSystem solarSystem;
		sf::Vector2<long long> view;
		float ppm;
	public:
		Game();
		~Game();
		void events();
		int getStop();
		float dist(long long x1, long long y1, long long x2, long long y2);
		void update();
		void render();
};


#endif