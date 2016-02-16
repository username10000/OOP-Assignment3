#include <SolarSystem.h>

SolarSystem::SolarSystem(double _radius) {
	radius = _radius;
}

SolarSystem::SolarSystem() : SolarSystem(1000000) {
}

double SolarSystem::getRadius() {
	return radius;
}