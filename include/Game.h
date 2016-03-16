#ifndef GAME_H
#define GAME_H

// Dependencies
#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <Formula.h>
#include <AstroObject.h>
#include <Sun.h>
#include <Planet.h>
#include <SolarSystem.h>
#include <Ship.h>
#include <VelocityVector.h>
#include <DistanceToObject.h>

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
		std::vector<std::unique_ptr<Ship>> ships;
		std::unique_ptr<VelocityVector> velocityVector;
		std::unique_ptr<DistanceToObject> distanceObject;
		SolarSystem solarSystem;
		sf::Vector2<double> view;
		float ppm;
		int frames;
		sf::Clock clock;
		sf::Clock frameTime;
		sf::Text frameRate;
		sf::Text distance;
		float dt;
		float accumulator;
	public:
		Game();
		~Game();
		void events();
		int getStop();
		double dist(double x1, double y1, double x2, double y2);
		//float semiMajorAxis(int i);
		//float eccentricityVector(int i);
		//float apoapsis(int i);
		void keyPressed();
		void collisions();
		void fastForwardObject(int i, int loops);
		int randomInt(int start, int stop);
		//float map(float v, float lmin, float lmax, float rmin, float rmax);
		void update();
		void render();
};


#endif