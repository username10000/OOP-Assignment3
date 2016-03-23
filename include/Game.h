#ifndef GAME_H
#define GAME_H

// Dependencies
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unordered_map>
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
#include <AstroMap.h>

// Game
class Game {
	private:
		sf::RenderWindow window;
		sf::VideoMode screen;
		sf::ContextSettings settings;
		sf::Font font;
		int keys[512] = { 0 };
		int stop;
		int noPlanets;
		std::vector<std::unique_ptr<AstroObject>> astro;
		std::vector<std::unique_ptr<Ship>> ships;
		std::unordered_map<std::string, bool> menu;
		int stars[200][3];
		//std::vector<std::unique_ptr<sf::CircleShape>> stars;
		std::unique_ptr<VelocityVector> velocityVector;
		std::unique_ptr<DistanceToObject> distanceObject;
		std::unique_ptr<AstroMap> astroMap;
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
		int targetAstro;
		//AstroMap astroMap(0);
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
		float randomFloat(float start, float stop);
		double map(double v, double lmin, double lmax, double rmin, double rmax);
		void disableMenus();
		void update();
		void render();
};


#endif